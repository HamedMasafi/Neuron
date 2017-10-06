/**************************************************************************
**
** This file is part of Noron.
** https://github.com/HamedMasafi/Noron
**
** Noron is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Noron is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Noron.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#include <NoronServer>
#include <QTimer>
#include <QtCore/QCryptographicHash>
#include <QtCore/QJsonDocument>
#include <QtCore/QSet>
#include <QtCore/QVariant>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>

#ifdef QT_QML_LIB
#include <QtQml/QJSEngine>
#endif

#include "noronpeer.h"
#include "noronabstracthub_p.h"
#include "noronabstracthub.h"
#include "noronabstractserializer.h"
#include "noronremotecall_p.h"
#include "noronsharedobject.h"
#include "noronjsonbinaryserializer.h"

#ifdef LONG_LONG_MAX
#define MAX LONG_LONG_MAX
#elif defined(LONG_MAX)
#define MAX LONG_MAX
#else
#error "No LONG_LONG_MAX nor LONG_MAX is defined"
#endif

NORON_BEGIN_NAMESPACE

NoronAbstractHubPrivate::NoronAbstractHubPrivate(NoronAbstractHub *parent)
    : q_ptr(parent), peer(0), validateToken(QString::null), serializer(0),
      requestId(0), isTransaction(false), isMultiThread(false), hubId(0),
      status(NoronAbstractHub::Unconnected)
#ifdef QT_QML_LIB
      ,
      jsEngine(0), qmlEngine(0)
#endif
{
}

void NoronAbstractHubPrivate::addToMap(QVariantMap *map, QVariant var,
                                       int index)
{
    if (var != QVariant()) {
        QString i = QString::number(index);
        map->insert("val" + i, var);
    }
}

void NoronAbstractHubPrivate::procMap(QVariantList list)
{
    foreach (QVariant v, list) {
        if (v.type() == QVariant::Map)
            procMap(v.toMap());
        else if (v.type() == QVariant::List)
            procMap(v.toList());
    }
}

void NoronAbstractHubPrivate::procMap(QVariantMap map)
{
    Q_Q(NoronAbstractHub);

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
    if (!q->validateToken().isNull())
        if (!checkValidateToken(map)) {
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
                        == QMetaType::type("NoronPeer*"))
                        args.prepend(Q_ARG(NoronPeer *, peer));*/

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

    if (q->inherits("NoronServerHub") && target->inherits("NoronSharedObject"))
        args.prepend(Q_ARG(NoronPeer *, peer));

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

bool NoronAbstractHubPrivate::response(const qlonglong &id,
                                       const QString &senderName,
                                       const QVariant &returnValue)
{
    Q_Q(NoronAbstractHub);

    //    if(socket. != NoronAbstractHub::Connected)
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

QString NoronAbstractHubPrivate::createValidateToken(QVariantMap &map)
{
    Q_Q(NoronAbstractHub);

    QString s = "";
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();

        QMetaType t(i.value().userType());

        bool ok;
        if (t.flags() & QMetaType::PointerToQObject)
            s.append(i.key() + ": " + i.value().typeName() + "*");
        else if (t.flags() & QMetaType::IsEnumeration)
            s.append(i.key() + ": " + i.value().toInt(&ok) + "*");
        else
            s.append(i.key() + ": " + i.value().toString() + "*");
    }

    return MD5(s + q->validateToken());
}

void NoronAbstractHubPrivate::addValidateToken(QVariantMap &map)
{
    map.insert(MAP_TOKEN_ITEM, QVariant(""));
    map.insert(MAP_TOKEN_ITEM, createValidateToken(map));
}

bool NoronAbstractHubPrivate::checkValidateToken(QVariantMap &map)
{
    QString token = map.value(MAP_TOKEN_ITEM).toString();
    map.insert(MAP_TOKEN_ITEM, QVariant(""));

    QString validateToken = createValidateToken(map);

    return token == validateToken;
}

QString NoronAbstractHubPrivate::MD5(const QString &text)
{
    return MD5(text.toLocal8Bit());
}

QString NoronAbstractHubPrivate::MD5(QByteArray text)
{
    return QString(
        QCryptographicHash::hash(text, QCryptographicHash::Md5).toHex());
}

void NoronAbstractHubPrivate::sync()
{
    Q_Q(NoronAbstractHub);

    if (status != NoronAbstractHub::Connected)
        return;

    q->beginTransaction();

    NoronPeer *peer = q->peer();

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

NoronAbstractHub::NoronAbstractHub(QObject *parent)
    : QObject(parent), d_ptr(new NoronAbstractHubPrivate(this))
{
    qRegisterMetaType<Status>();

    socket = new QTcpSocket(this);
    K_REG_OBJECT(socket);

    connect(socket, &QIODevice::readyRead, this, &NoronAbstractHub::socket_onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &NoronAbstractHub::socket_disconnected);
    connect(socket, &QTcpSocket::connected, this, &NoronAbstractHub::socket_connected);
//    connect(socket, &QTcpSocket::error, this, &NoronAbstractHub::socket_error);

    NoronAbstractSerializer *serializer = new NoronJsonBinarySerializer(this);
    K_REG_OBJECT(serializer);

    setSerializer(serializer);
}

NoronAbstractHub::NoronAbstractHub(NoronAbstractSerializer *serializer,
                                   QObject *parent)
    : QObject(parent), d_ptr(new NoronAbstractHubPrivate(this))
{
    qRegisterMetaType<Status>();

    socket = new QTcpSocket(this);
    K_REG_OBJECT(socket);

    connect(socket, &QIODevice::readyRead, this,
            &NoronAbstractHub::socket_onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this,
            &NoronAbstractHub::socket_disconnected);
    connect(socket, &QTcpSocket::connected, this,
            &NoronAbstractHub::socket_connected);

    setSerializer(serializer);
}

NoronAbstractHub::~NoronAbstractHub()
{
    Q_D(NoronAbstractHub);

    // TODO: remove hub??
    //    if(peer())
    //        peer()->deleteLater();

    delete d;
}

QHash<const QString, NoronSharedObject *>
NoronAbstractHub::sharedObjectHash() const
{
    Q_D(const NoronAbstractHub);
    return d->sharedObjects;
}

NoronPeer *NoronAbstractHub::peer() const
{
    Q_D(const NoronAbstractHub);
    return d->peer;
}

bool NoronAbstractHub::isConnected() const
{
    Q_D(const NoronAbstractHub);
    return d->status == Connected;
}

QString NoronAbstractHub::validateToken() const
{
    Q_D(const NoronAbstractHub);
    return d->validateToken;
}

NoronAbstractSerializer *NoronAbstractHub::serializer() const
{
    Q_D(const NoronAbstractHub);
    return d->serializer;
}

void NoronAbstractHub::attachSharedObject(NoronSharedObject *o)
{
    Q_D(NoronAbstractHub);

    if (!d->sharedObjects.contains(o->peerName())) {
        d->sharedObjects.insert(o->peerName(), o);
        o->attachHub(this);
        d->sync();
        //        qDebug() << "SharedObject" << o->objectName() << "attached to"
        //        << metaObject()->className() << objectName();
    }
}

void NoronAbstractHub::detachSharedObject(NoronSharedObject *o)
{
    Q_D(NoronAbstractHub);

    if(qobject_cast<NoronServer*>(this))
        return;

    if (d->sharedObjects.remove(o->peerName())) {
        o->detachHub(this);
        //        qDebug() << "NoronAbstractHub::detachSharedObject" <<
        //        o->objectName() << "; " << metaObject()->className() <<
        //        objectName();
    }
}

QList<NoronSharedObject *> NoronAbstractHub::sharedObjects() const
{
    Q_D(const NoronAbstractHub);
    return d->sharedObjects.values();
}

QList<NoronSharedObject *>
NoronAbstractHub::sharedObjects(QString peerName) const
{
    Q_D(const NoronAbstractHub);
    return d->sharedObjects.values(peerName);
}

bool NoronAbstractHub::isMultiThread() const
{
    Q_D(const NoronAbstractHub);
    return d->isMultiThread;
}

NoronAbstractHub::Status NoronAbstractHub::status() const
{
    Q_D(const NoronAbstractHub);
    return d->status;
}

void NoronAbstractHub::waitForConnected(int timeout)
{
    if (socket->state() == QAbstractSocket::ConnectedState)
        return;

    QEventLoop loop;
    connect(this, &NoronAbstractHub::connected, &loop, &QEventLoop::quit);
    QTimer::singleShot(timeout, &loop, SLOT(quit()));
    loop.exec();
}

// TODO: move this method to D
void NoronAbstractHub::flushSocket()
{
    Q_D(NoronAbstractHub);
    bufferMutex.lock();
    socket->write(serializer()->serialize(d->buffer));
    socket->flush();
    d->buffer.clear();
    bufferMutex.unlock();
    d->isTransaction = false;
}

#ifdef QT_QML_LIB
QJSEngine *NoronAbstractHub::jsEngine() const
{
    Q_D(const NoronAbstractHub);
    return d->jsEngine;
}

QQmlEngine *NoronAbstractHub::qmlEngine() const
{
    Q_D(const NoronAbstractHub);
    return d->qmlEngine;
}
#endif

qlonglong NoronAbstractHub::hubId() const
{
    Q_D(const NoronAbstractHub);
    return d->hubId;
}

void NoronAbstractHub::setHubId(qlonglong id)
{
    Q_D(NoronAbstractHub);

    if (d->hubId == id)
        return;

    //    invokeOnPeer(THIS_HUB, QT_STRINGIFY(setHubId), id);
    d->hubId = id;
}

void NoronAbstractHub::socket_connected()
{
    initalizeMutex.lock();
    K_TRACE_DEBUG;
    beginConnection();

//    setStatus(NoronAbstractHub::Connected);
    initalizeMutex.unlock();
}

void NoronAbstractHub::socket_disconnected()
{
    qDebug() << "NoronAbstractHub::socket_disconnected()";
    setStatus(NoronAbstractHub::Unconnected);
    qDebug() << "NoronAbstractHub::socket_disconnected(2)";

    // TODO:    if(isAutoReconnect()){
    //        connectToServer();
    //        d->reconnectTimerId = startTimer(500);
    //    }else
    //    {
    //        this->deleteLater();
    //    }
}

void NoronAbstractHub::socket_onReadyRead()
{
    Q_D(NoronAbstractHub);

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

void NoronAbstractHub::socket_error(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    emit error();
}

void NoronAbstractHub::beginTransaction()
{
    Q_D(NoronAbstractHub);
    d->isTransaction = true;
}

bool NoronAbstractHub::isTransaction() const
{
    Q_D(const NoronAbstractHub);
    return d->isTransaction;
}

void NoronAbstractHub::rollback()
{
    Q_D(NoronAbstractHub);

    if (!d->isTransaction)
        return;

    bufferMutex.lock();
    d->buffer.clear();
    bufferMutex.unlock();
    d->isTransaction = false;
}

// TODO: make commit thread-safe
void NoronAbstractHub::commit()
{
    Q_D(NoronAbstractHub);

    if (!d->isTransaction)
        return;

    if (status() != Connected)
        return;

    if (!socket->isOpen())
        return;

    QMetaObject::invokeMethod(this, "flushSocket");
}

// TODO: remove val8, val9
qlonglong NoronAbstractHub::invokeOnPeer(QString sender, QString methodName,
                                         QVariant val0, QVariant val1,
                                         QVariant val2, QVariant val3,
                                         QVariant val4, QVariant val5,
                                         QVariant val6, QVariant val7,
                                         QVariant val8, QVariant val9)
{
    Q_D(NoronAbstractHub);
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

    if (!validateToken().isNull())
        d->addValidateToken(map);

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

void NoronAbstractHub::setPeer(NoronPeer *peer)
{
    Q_D(NoronAbstractHub);

    if (d->peer == peer)
        return;

    d->peer = peer;
    d->sync();
    emit peerChanged(peer);
}

void NoronAbstractHub::setValidateToken(QString validateToken)
{
    Q_D(NoronAbstractHub);

    if (d->validateToken == validateToken)
        return;

    d->validateToken = validateToken;
    emit validateTokenChanged(validateToken);
}

void NoronAbstractHub::setSerializer(NoronAbstractSerializer *serializer)
{
    Q_D(NoronAbstractHub);

    if (d->serializer == serializer)
        return;

    d->serializer = serializer;
    emit serializerChanged(serializer);
}

#ifdef QT_QML_LIB
void NoronAbstractHub::setJsEngine(QJSEngine *engine)
{
    Q_D(NoronAbstractHub);

    if (d->jsEngine == engine)
        return;

    d->jsEngine = engine;
    emit jsEngineChanged(engine);
}

void NoronAbstractHub::setQmlEngine(QQmlEngine *qmlEngine)
{
    Q_D(NoronAbstractHub);

    if (d->qmlEngine == qmlEngine)
        return;

    d->qmlEngine = qmlEngine;
    emit qmlEngineChanged(qmlEngine);
}
#endif

void NoronAbstractHub::beginConnection()
{
}

void NoronAbstractHub::setIsMultiThread(bool isMultiThread)
{
    Q_D(NoronAbstractHub);
    d->isMultiThread = isMultiThread;
}

void NoronAbstractHub::setStatus(NoronAbstractHub::Status status)
{
    Q_D(NoronAbstractHub);

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

NORON_END_NAMESPACE
