#include "noronpeer.h"
#include "noronhubbase.h"
#include "noronhubbase_p.h"
#include "noronserializerbase_p.h"

QT_BEGIN_NAMESPACE

NoronHubBasePrivate::NoronHubBasePrivate(NoronHubBase *parent) : q_ptr(parent),
    autoReconnect(false),
    serializer(0), thread(0)
{

}

NoronHubBase::NoronHubBase(QObject *parent) : QObject(parent),
    d_ptr(new NoronHubBasePrivate(this))
{

}

void NoronHubBase::addSharedObject(NoronPeer *o)
{
    if(!o->inherits("NoronPeer")){
        qFatal("The class %s does not inherits from NoronPeer. Use NoronPeerGenerate tool for creating peer classes",
               o->metaObject()->className());
        return;
    }
    _classes[o->metaObject()->className()] = o;
}

QList<NoronPeer *> NoronHubBase::sharedObjects() const
{
    return _classes.values();
}

void NoronHubBase::connectToServer(QString address, qint16 port)
{
    Q_UNUSED(address);
    Q_UNUSED(port);

    qWarning("NoronHubBase::connectToServer");
}

bool NoronHubBase::setSocketDescriptor(qintptr socketDescriptor)
{
    Q_UNUSED(socketDescriptor);

    qWarning("NoronHubBase::setSocketDescriptor");

    return false;
}

qint16 NoronHubBase::port() const
{
    Q_D(const NoronHubBase);
    return d->port;
}

QString NoronHubBase::serverAddress() const
{
    Q_D(const NoronHubBase);
    return d->serverAddress;
}

bool NoronHubBase::autoReconnect() const
{
    Q_D(const NoronHubBase);
    return d->autoReconnect;
}

bool NoronHubBase::isConnected() const
{
    Q_D(const NoronHubBase);
    return d->isConnected;
}

QString NoronHubBase::validateToken() const
{
    Q_D(const NoronHubBase);
    return d->validateToken;
}

NoronSerializerBase *NoronHubBase::serializer() const
{
    Q_D(const NoronHubBase);
    return d->serializer;
}

QThread *NoronHubBase::thread() const
{
    Q_D(const NoronHubBase);
    return d->thread;
}

void NoronHubBase::setPort(qint16 port)
{
    Q_D(NoronHubBase);

    if (d->port == port)
        return;

    d->port = port;
    emit portChanged(port);
}

void NoronHubBase::setServerAddress(QString serverAddress)
{
    Q_D(NoronHubBase);

    if (d->serverAddress == serverAddress)
        return;

    d->serverAddress = serverAddress;
    emit serverAddressChanged(serverAddress);
}

void NoronHubBase::setAutoReconnect(bool autoReconnect)
{
    Q_D(NoronHubBase);

    if (d->autoReconnect == autoReconnect)
        return;

    d->autoReconnect = autoReconnect;
    emit autoReconnectChanged(autoReconnect);
}

void NoronHubBase::setIsConnected(bool isConnected)
{
    Q_D(NoronHubBase);

    if (d->isConnected == isConnected)
        return;

    d->isConnected = isConnected;
    emit isConnectedChanged(isConnected);
}

void NoronHubBase::setValidateToken(QString validateToken)
{
    Q_D(NoronHubBase);

    if (d->validateToken == validateToken)
        return;

    d->validateToken = validateToken;
    emit validateTokenChanged(validateToken);
}

void NoronHubBase::setSerializer(NoronSerializerBase *serializerObject)
{
    Q_D(NoronHubBase);

    if (d->serializer == serializerObject)
        return;

    d->serializer = serializerObject;
    emit serializerChanged(serializerObject);
}

void NoronHubBase::setThread(QThread *thread)
{
    Q_D(NoronHubBase);

    if (d->thread == thread)
        return;

    d->thread = thread;
    emit threadChanged(thread);
}

QT_END_NAMESPACE
