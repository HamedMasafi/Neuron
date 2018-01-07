/**************************************************************************
**
** This file is part of Neuron.
** https://github.com/HamedMasafi/Neuron
**
** Neuron is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Neuron is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Neuron.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#include <NeuronServer>
#include <QTimer>
#include <QtCore/QCryptographicHash>
#include <QtCore/QJsonDocument>
#include <QtCore/QSet>
#include <QtCore/QThread>
#include <QtCore/QVariant>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>

#ifdef QT_QML_LIB
#include <QtQml/QJSEngine>
#endif

#include "neuronpeer.h"
#include "neuronabstracthub_p.h"
#include "neuronabstracthub.h"
#include "neuronabstractserializer.h"
#include "neuronremotecall_p.h"
#include "neuronsharedobject.h"
#include "neuronjsonbinaryserializer.h"
#include "neuronsimpletokenvalidator.h"

#ifdef LONG_LONG_MAX
#define MAX LONG_LONG_MAX
#elif defined(LONG_MAX)
#define MAX LONG_MAX
#else
#error "No LONG_LONG_MAX nor LONG_MAX is defined"
#endif

NEURON_BEGIN_NAMESPACE

NeuronAbstractHubPrivate::NeuronAbstractHubPrivate(NeuronAbstractHub *parent)
    : q_ptr(parent), peer(0), serializer(0),
      requestId(0), isTransaction(false), isMultiThread(false), hubId(0),
      status(NeuronAbstractHub::Unconnected)
#ifdef QT_QML_LIB
      ,
      jsEngine(0), qmlEngine(0)
#endif
{
}

void NeuronAbstractHubPrivate::addToMap(QVariantMap *map, QVariant var,
                                       int index)
{
    if (var != QVariant()) {
        QString i = QString::number(index);
        map->insert("val" + i, var);
    }
}

void NeuronAbstractHubPrivate::procMap(QVariantList list)
{
    foreach (QVariant v, list) {
        if (v.type() == QVariant::Map)
            procMap(v.toMap());
        else if (v.type() == QVariant::List)
            procMap(v.toList());
    }
}

void NeuronAbstractHubPrivate::procMap(QVariantMap map)
{
    Q_Q(NeuronAbstractHub);

    QList<QGenericArgument> args;
    bool ok;
    qlonglong id = map[ID].toLongLong(&ok);

    if (!ok) {
        qWarning("An injection detected. The id '%s' is not numeric",
                 map[ID].toString().toLatin1().data());
        return;
    }

    if (map[MAP_TYPE] == MAP_TYPE_RESPONSE) {
        if (q->_calls[id]) {
            q->_calls[id]->returnData = map[MAP_RETURN_VALUE];
            q->_calls[id]->returnToCaller();
            // TODO flowing two lines must be test
            delete q->_calls[id];
            q->_calls.remove(id);
        }
        return;
    }

    if (!encoder->decrypt(map)) {
        qWarning("Token validation was faild! %s::%s",
                 qPrintable(map[CLASS_NAME].toString()),
                 qPrintable(map[METHOD_NAME].toString()));
        return;
    }

    QObject *target = 0;

    if (map[CLASS_NAME] == "") {
        qDebug() << map;
//        qFatal("Error in data");
    }
    if (map[CLASS_NAME] == THIS_HUB) {
        target = q;
    } else {
        target = sharedObjects.value(map[CLASS_NAME].toString());

        if (peer && !target && map[CLASS_NAME] == peer->peerName())
            target = peer;
    }

    if (!target) {
        qWarning("There are no '%s' service for method %s",
                 map[CLASS_NAME].toString().toLatin1().data(),
                 map[METHOD_NAME].toString().toLatin1().data());
        return;
    }

    QMetaMethod method;
    QGenericReturnArgument returnArgument;

    QByteArray methodName = map.value(METHOD_NAME).toByteArray();
    if (methodName == "")
        return;

    QVariant returnData;

    // find method
    for (int i = 0; i < target->metaObject()->methodCount(); i++) {
        method = target->metaObject()->method(i);
        if (method.name() == methodName) {
            const char *type = QVariant::typeToName(method.returnType());
            QString typeString = QString(type);

            if (typeString == "void") {
                returnData = QVariant(QVariant::Invalid);
            } else {
                returnData = QVariant(method.returnType(), (const void *)0);
                returnArgument = QGenericReturnArgument(
                    QMetaType::typeName(method.returnType()),
                    returnData.data());

                if (!method.returnType())
                    qWarning("%s is not registered in meta type. Did you "
                             "forget to call qRegisterMetaType?",
                             qPrintable(method.typeName()));
            }

            // TODO: why?
            /*if (q->peer())
                if (map[CLASS_NAME].toString() != q->peer()->peerName()
                    && method.parameterCount() > 0)
                    if (method.parameterType(0)
                        == QMetaType::type("NeuronPeer*"))
                        args.prepend(Q_ARG(NeuronPeer *, peer));*/

            break;
        }
    }

    if (method.name().isEmpty()) {
        qWarning("No such method %s", qPrintable(methodName));
        return;
    }
    for (int i = 0; i < 10; i++) {
        QString indexString = QString::number(i);
        if (!map.contains("val" + indexString))
            continue;

        const void *data = map["val" + indexString].data();
        const char *name = map["val" + indexString].typeName();
        args << QGenericArgument(name, data);
    }
    // FIXME: remove
    //    if (method.returnType() != QMetaType::Void) {
    //        const void *data = NULL;
    //        const char *name = QMetaType::typeName(method.returnType());
    //        args << QGenericArgument(name, data);
    //    }

    NeuronSharedObject *so = 0;
    if (q->inherits("NeuronServerHub") && target->inherits("NeuronSharedObject")) {
        so = qobject_cast<NeuronSharedObject*>(target);
        so->registerSender(target->thread(), peer);
//        args.prepend(Q_ARG(NeuronPeer *, peer));
    }

    QString lockName = map[CLASS_NAME].toString() + "::" + methodName;

    locks.insert(lockName);

    Qt::ConnectionType connectionType = Qt::DirectConnection;
    if (target->thread() != q->thread())
        connectionType = Qt::BlockingQueuedConnection;


    if (returnData.type() == QVariant::Invalid)
        ok = QMetaObject::invokeMethod(target, methodName.constData(),
                                       connectionType,
                                       args.value(0, QGenericArgument()),
                                       args.value(1, QGenericArgument()),
                                       args.value(2, QGenericArgument()),
                                       args.value(3, QGenericArgument()),
                                       args.value(4, QGenericArgument()),
                                       args.value(5, QGenericArgument()),
                                       args.value(6, QGenericArgument()),
                                       args.value(7, QGenericArgument()),
                                       args.value(8, QGenericArgument()),
                                       args.value(9, QGenericArgument()));
    else
        ok = QMetaObject::invokeMethod(target, methodName.constData(),
                                       connectionType, returnArgument,
                                       args.value(0, QGenericArgument()),
                                       args.value(1, QGenericArgument()),
                                       args.value(2, QGenericArgument()),
                                       args.value(3, QGenericArgument()),
                                       args.value(4, QGenericArgument()),
                                       args.value(5, QGenericArgument()),
                                       args.value(6, QGenericArgument()),
                                       args.value(7, QGenericArgument()),
                                       args.value(8, QGenericArgument()),
                                       args.value(9, QGenericArgument()));

    if (so)
        so->unregisterSender(target->thread());

    if (!ok) {
        qWarning("Invoke %s on %s faild", qPrintable(method.name()),
                 qPrintable(map[CLASS_NAME].toString()));
    } else {
        response(id, map[CLASS_NAME].toString(),
                 returnData.type() == QVariant::Invalid ? QVariant()
                                                        : returnData);
    }

    QObject *returnDataPointer = returnData.value<QObject *>();

    if (returnDataPointer)
        returnDataPointer->deleteLater();

    locks.remove(lockName);
}

bool NeuronAbstractHubPrivate::response(const qlonglong &id,
                                       const QString &senderName,
                                       const QVariant &returnValue)
{
    Q_Q(NeuronAbstractHub);

    //    if(socket. != NeuronAbstractHub::Connected)
    //        return false;

    QVariantMap map;
    map[MAP_TYPE] = MAP_TYPE_RESPONSE;
    map[ID] = QVariant(id);
    map[CLASS_NAME] = senderName;

    if (returnValue != QVariant())
        map[MAP_RETURN_VALUE] = returnValue;

    int res = q->socket->write(q->serializer()->serialize(map));

    return 0 != res;
}

void NeuronAbstractHubPrivate::sync()
{
    Q_Q(NeuronAbstractHub);

    if (status != NeuronAbstractHub::Connected)
        return;

    q->beginTransaction();

    NeuronPeer *peer = q->peer();

    int pcount = peer->metaObject()->propertyCount();
    for (int i = 0; i < pcount; i++) {
        QMetaProperty p = peer->metaObject()->property(i);

        if (!p.isUser())
            continue;

        QString w = p.name();
        w[0] = w[0].toUpper();

        q->invokeOnPeer(peer->peerName(), "set" + w, p.read(peer));
    }
    QMetaObject::invokeMethod(q, "commit", Qt::QueuedConnection);
    //    q->commit();
}

NeuronAbstractHub::NeuronAbstractHub(QObject *parent)
    : QObject(parent), d_ptr(new NeuronAbstractHubPrivate(this))
{
    qRegisterMetaType<Status>("NeuronAbstractHub::Status");

    socket = new QTcpSocket(this);
    K_REG_OBJECT(socket);

    connect(socket, &QIODevice::readyRead, this, &NeuronAbstractHub::socket_onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &NeuronAbstractHub::socket_disconnected);
    connect(socket, &QTcpSocket::connected, this, &NeuronAbstractHub::socket_connected);
//    connect(socket, &QTcpSocket::error, this, &NeuronAbstractHub::socket_error);

    NeuronAbstractSerializer *serializer = new NeuronJsonBinarySerializer(this);
    K_REG_OBJECT(serializer);

    setSerializer(serializer);
}

NeuronAbstractHub::NeuronAbstractHub(NeuronAbstractSerializer *serializer,
                                   QObject *parent)
    : QObject(parent), d_ptr(new NeuronAbstractHubPrivate(this))
{
    qRegisterMetaType<Status>("NeuronAbstractHub::Status");

    socket = new QTcpSocket(this);
    K_REG_OBJECT(socket);

    connect(socket, &QIODevice::readyRead, this,
            &NeuronAbstractHub::socket_onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this,
            &NeuronAbstractHub::socket_disconnected);
    connect(socket, &QTcpSocket::connected, this,
            &NeuronAbstractHub::socket_connected);

    setSerializer(serializer);
}

NeuronAbstractHub::~NeuronAbstractHub()
{
    Q_D(NeuronAbstractHub);

    // TODO: remove hub??
    //    if(peer())
    //        peer()->deleteLater();

    delete d;
}

QHash<const QString, NeuronSharedObject *>
NeuronAbstractHub::sharedObjectHash() const
{
    Q_D(const NeuronAbstractHub);
    return d->sharedObjects;
}

NeuronPeer *NeuronAbstractHub::peer() const
{
    Q_D(const NeuronAbstractHub);
    return d->peer;
}

bool NeuronAbstractHub::isConnected() const
{
    Q_D(const NeuronAbstractHub);
    return d->status == Connected;
}

NeuronAbstractSerializer *NeuronAbstractHub::serializer() const
{
    Q_D(const NeuronAbstractHub);
    return d->serializer;
}

void NeuronAbstractHub::attachSharedObject(NeuronSharedObject *o)
{
    Q_D(NeuronAbstractHub);

    if (!d->sharedObjects.contains(o->peerName())) {
        d->sharedObjects.insert(o->peerName(), o);
        o->attachHub(this);
        d->sync();
        //        qDebug() << "SharedObject" << o->objectName() << "attached to"
        //        << metaObject()->className() << objectName();
    }
}

void NeuronAbstractHub::detachSharedObject(NeuronSharedObject *o)
{
    Q_D(NeuronAbstractHub);

    if(qobject_cast<NeuronServer*>(this))
        return;

    if (d->sharedObjects.remove(o->peerName())) {
        o->detachHub(this);
        //        qDebug() << "NeuronAbstractHub::detachSharedObject" <<
        //        o->objectName() << "; " << metaObject()->className() <<
        //        objectName();
    }
}

QList<NeuronSharedObject *> NeuronAbstractHub::sharedObjects() const
{
    Q_D(const NeuronAbstractHub);
    return d->sharedObjects.values();
}

QList<NeuronSharedObject *>
NeuronAbstractHub::sharedObjects(QString peerName) const
{
    Q_D(const NeuronAbstractHub);
    return d->sharedObjects.values(peerName);
}

bool NeuronAbstractHub::isMultiThread() const
{
    Q_D(const NeuronAbstractHub);
    return d->isMultiThread;
}

NeuronAbstractHub::Status NeuronAbstractHub::status() const
{
    Q_D(const NeuronAbstractHub);
    return d->status;
}

void NeuronAbstractHub::waitForConnected(int timeout)
{
    if (socket->state() == QAbstractSocket::ConnectedState)
        return;

    QEventLoop loop;
    connect(this, &NeuronAbstractHub::connected, &loop, &QEventLoop::quit);
    QTimer::singleShot(timeout, &loop, SLOT(quit()));
    loop.exec();
}

// TODO: move this method to D
void NeuronAbstractHub::flushSocket()
{
    Q_D(NeuronAbstractHub);
    bufferMutex.lock();
    socket->write(serializer()->serialize(d->buffer));
    socket->flush();
    d->buffer.clear();
    bufferMutex.unlock();
    d->isTransaction = false;
}

#ifdef QT_QML_LIB
QJSEngine *NeuronAbstractHub::jsEngine() const
{
    Q_D(const NeuronAbstractHub);
    return d->jsEngine;
}

QQmlEngine *NeuronAbstractHub::qmlEngine() const
{
    Q_D(const NeuronAbstractHub);
    return d->qmlEngine;
}
#endif

qlonglong NeuronAbstractHub::hubId() const
{
    Q_D(const NeuronAbstractHub);
    return d->hubId;
}

void NeuronAbstractHub::setHubId(qlonglong id)
{
    Q_D(NeuronAbstractHub);

    if (d->hubId == id)
        return;

    //    invokeOnPeer(THIS_HUB, QT_STRINGIFY(setHubId), id);
    d->hubId = id;
}

void NeuronAbstractHub::socket_connected()
{
    initalizeMutex.lock();
    K_TRACE_DEBUG;
    beginConnection();

//    setStatus(NeuronAbstractHub::Connected);
    initalizeMutex.unlock();
}

void NeuronAbstractHub::socket_disconnected()
{
    qDebug() << "NeuronAbstractHub::socket_disconnected()";
    setStatus(NeuronAbstractHub::Unconnected);
    qDebug() << "NeuronAbstractHub::socket_disconnected(2)";

    // TODO:    if(isAutoReconnect()){
    //        connectToServer();
    //        d->reconnectTimerId = startTimer(500);
    //    }else
    //    {
    //        this->deleteLater();
    //    }
}

void NeuronAbstractHub::socket_onReadyRead()
{
    Q_D(NeuronAbstractHub);

    //    d->socketReadMutes.lock();

    d->readBuffer.append(socket->readAll());

    if (!d->readBuffer.size())
        return;

    QString bufferString = d->readBuffer;

    if (bufferString.endsWith("}\n")) {
        //        int bracketOpen = 0;
        //        int bracketClose = 0;
        //        for (int i = 0; i < bufferString.size(); ++i) {
        //            if(bufferString.at(i) == '{')
        //                bracketOpen++;

        //            if(bufferString.at(i) == '}')
        //                bracketClose++;
        //        }
        //        if(bracketClose != bracketOpen)
        //            return;
        if (bufferString.count('{') != bufferString.count('}'))
            return;
    } else {
        return;
    }

    //    buffer = "[" + buffer.replace("}\n{", "},{") + "]";

    QVariant var = serializer()->deserialize(
        "[" + d->readBuffer.replace("}\n{", "},{") + "]");
    d->readBuffer.clear();
    //    d->socketReadMutes.unlock();

    if (var.type() == QVariant::Map)
        d->procMap(var.toMap());

    if (var.type() == QVariant::List) {
        d->procMap(var.toList());
        //        QVariantList list = var.toList();

        //        // Check for transaction
        //        if(list.count() && list.at(0).type() == QVariant::List){
        //            QVariantList transactionListData = list.at()
        //        }

        //        foreach (QVariant map, list)
        //            d->procMap(map.toMap());
    }
}

void NeuronAbstractHub::socket_error(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    emit error();
}

void NeuronAbstractHub::beginTransaction()
{
    Q_D(NeuronAbstractHub);
    d->isTransaction = true;
}

bool NeuronAbstractHub::isTransaction() const
{
    Q_D(const NeuronAbstractHub);
    return d->isTransaction;
}

void NeuronAbstractHub::rollback()
{
    Q_D(NeuronAbstractHub);

    if (!d->isTransaction)
        return;

    bufferMutex.lock();
    d->buffer.clear();
    bufferMutex.unlock();
    d->isTransaction = false;
}

// TODO: make commit thread-safe
void NeuronAbstractHub::commit()
{
    Q_D(NeuronAbstractHub);

    if (!d->isTransaction)
        return;

    if (status() != Connected)
        return;

    if (!socket->isOpen())
        return;

    QMetaObject::invokeMethod(this, "flushSocket");
}

// TODO: remove val8, val9
qlonglong NeuronAbstractHub::invokeOnPeer(QString sender, QString methodName,
                                         QVariant val0, QVariant val1,
                                         QVariant val2, QVariant val3,
                                         QVariant val4, QVariant val5,
                                         QVariant val6, QVariant val7,
                                         QVariant val8, QVariant val9)
{
    Q_D(NeuronAbstractHub);
    if (d->locks.contains(sender + "::" + methodName))
        return 0;

    if (/*d->status != Connected || */ !socket->isOpen()) {
        qWarning("Socket is closed");
        return 0;
    }

    if (d->requestId++ >= MAX - 1)
        d->requestId = 0;

    QVariantMap map;
    map[ID] = QVariant(d->requestId);
    map[METHOD_NAME] = methodName;
    map[MAP_TYPE] = MAP_TYPE_REQUEST;
    map[CLASS_NAME] = sender;

    d->addToMap(&map, val0, 0);
    d->addToMap(&map, val1, 1);
    d->addToMap(&map, val2, 2);
    d->addToMap(&map, val3, 3);
    d->addToMap(&map, val4, 4);
    d->addToMap(&map, val5, 5);
    d->addToMap(&map, val6, 6);
    d->addToMap(&map, val7, 7);
    d->addToMap(&map, val8, 8);
    d->addToMap(&map, val9, 9);

    d->encoder->encrypt(map);

    if (d->isTransaction) {
        bufferMutex.lock();
        d->buffer.append(map);
        bufferMutex.unlock();
        return 0;
    } else {
        qint64 res = socket->write(serializer()->serialize(map));
        return res == 0 ? 0 : d->requestId;
    }
}

void NeuronAbstractHub::setPeer(NeuronPeer *peer)
{
    Q_D(NeuronAbstractHub);

    if (d->peer == peer)
        return;

    d->peer = peer;
    d->sync();
    emit peerChanged(peer);
}

void NeuronAbstractHub::setSerializer(NeuronAbstractSerializer *serializer)
{
    Q_D(NeuronAbstractHub);

    if (d->serializer == serializer)
        return;

    d->serializer = serializer;
    emit serializerChanged(serializer);
}

#ifdef QT_QML_LIB
void NeuronAbstractHub::setJsEngine(QJSEngine *engine)
{
    Q_D(NeuronAbstractHub);

    if (d->jsEngine == engine)
        return;

    d->jsEngine = engine;
    emit jsEngineChanged(engine);
}

void NeuronAbstractHub::setQmlEngine(QQmlEngine *qmlEngine)
{
    Q_D(NeuronAbstractHub);

    if (d->qmlEngine == qmlEngine)
        return;

    d->qmlEngine = qmlEngine;
    emit qmlEngineChanged(qmlEngine);
}
#endif

void NeuronAbstractHub::beginConnection()
{
}

void NeuronAbstractHub::setIsMultiThread(bool isMultiThread)
{
    Q_D(NeuronAbstractHub);
    d->isMultiThread = isMultiThread;
}

void NeuronAbstractHub::setStatus(NeuronAbstractHub::Status status)
{
    Q_D(NeuronAbstractHub);

    if (d->status == status)
        return;

    d->status = status;

    switch(status) {
    case Connected:
        emit connected();
        break;

    case Unconnected:
        emit disconnected();
        break;

    case Reconnecting:
        qt_noop();
        break;
    }

    emit statusChanged(status);
}

NeuronAbstractDataEncoder *NeuronAbstractHub::encoder() const
{
    Q_D(const NeuronAbstractHub);
    return d->encoder;
}

void NeuronAbstractHub::setEncoder(NeuronAbstractDataEncoder *encoder)
{
    Q_D(NeuronAbstractHub);

    if (d->encoder == encoder)
        return;

    d->encoder = encoder;
    emit encoderChanged(d->encoder);
}
NEURON_END_NAMESPACE
