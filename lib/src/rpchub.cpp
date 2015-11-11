#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaMethod>
#include <QCryptographicHash>

#include "rpchub.h"
#include "rpchub_p.h"
#include "rpcpeer.h"
#include "rpcjsondataserializer.h"

QT_BEGIN_NAMESPACE

RpcHubPrivate::RpcHubPrivate(RpcHub *parent) : q_ptr(parent),
    isTransaction(false), requestId(0)
{

}

void RpcHubPrivate::addToMap(QVariantMap *map, QVariant var, int index)
{

    QString i = QString::number(index);

    if(var != QVariant()){
        map->insert("val" + i, var);
        //        map->insert("type" + i, var.typeName());
    }
}

void RpcHubPrivate::procMap(QVariantMap map)
{
    Q_Q(RpcHub);

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
            qWarning("Map token validate is invalid!");
            return;
        }

    QObject *target = q->_classes[map[CLASS_NAME].toString()];

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
        response(id, map[CLASS_NAME].toString(),
                 returnData.type() == QVariant::Invalid ? QVariant() : returnData);

    locks.remove(lockName);
}

bool RpcHubPrivate::response(qlonglong id, QString senderName, QVariant returnValue)
{
    Q_Q(RpcHub);

    QVariantMap map;
    map[MAP_TYPE] = MAP_TYPE_RESPONSE;
    map[ID] = QVariant(id);
    map[CLASS_NAME] = senderName;

    if(returnValue != QVariant())
        map[MAP_RETURN_VALUE] = returnValue;

    int res = socket->write(q->serializer()->serialize(map));

    return 0 != res;
}

void RpcHubPrivate::addValidateToken(QVariantMap *map)
{
    Q_Q(RpcHub);

    QByteArray s;

    map->insert(MAP_TOKEN_ITEM, QVariant(""));

    QMapIterator<QString, QVariant> i(*map);
    while (i.hasNext()) {
        i.next();
        s.append(i.key() + ": " + i.value().toString() + "*");
    }

    map->insert(MAP_TOKEN_ITEM, QVariant(MD5(s + q->validateToken())));
}

bool RpcHubPrivate::checkValidateToken(QVariantMap *map)
{
    Q_Q(RpcHub);

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

QString RpcHubPrivate::MD5(QString text)
{
    return MD5(text.toLocal8Bit());
}

QString RpcHubPrivate::MD5(QByteArray text)
{
    return QString(QCryptographicHash::hash(text, QCryptographicHash::Md5).toHex());
}

RpcHub::RpcHub(QObject *parent) : RpcHubBase(parent),
    d_ptr(new RpcHubPrivate(this))
{
    Q_D(RpcHub);

    d->socket = new QTcpSocket(this);

    connect(d->socket, &QIODevice::readyRead, this, &RpcHub::socket_onReadyRead);
    connect(d->socket, &QTcpSocket::disconnected, this, &RpcHub::socket_disconnected);
    connect(d->socket, &QTcpSocket::connected, this, &RpcHub::socket_connected);

    setSerializer(new RpcJsonDataSerializer(this));
}

RpcHub::RpcHub(RpcSerializerBase *serializer, QObject *parent) : RpcHubBase(parent),
    d_ptr(new RpcHubPrivate(this))
{
    Q_D(RpcHub);

    d->socket = new QTcpSocket(this);

    connect(d->socket, &QIODevice::readyRead, this, &RpcHub::socket_onReadyRead);
    connect(d->socket, &QTcpSocket::disconnected, this, &RpcHub::socket_disconnected);
    connect(d->socket, &QTcpSocket::connected, this, &RpcHub::socket_connected);

    setSerializer(serializer);
}

RpcHub::~RpcHub()
{
    foreach (QObject *o, _classes) {
        RpcPeer *peer = qobject_cast<RpcPeer*>(o);
        if(peer->hub() == this)
            o->deleteLater();
    }
}

void RpcHub::connectToServer(QString address, qint16 port)
{
    Q_D(RpcHub);

    if(!address.isNull())
        setServerAddress(address);

    if(port)
        setPort(port);

    d->socket->connectToHost(this->serverAddress(), this->port());
}

void RpcHub::disconnectFromServer()
{
    Q_D(RpcHub);

    setAutoReconnect(false);
    d->socket->disconnectFromHost();
}

bool RpcHub::setSocketDescriptor(qintptr socketDescriptor)
{
    Q_D(RpcHub);
    return d->socket->setSocketDescriptor(socketDescriptor);
}

void RpcHub::timerEvent(QTimerEvent *)
{
    Q_D(RpcHub);

    if(d->socket->state() == QAbstractSocket::UnconnectedState){
        connectToServer();
    }else if(d->socket->state() == QAbstractSocket::ConnectedState){
        killTimer(d->reconnectTimerId);

        sync();
    }
}

void RpcHub::sync()
{
    beginTransaction();
    foreach (QObject *o, _classes) {

        int pcount = o->metaObject()->propertyCount();
        for(int i = 0; i < pcount; i++){
            QMetaProperty p = o->metaObject()->property(i);

            if(!p.isUser())
                continue;

            QString w = p.name();
            w[0] = w[0].toUpper();
            invokeOnPeer(o->metaObject()->className(),
                         "set" + w,
                         p.read(o));
        }
    }
    commit();
}

void RpcHub::beginTransaction()
{
    Q_D(RpcHub);
    d->isTransaction = true;
}

bool RpcHub::isTransaction() const
{
    Q_D(const RpcHub);
    return d->isTransaction;
}

void RpcHub::rollback()
{
    Q_D(RpcHub);
    d->buffer.clear();
    d->isTransaction = false;
}

void RpcHub::commit()
{
    Q_D(RpcHub);
    d->socket->write(QJsonDocument::fromVariant(d->buffer).toJson());
    d->socket->flush();
    d->buffer.clear();
    d->isTransaction = false;
}

void RpcHub::socket_connected()
{
    setIsConnected(true);
}

void RpcHub::socket_disconnected()
{
    Q_D(RpcHub);

    setIsConnected(false);

    if(autoReconnect()){
        connectToServer();
        d->reconnectTimerId = startTimer(500);
    }else{
        this->deleteLater();
    }
}

void RpcHub::socket_onReadyRead()
{
    Q_D(RpcHub);

    QByteArray buffer = d->socket->readAll();
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

qlonglong RpcHub::invokeOnPeer(QString sender, QString methodName,
                               QVariant val0, QVariant val1,
                               QVariant val2, QVariant val3,
                               QVariant val4, QVariant val5,
                               QVariant val6, QVariant val7,
                               QVariant val8, QVariant val9)
{
    Q_D(RpcHub);

    if(d->locks.contains(sender + "::" + methodName))
        return 0;

    if(d->requestId++ >= LONG_LONG_MAX - 1)
        d->requestId = 0;

    QVariantMap map;
    map[METHOD_NAME] = methodName;
    map[MAP_TYPE] = MAP_TYPE_REQUEST;
    map[ID] = QVariant(d->requestId);
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
        int res = d->socket->write(serializer()->serialize(map));

        if(res == 0)
            return 0;
        else
            return d->requestId;
    }
}

QT_END_NAMESPACE
