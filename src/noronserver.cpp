#include "noronpeer.h"
#include <QTcpServer>
#include <QSet>
#include <QThread>

#include "noronserver.h"
#include "noronserver_p.h"
#include "norontcpsocketserver_p.h"
#include "noronjsondataserializer.h"

QT_BEGIN_NAMESPACE

NoronServerPrivate::NoronServerPrivate(NoronServer *parent) : q_ptr(parent), isMultiThread(false)
{

}

NoronServer::NoronServer(qint16 port, QObject *parent) : NoronHubBase(parent),
    d_ptr(new NoronServerPrivate(this))
{
    Q_D(NoronServer);

    d->serverSocket = new NoronTcpSocketServer(this);

    d->serverSocket->listen(QHostAddress::Any, port);
    d->serverSocket->setObjectName("serverSocket");

    setSerializer(new NoronJsonDataSerializer(this));

    connect(d->serverSocket, &NoronTcpSocketServer::newIncomingConnection, this, &NoronServer::server_newIncomingConnection);
}

QSet<NoronPeer *> NoronServer::peers()
{
    Q_D(NoronServer);
    return d->peers;
}

int NoronServer::typeId() const
{
    Q_D(const NoronServer);
    return d->typeId;
}

bool NoronServer::isMultiThread() const
{
    Q_D(const NoronServer);
    return d->isMultiThread;
}

void NoronServer::beginTransaction()
{
    Q_D(const NoronServer);

    foreach(NoronPeer *peer, d->peers)
        peer->hub()->beginTransaction();
}

void NoronServer::rollback()
{
    Q_D(const NoronServer);
    foreach(NoronPeer *peer, d->peers)
        peer->hub()->rollback();
}

void NoronServer::commit()
{
    Q_D(const NoronServer);
    foreach(NoronPeer *peer, d->peers)
        peer->hub()->commit();
}

void NoronServer::server_newIncomingConnection(qintptr socketDescriptor)
{
    Q_D(NoronServer);

    const QMetaObject *metaObject = QMetaType::metaObjectForType(d->typeId);
    QObject *o = metaObject->newInstance();
    NoronPeer *peer = qobject_cast<NoronPeer*>(o);

    if(!peer){
        qWarning("PEER IS INCORRECT!!!");
        return;
    }
    NoronHub *hub = new NoronHub(serializer(), this);
    peer->setHub(hub);
    if (!peer->hub()->setSocketDescriptor(socketDescriptor)) {
        delete peer;
        return;
    }

    hub->setValidateToken(validateToken());
    hub->addSharedObject(peer);
    foreach (NoronPeer *o, _classes.values())
        peer->hub()->addSharedObject(o);

    QThread *thread;

    if(isMultiThread()){
        thread = new QThread(this);
        hub->setThread(thread);
        peer->moveToThread(thread);
        thread->start();

        connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    }

    connect(hub, &NoronHub::disconnected, this, &NoronServer::hub_disconnected);
//            [=] () {
//        //TODO: add a property QThread for NoronHub and in disconnect delete thread and all shared objects
//        d->peers.remove(peer);
//        emit peerDisconnected(peer);
//        peer->deleteLater();
//        if(peer->hub()->thread()){
//            peer->hub()->thread()->exit();
//            peer->hub()->thread()->deleteLater();
//        }
//    } );

    d->peers.insert(peer);
    emit peerConnected(peer);
}

void NoronServer::setTypeId(int typeId)
{
    Q_D(NoronServer);

    if (d->typeId == typeId)
        return;

    d->typeId = typeId;
    emit typeIdChanged(typeId);
}

void NoronServer::setIsMultiThread(bool isMultiThread)
{
    Q_D(NoronServer);

    if (d->isMultiThread == isMultiThread)
        return;

    d->isMultiThread = isMultiThread;
    emit isMultiThreadChanged(isMultiThread);
}

void NoronServer::hub_disconnected()
{
    Q_D(NoronServer);

    NoronHubBase *hub = qobject_cast<NoronHubBase*>(sender());

    d->peers.remove(hub->sharedObjects().at(0));

    if(hub->thread())
        hub->thread()->exit();

    emit peerDisconnected(hub->sharedObjects().at(0));
}

qlonglong NoronServer::invokeOnPeer(QString sender, QString methodName,
                                  QVariant val0, QVariant val1,
                                  QVariant val2, QVariant val3,
                                  QVariant val4, QVariant val5,
                                  QVariant val6, QVariant val7,
                                  QVariant val8, QVariant val9)
{
    Q_D(NoronServer);

    foreach(NoronPeer *peer, d->peers)
        peer->hub()->invokeOnPeer(sender, methodName,
                                  val0, val1, val2, val3, val4,
                                  val5, val6, val7, val8, val9);

    return 0;
}

QT_END_NAMESPACE
