#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaMethod>
#include <QCryptographicHash>

#include "noronhub.h"
#include "noronhub_p.h"
#include "noronpeer.h"
#include "noronjsondataserializer.h"

QT_BEGIN_NAMESPACE

NoronHubPrivate::NoronHubPrivate(NoronHub *parent) : q_ptr(parent),
    isTransaction(false), requestId(0)
{

}

void NoronHubPrivate::addToMap(QVariantMap *map, QVariant var, int index)
{

    QString i = QString::number(index);

    if(var != QVariant()){
        map->insert("val" + i, var);
        //        map->insert("type" + i, var.typeName());
    }
}

void NoronHubPrivate::procMap(QVariantMap map)
{
    Q_Q(NoronHub);

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

bool NoronHubPrivate::response(qlonglong id, QString senderName, QVariant returnValue)
{
    Q_Q(NoronHub);

    QVariantMap map;
    map[MAP_TYPE] = MAP_TYPE_RESPONSE;
    map[ID] = QVariant(id);
    map[CLASS_NAME] = senderName;

    if(returnValue != QVariant())
        map[MAP_RETURN_VALUE] = returnValue;

    int res = socket->write(q->serializer()->serialize(map));

    return 0 != res;
}

void NoronHubPrivate::addValidateToken(QVariantMap *map)
{
    Q_Q(NoronHub);

    QByteArray s;

    map->insert(MAP_TOKEN_ITEM, QVariant(""));

    QMapIterator<QString, QVariant> i(*map);
    while (i.hasNext()) {
        i.next();
        s.append(i.key() + ": " + i.value().toString() + "*");
    }

    map->insert(MAP_TOKEN_ITEM, QVariant(MD5(s + q->validateToken())));
}

bool NoronHubPrivate::checkValidateToken(QVariantMap *map)
{
    Q_Q(NoronHub);

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

QString NoronHubPrivate::MD5(QString text)
{
    return MD5(text.toLocal8Bit());
}

QString NoronHubPrivate::MD5(QByteArray text)
{
    return QString(QCryptographicHash::hash(text, QCryptographicHash::Md5).toHex());
}

NoronHub::NoronHub(QObject *parent) : NoronHubBase(parent),
    d_ptr(new NoronHubPrivate(this))
{
    Q_D(NoronHub);

    d->socket = new QTcpSocket(this);

    connect(d->socket, &QIODevice::readyRead, this, &NoronHub::socket_onReadyRead);
    connect(d->socket, &QTcpSocket::disconnected, this, &NoronHub::socket_disconnected);
    connect(d->socket, &QTcpSocket::connected, this, &NoronHub::socket_connected);

    setSerializer(new NoronJsonDataSerializer(this));
}

NoronHub::NoronHub(NoronSerializerBase *serializer, QObject *parent) : NoronHubBase(parent),
    d_ptr(new NoronHubPrivate(this))
{
    Q_D(NoronHub);

    d->socket = new QTcpSocket(this);

    connect(d->socket, &QIODevice::readyRead, this, &NoronHub::socket_onReadyRead);
    connect(d->socket, &QTcpSocket::disconnected, this, &NoronHub::socket_disconnected);
    connect(d->socket, &QTcpSocket::connected, this, &NoronHub::socket_connected);

    setSerializer(serializer);
}

NoronHub::~NoronHub()
{
    foreach (NoronPeer *peer, _classes.values()) {
        if(peer->hub() == this)
            peer->deleteLater();
    }
}

void NoronHub::connectToServer(QString address, qint16 port)
{
    Q_D(NoronHub);

    if(!address.isNull())
        setServerAddress(address);

    if(port)
        setPort(port);

    d->socket->connectToHost(this->serverAddress(), this->port());
}

void NoronHub::disconnectFromServer()
{
    Q_D(NoronHub);

    setAutoReconnect(false);
    d->socket->disconnectFromHost();
}

bool NoronHub::setSocketDescriptor(qintptr socketDescriptor)
{
    Q_D(NoronHub);
    return d->socket->setSocketDescriptor(socketDescriptor);
}

void NoronHub::timerEvent(QTimerEvent *)
{
    Q_D(NoronHub);

    if(d->socket->state() == QAbstractSocket::UnconnectedState){
        connectToServer();
    }else if(d->socket->state() == QAbstractSocket::ConnectedState){
        killTimer(d->reconnectTimerId);
        sync();
    }
}

void NoronHub::sync()
{
    qDebug() << "sync";
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
            qDebug() << ("set" + w) << p.read(o);
        }
    }
    qDebug() << "commit";
    commit();
}

void NoronHub::beginTransaction()
{
    Q_D(NoronHub);
    d->isTransaction = true;
}

bool NoronHub::isTransaction() const
{
    Q_D(const NoronHub);
    return d->isTransaction;
}

void NoronHub::rollback()
{
    Q_D(NoronHub);
    d->buffer.clear();
    d->isTransaction = false;
}

void NoronHub::commit()
{
    Q_D(NoronHub);
    d->socket->write(QJsonDocument::fromVariant(d->buffer).toJson());
    d->socket->flush();
    d->buffer.clear();
    d->isTransaction = false;
}

void NoronHub::socket_connected()
{
    setIsConnected(true);
}

void NoronHub::socket_disconnected()
{
    Q_D(NoronHub);

    setIsConnected(false);

    if(autoReconnect()){
        connectToServer();
        d->reconnectTimerId = startTimer(500);
    }else{
        qDebug()<<"emit disconnected()";
        emit disconnected();
        this->deleteLater();
    }
}

void NoronHub::socket_onReadyRead()
{
    Q_D(NoronHub);

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

qlonglong NoronHub::invokeOnPeer(QString sender, QString methodName,
                               QVariant val0, QVariant val1,
                               QVariant val2, QVariant val3,
                               QVariant val4, QVariant val5,
                               QVariant val6, QVariant val7,
                               QVariant val8, QVariant val9)
{
    Q_D(NoronHub);

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
