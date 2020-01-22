/**************************************************************************
**
** This file is part of .
** https://github.com/HamedMasafi/
**
**  is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
**  is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with .  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#include <QtCore/QThread>

#include <QEvent>
#include <QNetworkInterface>
#include <QUdpSocket>
#include <SharedObject>

#include "abstractdataencoder.h"
#include "serverhub.h"
#include "peer.h"
#include "jsonbinaryserializer.h"
#include "tcpsocketserver_p.h"
#include "server_p.h"
#include "server.h"
#include "serverthread.h"

NEURON_BEGIN_NAMESPACE

ServerPrivate::ServerPrivate(Server *parent) : q_ptr(parent),
    serverSocket(nullptr), typeId(0), serverType(Server::SingleThread),
    hubId(0), reconnectTimeout(0), broadcastSocket(nullptr)
{
}

Server::Server(QObject *parent) : AbstractHub(parent),
    d(new ServerPrivate(this))
{
    d->serverSocket = new TcpSocketServer;
    d->serverSocket->setObjectName("serverSocket");

    K_REG_OBJECT(d->serverSocket);

//    qRegisterMetaType<NEURON_WRAP_NAMESPACE(AbstractHub::Status)>("AbstractHub::Status");
    connect(d->serverSocket, &TcpSocketServer::newIncomingConnection,
            this, &Server::server_newIncomingConnection);
}

Server::Server(quint16 port, QObject *parent) : AbstractHub(parent),
     d(new ServerPrivate(this))
{
    d->serverSocket = new TcpSocketServer;
    d->serverSocket->setObjectName("serverSocket");

    K_REG_OBJECT(d->serverSocket);

//    qRegisterMetaType<NEURON_WRAP_NAMESPACE(AbstractHub::Status)>("AbstractHub::Status");
    connect(d->serverSocket, &TcpSocketServer::newIncomingConnection,
            this, &Server::server_newIncomingConnection);

    startServer(port);
}

Server::~Server()
{
}

QSet<Peer *> Server::peers() const
{
    return d->peers;
}

bool Server::startServer(quint16 port)
{
    bool ok = d->serverSocket->listen(QHostAddress::Any, port);
    if (!ok) {
       qWarning("Unable to start server. Error: %s", d->serverSocket->errorString().toUtf8().data());
    }
    return ok;
}

quint32 Server::reconnectTimeout() const
{
    return d->reconnectTimeout;
}

bool Server::isListening() const
{
    return d->serverSocket->isListening();
}

void Server::startBroadcast(const quint16 &serverPort, const quint16 &broadcastPort)
{
    if (d->broadcastSocket)
        return;

    QVariantMap map;

    QString localAddress;
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            localAddress = address.toString();
    }

    map.insert("port", serverPort);
    map.insert("address", localAddress);
    if (encoder())
        encoder()->encrypt(map);

    d->broadcastData = serializer()->serialize(map);
    d->broadcastSocket = new QUdpSocket(this);
    d->broadcastPort = broadcastPort;
    d->broadcastTimer = startTimer(2000);
}

void Server::stopBroadcast()
{
    killTimer(d->broadcastTimer);
}

int Server::typeId() const
{
    return d->typeId;
}

Server::ServerType Server::serverType() const
{
    return d->serverType;
}

void Server::hub_connected()
{
    K_TRACE_DEBUG;
    ServerHub *hub = qobject_cast<ServerHub*>(sender());
    K_REG_OBJECT(hub);

    if(hub->hubId()){
        K_TRACE("is reconnect");

        AbstractHub *hub2 = d->hubs[hub->hubId()];

        if(!hub2)
            qFatal("reconnecting to an invalid hub");

    }else{
        K_TRACE("is new connect");
    }

    //TODO: delete peerNewCreatedObject
    const QMetaObject *metaObject = QMetaType::metaObjectForType(d->typeId);
    QObject *peerNewCreatedObject = metaObject->newInstance(Q_ARG(QObject*, this));

    Peer *peer = qobject_cast<Peer*>(peerNewCreatedObject);
    K_REG_OBJECT(peerNewCreatedObject);

    if(!peer){
        qWarning("Unable to instancticate %s.", metaObject->className());
        peerNewCreatedObject->deleteLater();
        return;
    }

    //    hub->setPeer(peer);
    peer->setHub(hub);

    foreach (SharedObject *sharedObj, sharedObjects()){
        hub->attachSharedObject(sharedObj);
    }

    if(d->hubId++ >= LONG_MAX - 1)
        d->hubId = 1;

    hub->setHubId(d->hubId);

    d->hubs.insert(d->hubId, hub);
    d->peers.insert(peer);

//    hub->setStatus(AbstractHub::Connected);
    emit peerConnected(peer);
}

void Server::hub_disconnected()
{
    ServerHub *hub = qobject_cast<ServerHub*>(sender());

    if(d->reconnectTimeout){
        QThread::sleep(d->reconnectTimeout);
        if(hub->status() == ServerHub::Connected)
            return;
    }

    emit peerDisconnected(hub->peer());
    d->peers.remove(hub->peer());
    d->hubs.remove(hub->hubId());
//    QList<SharedObject *> sharedObjects = hub->sharedObjects();
//    foreach (SharedObject *so, sharedObjects){
//        hub->removeSharedObject(so);
//    }

    //TODO: correct lifetime
//    d->peers.remove(hub->peer());
//    d->hubs.remove(hub);
//    hub->peer()->deleteLater();
//    hub->deleteLater();

    if(d->serverType == Server::MultiThread && hub->serverThread()){
        hub->serverThread()->exit();
    } else {
        hub->deleteLater();
    }


    hub->peer()->deleteLater();
}

void Server::server_newIncomingConnection(qintptr socketDescriptor)
{
    initalizeMutex.lock();

    K_TRACE_DEBUG;

//    const QMetaObject *metaObject = QMetaType::metaObjectForType(d->typeId);
//    QObject *o = metaObject->newInstance();
//    Peer *peer = qobject_cast<Peer*>(o);

//    if(!peer){
//        qWarning("Peer object is incorrect! Use peer-generator tool for peer generation.");
//        o->deleteLater();
//        return;
//    }

//    K_REG_OBJECT(o);
    ServerHub *hub;
    bool hubIsValid;
    if(d->serverType == Server::MultiThread){
        ServerThread *thread = new ServerThread(socketDescriptor, sender());

        connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        thread->start();

        while(!thread->isStarted()) ;

        hub = thread->hub();
        hub->setServerThread(thread);
        hub->setIsMultiThread(true);

        hubIsValid = (hub != nullptr);

        K_REG_OBJECT(thread);
    }else{
        hub = new ServerHub(serializer(), this);
        hubIsValid = hub->setSocketDescriptor(socketDescriptor);
        K_REG_OBJECT(hub);
    }

    connect(hub, &AbstractHub::connected, this, &Server::hub_connected);
    connect(hub, &AbstractHub::disconnected, this, &Server::hub_disconnected);

//    if (hub->status() == AbstractHub::Connected)
//        emit hub->connected();

    /*
    hub = new ServerHub;
    if(d->serverType == Server::MultiThread){
        QThread *t = new QThread(this);
        hub->moveToThread(t);
        t->start();
    }
    hubIsValid = hub->setSocketDescriptor(socketDescriptor);
    */

    if (!hubIsValid) {
        qWarning("ServerHub creation faild");
        hub->deleteLater();
//        peer->deleteLater();
        initalizeMutex.unlock();
        return;
    }

    hub->setSerializer(serializer());
    hub->setEncoder(encoder());
    K_TRACE_DEBUG;

    initalizeMutex.unlock();
}

void Server::setTypeId(int typeId)
{
    if (d->typeId == typeId)
        return;

    d->typeId = typeId;
    emit typeIdChanged(typeId);
}

void Server::setServerType(Server::ServerType serverType)
{
    if (d->serverType == serverType)
        return;

    d->serverType = serverType;
    emit serverTypeChanged(serverType);
}

void Server::setReconnectTimeout(quint32 reconnectTimeout)
{
    if (d->reconnectTimeout == reconnectTimeout)
        return;

    d->reconnectTimeout = reconnectTimeout;
    emit reconnectTimeoutChanged(reconnectTimeout);
}

void Server::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == d->broadcastTimer) {
        d->broadcastSocket->writeDatagram(d->broadcastData,
                                          QHostAddress::Broadcast,
                                          d->broadcastPort);

#ifdef RAT_TEST_PAD
        d->broadcastSocket->writeDatagram(d->broadcastData,
                                          QHostAddress::LocalHost,
                                          d->broadcastPort);
#endif
    }
}



NEURON_END_NAMESPACE
