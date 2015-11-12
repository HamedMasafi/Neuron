#include "rpcpeer.h"
#include "rpchubbase.h"
#include "rpchubbase_p.h"
#include "rpcserializerbase_p.h"

QT_BEGIN_NAMESPACE

RpcHubBasePrivate::RpcHubBasePrivate(RpcHubBase *parent) : q_ptr(parent),
    autoReconnect(false),
    serializer(0), thread(0)
{

}

RpcHubBase::RpcHubBase(QObject *parent) : QObject(parent),
    d_ptr(new RpcHubBasePrivate(this))
{

}

void RpcHubBase::addSharedObject(RpcPeer *o)
{
    if(!o->inherits("RpcPeer")){
        qFatal("The class %s does not inherits from RpcPeer. Use RpcPeerGenerate tool for creating peer classes",
               o->metaObject()->className());
        return;
    }
    _classes[o->metaObject()->className()] = o;
}

QList<RpcPeer*> RpcHubBase::sharedObjects() const
{
    return _classes.values();
}

void RpcHubBase::connectToServer(QString address, qint16 port)
{
    Q_UNUSED(address);
    Q_UNUSED(port);

    qWarning("RpcHubBase::connectToServer");
}

bool RpcHubBase::setSocketDescriptor(qintptr socketDescriptor)
{
    Q_UNUSED(socketDescriptor);

    qWarning("RpcHubBase::setSocketDescriptor");

    return false;
}

qint16 RpcHubBase::port() const
{
    Q_D(const RpcHubBase);
    return d->port;
}

QString RpcHubBase::serverAddress() const
{
    Q_D(const RpcHubBase);
    return d->serverAddress;
}

bool RpcHubBase::autoReconnect() const
{
    Q_D(const RpcHubBase);
    return d->autoReconnect;
}

bool RpcHubBase::isConnected() const
{
    Q_D(const RpcHubBase);
    return d->isConnected;
}

QString RpcHubBase::validateToken() const
{
    Q_D(const RpcHubBase);
    return d->validateToken;
}

RpcSerializerBase *RpcHubBase::serializer() const
{
    Q_D(const RpcHubBase);
    return d->serializer;
}

QThread *RpcHubBase::thread() const
{
    Q_D(const RpcHubBase);
    return d->thread;
}

void RpcHubBase::setPort(qint16 port)
{
    Q_D(RpcHubBase);

    if (d->port == port)
        return;

    d->port = port;
    emit portChanged(port);
}

void RpcHubBase::setServerAddress(QString serverAddress)
{
    Q_D(RpcHubBase);

    if (d->serverAddress == serverAddress)
        return;

    d->serverAddress = serverAddress;
    emit serverAddressChanged(serverAddress);
}

void RpcHubBase::setAutoReconnect(bool autoReconnect)
{
    Q_D(RpcHubBase);

    if (d->autoReconnect == autoReconnect)
        return;

    d->autoReconnect = autoReconnect;
    emit autoReconnectChanged(autoReconnect);
}

void RpcHubBase::setIsConnected(bool isConnected)
{
    Q_D(RpcHubBase);

    if (d->isConnected == isConnected)
        return;

    d->isConnected = isConnected;
    emit isConnectedChanged(isConnected);
}

void RpcHubBase::setValidateToken(QString validateToken)
{
    Q_D(RpcHubBase);

    if (d->validateToken == validateToken)
        return;

    d->validateToken = validateToken;
    emit validateTokenChanged(validateToken);
}

void RpcHubBase::setSerializer(RpcSerializerBase *serializerObject)
{
    Q_D(RpcHubBase);

    if (d->serializer == serializerObject)
        return;

    d->serializer = serializerObject;
    emit serializerChanged(serializerObject);
}

void RpcHubBase::setThread(QThread *thread)
{
    Q_D(RpcHubBase);

    if (d->thread == thread)
        return;

    d->thread = thread;
    emit threadChanged(thread);
}

QT_END_NAMESPACE
