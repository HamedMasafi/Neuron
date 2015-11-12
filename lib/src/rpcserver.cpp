#include "rpcpeer.h"
#include <QTcpServer>
#include <QSet>
#include <QThread>

#include "rpcserver.h"
#include "rpcserver_p.h"
#include "rpctcpsocketserver_p.h"
#include "rpcjsondataserializer.h"

QT_BEGIN_NAMESPACE

RpcServerPrivate::RpcServerPrivate(RpcServer *parent) : q_ptr(parent), isMultiThread(false)
{

}

RpcServer::RpcServer(qint16 port, QObject *parent) : RpcHubBase(parent),
    d_ptr(new RpcServerPrivate(this))
{
    Q_D(RpcServer);

    d->serverSocket = new RpcTcpSocketServer(this);

    d->serverSocket->listen(QHostAddress::Any, port);
    d->serverSocket->setObjectName("serverSocket");

    setSerializer(new RpcJsonDataSerializer(this));

    connect(d->serverSocket, &RpcTcpSocketServer::newIncomingConnection, this, &RpcServer::server_newIncomingConnection);
}

QSet<RpcPeer *> RpcServer::peers()
{
    Q_D(RpcServer);
    return d->peers;
}

int RpcServer::typeId() const
{
    Q_D(const RpcServer);
    return d->typeId;
}

bool RpcServer::isMultiThread() const
{
    Q_D(const RpcServer);
    return d->isMultiThread;
}

void RpcServer::beginTransaction()
{
    Q_D(const RpcServer);

    foreach(RpcPeer *peer, d->peers)
        peer->hub()->beginTransaction();
}

void RpcServer::rollback()
{
    Q_D(const RpcServer);
    foreach(RpcPeer *peer, d->peers)
        peer->hub()->rollback();
}

void RpcServer::commit()
{
    Q_D(const RpcServer);
    foreach(RpcPeer *peer, d->peers)
        peer->hub()->commit();
}

void RpcServer::server_newIncomingConnection(qintptr socketDescriptor)
{
    Q_D(RpcServer);

    const QMetaObject *metaObject = QMetaType::metaObjectForType(d->typeId);
    QObject *o = metaObject->newInstance();
    RpcPeer *peer = qobject_cast<RpcPeer*>(o);

    if(!peer){
        qWarning("PEER IS INCORRECT!!!");
        return;
    }
    RpcHub *hub = new RpcHub(serializer(), this);
    peer->setHub(hub);
    if (!peer->hub()->setSocketDescriptor(socketDescriptor)) {
        delete peer;
        return;
    }

    hub->setValidateToken(validateToken());
    hub->addSharedObject(peer);
    foreach (RpcPeer *o, _classes.values())
        peer->hub()->addSharedObject(o);

    QThread *thread;

    if(isMultiThread()){
        thread = new QThread(this);
        hub->setThread(thread);
        peer->moveToThread(thread);
        thread->start();

        connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    }

    connect(hub, &RpcHub::disconnected, this, &RpcServer::hub_disconnected);
//            [=] () {
//        //TODO: add a property QThread for RpcHub and in disconnect delete thread and all shared objects
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

void RpcServer::setTypeId(int typeId)
{
    Q_D(RpcServer);

    if (d->typeId == typeId)
        return;

    d->typeId = typeId;
    emit typeIdChanged(typeId);
}

void RpcServer::setIsMultiThread(bool isMultiThread)
{
    Q_D(RpcServer);

    if (d->isMultiThread == isMultiThread)
        return;

    d->isMultiThread = isMultiThread;
    emit isMultiThreadChanged(isMultiThread);
}

void RpcServer::hub_disconnected()
{
    Q_D(RpcServer);

    RpcHubBase *hub = qobject_cast<RpcHubBase*>(sender());

    d->peers.remove(hub->sharedObjects().at(0));

    if(hub->thread())
        hub->thread()->exit();

    emit peerDisconnected(hub->sharedObjects().at(0));
}

qlonglong RpcServer::invokeOnPeer(QString sender, QString methodName,
                                  QVariant val0, QVariant val1,
                                  QVariant val2, QVariant val3,
                                  QVariant val4, QVariant val5,
                                  QVariant val6, QVariant val7,
                                  QVariant val8, QVariant val9)
{
    Q_D(RpcServer);

    foreach(RpcPeer *peer, d->peers)
        peer->hub()->invokeOnPeer(sender, methodName,
                                  val0, val1, val2, val3, val4,
                                  val5, val6, val7, val8, val9);

    return 0;
}

QT_END_NAMESPACE
