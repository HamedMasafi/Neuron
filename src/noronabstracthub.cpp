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

#include <QtCore/QCryptographicHash>
#include <QtCore/QJsonDocument>
#include <QtCore/QSet>
#include <QtCore/QVariant>
#include <QtNetwork/QTcpSocket>

#include "noronpeer.h"
#include "noronabstracthub_p.h"
#include "noronabstracthub.h"
#include "noronabstractserializer.h"
#include "noronremotecall_p.h"
#include "noronsharedobject.h"
#include "noronjsonbinaryserializer.h"

QT_BEGIN_NAMESPACE

NoronAbstractHubPrivate::NoronAbstractHubPrivate(NoronAbstractHub *parent) : q_ptr(parent),
    peer(0), isConnected(false), validateToken(QString::null), serializer(0), requestId(0),
    isTransaction(false)
{

}

void NoronAbstractHubPrivate::addToMap(QVariantMap *map, QVariant var, int index)
{
    if(var != QVariant()){
        QString i = QString::number(index);
        map->insert("val" + i, var);
    }
}

void NoronAbstractHubPrivate::procMap(QVariantMap map)
{
    Q_Q(NoronAbstractHub);

    bool ok;
    qlonglong id = map[ID].toLongLong(&ok);

    if(!ok){
        qWarning("An injection detected. The id '" + map[ID].toString().toLatin1() + "' is not numeric");
        return;
    }

    if(map[MAP_TYPE] == MAP_TYPE_RESPONSE){
        if(q->_calls[id]){
            q->_calls[id]->returnData = map[MAP_RETURN_VALUE];
            q->_calls[id]->returnToCaller();
        }
        return;
    }

    if(!q->validateToken().isNull())
        if(!checkValidateToken(&map)){
            qWarning("Token validation was faild!");
            return;
        }

    QObject *target = sharedObjects[map[CLASS_NAME].toString()];

    if(!target && map[CLASS_NAME] == q->peer()->metaObject()->className())
        target = q->peer();

    if(!target){
        qWarning("There are no '" + map[CLASS_NAME].toString().toLatin1() + "' service");
        return;
    }

    QMetaMethod method;
    QGenericReturnArgument returnArgument;

    QByteArray methodName = map.value(METHOD_NAME).toByteArray();
    if(methodName == "")
        return;

    QVariant returnData = QVariant("");

    // find method
    for(int i = 0; i < target->metaObject()->methodCount(); i++){
        method = target->metaObject()->method(i);
        if(method.name() == methodName){
            const char* type = QVariant::typeToName(method.returnType());
            QVariant::Type returnType = QVariant::nameToType(type);
            returnData.convert(returnType);
            returnArgument = QGenericReturnArgument(type, &returnData);

            if(QString(type) == "void")
                returnData = QVariant(QVariant::Invalid);

            break;
        }
    }

    if(method.name().isEmpty())
        return;

    QList<QGenericArgument> args;
    for(int i = 0; i < 10; i++){
        QString indexString = QString::number(i);
        if(!map.contains("val" + indexString))
            continue;

        const void *data = map["val" + indexString].data();
        const char *name = map["val" + indexString].typeName();
        args << QGenericArgument(name, data);
    }

    QString lockName = map[CLASS_NAME].toString() + "::" + methodName;

    locks.insert(lockName);

    if(returnData.type() == QVariant::Invalid)
        ok = QMetaObject::invokeMethod(
                    target,
                    methodName.constData(),
                    Qt::DirectConnection,
                    args.value(0, QGenericArgument() ),
                    args.value(1, QGenericArgument() ),
                    args.value(2, QGenericArgument() ),
                    args.value(3, QGenericArgument() ),
                    args.value(4, QGenericArgument() ),
                    args.value(5, QGenericArgument() ),
                    args.value(6, QGenericArgument() ),
                    args.value(7, QGenericArgument() ),
                    args.value(8, QGenericArgument() ),
                    args.value(9, QGenericArgument() ));
    else
        ok = QMetaObject::invokeMethod(
                    target,
                    methodName.constData(),
                    Qt::DirectConnection,
                    returnArgument,
                    args.value(0, QGenericArgument() ),
                    args.value(1, QGenericArgument() ),
                    args.value(2, QGenericArgument() ),
                    args.value(3, QGenericArgument() ),
                    args.value(4, QGenericArgument() ),
                    args.value(5, QGenericArgument() ),
                    args.value(6, QGenericArgument() ),
                    args.value(7, QGenericArgument() ),
                    args.value(8, QGenericArgument() ),
                    args.value(9, QGenericArgument() ));

    if(!ok)
        qWarning("Invoke " + method.name() + " on " + map[CLASS_NAME].toString().toLatin1() + " faild");
    else
        response(id,
                 map[CLASS_NAME].toString(),
                 returnData.type() == QVariant::Invalid
                    ? QVariant()
                    : returnData);

    QObject *returnDataPointer = returnData.value<QObject*>();

    if(returnDataPointer)
        returnDataPointer->deleteLater();

    locks.remove(lockName);
}

bool NoronAbstractHubPrivate::response(qlonglong id, QString senderName, QVariant returnValue)
{
    Q_Q(NoronAbstractHub);

    QVariantMap map;
    map[MAP_TYPE] = MAP_TYPE_RESPONSE;
    map[ID] = QVariant(id);
    map[CLASS_NAME] = senderName;

    if(returnValue != QVariant())
        map[MAP_RETURN_VALUE] = returnValue;

    int res = q->socket->write(q->serializer()->serialize(map));

    return 0 != res;
}

void NoronAbstractHubPrivate::addValidateToken(QVariantMap *map)
{
    Q_Q(NoronAbstractHub);

    QByteArray s;

    map->insert(MAP_TOKEN_ITEM, QVariant(""));

    QMapIterator<QString, QVariant> i(*map);
    while (i.hasNext()) {
        i.next();
        s.append(i.key() + ": " + i.value().toString() + "*");
    }

    map->insert(MAP_TOKEN_ITEM, QVariant(MD5(s + q->validateToken())));
}

bool NoronAbstractHubPrivate::checkValidateToken(QVariantMap *map)
{
    Q_Q(NoronAbstractHub);

    QString token = map->value(MAP_TOKEN_ITEM).toString();
    map->insert(MAP_TOKEN_ITEM, QVariant(""));

    QByteArray s;

    QMapIterator<QString, QVariant> i(*map);
    while (i.hasNext()) {
        i.next();
        s.append(i.key() + ": " + i.value().toString() + "*");
    }

    return token == MD5(s + q->validateToken());
}

QString NoronAbstractHubPrivate::MD5(QString text)
{
    return MD5(text.toLocal8Bit());
}

QString NoronAbstractHubPrivate::MD5(QByteArray text)
{
    return QString(QCryptographicHash::hash(text, QCryptographicHash::Md5).toHex());
}

NoronAbstractHub::NoronAbstractHub(QObject *parent) : QObject(parent),
    d_ptr(new NoronAbstractHubPrivate(this)), _isMultiThread(false)
{
    socket = new QTcpSocket(this);

    connect(socket, &QIODevice::readyRead, this, &NoronAbstractHub::socket_onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &NoronAbstractHub::socket_disconnected);
    connect(socket, &QTcpSocket::connected, this, &NoronAbstractHub::socket_connected);

    setSerializer(new NoronJsonBinarySerializer(this));
}

NoronPeer *NoronAbstractHub::peer() const
{
    Q_D(const NoronAbstractHub);
    return d->peer;
}

bool NoronAbstractHub::isConnected() const
{
    Q_D(const NoronAbstractHub);
    return d->isConnected;
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

void NoronAbstractHub::addSharedObject(NoronSharedObject *o)
{
    Q_D(NoronAbstractHub);

    o->addHub(this);
    d->sharedObjects[o->metaObject()->className()] = o;
}

void NoronAbstractHub::removeSharedObject(NoronSharedObject *o)
{
    Q_D(NoronAbstractHub);

    if(d->sharedObjects.contains(o->metaObject()->className())){
        o->removeHub(this);
        d->sharedObjects.remove(o->metaObject()->className());
    }
}

QList<NoronSharedObject *> NoronAbstractHub::sharedObjects() const
{
    Q_D(const NoronAbstractHub);
    return d->sharedObjects.values();
}

bool NoronAbstractHub::isMultiThread() const
{
    return _isMultiThread;
}

void NoronAbstractHub::socket_connected()
{
    setIsConnected(true);
}

void NoronAbstractHub::socket_disconnected()
{
    setIsConnected(false);
    emit disconnected();

//TODO:    if(isAutoReconnect()){
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

    QByteArray buffer = socket->readAll();
    //multi chunck support
    buffer = "[" + buffer.replace("}\n{", "},{") + "]";

    QVariant var = serializer()->deserialize(buffer);

    if(var.type() == QVariant::Map)
        d->procMap(var.toMap());

    if(var.type() == QVariant::List){
        QVariantList list = var.toList();
        foreach (QVariant map, list){
            d->procMap(map.toMap());
        }
    }
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

    if(!d->isTransaction)
        return;

    d->buffer.clear();
    d->isTransaction = false;
}

void NoronAbstractHub::commit()
{
    Q_D(NoronAbstractHub);

    if(!d->isTransaction)
        return;

    socket->write(serializer()->serialize(d->buffer));
    socket->flush();
    d->buffer.clear();
    d->isTransaction = false;
}

qlonglong NoronAbstractHub::invokeOnPeer(QString sender, QString methodName, QVariant val0, QVariant val1, QVariant val2, QVariant val3, QVariant val4, QVariant val5, QVariant val6, QVariant val7, QVariant val8, QVariant val9)
{
    Q_D(NoronAbstractHub);

    if(d->locks.contains(sender + "::" + methodName))
        return 0;

    if(d->requestId++ >= LONG_LONG_MAX - 1)
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

    if(!validateToken().isNull())
        d->addValidateToken(&map);

    if(d->isTransaction){
        d->buffer.append(map);
        return 0;
    }else{
        int res = socket->write(serializer()->serialize(map));
        return res == 0 ? 0 : d->requestId;
    }
}

void NoronAbstractHub::setPeer(NoronPeer *peer)
{
    Q_D(NoronAbstractHub);

    if (d->peer == peer)
        return;

    d->peer = peer;
    emit peerChanged(peer);
}

void NoronAbstractHub::setIsConnected(bool isConnected)
{
    Q_D(NoronAbstractHub);

    if (d->isConnected == isConnected)
        return;

    d->isConnected = isConnected;
    emit isConnectedChanged(isConnected);
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

QT_END_NAMESPACE
