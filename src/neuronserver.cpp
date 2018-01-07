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

#include <QtCore/QThread>

#include <NeuronSharedObject>

#include "neuronserverhub.h"
#include "neuronpeer.h"
#include "neuronjsonbinaryserializer.h"
#include "neurontcpsocketserver_p.h"
#include "neuronserver_p.h"
#include "neuronserver.h"
#include "neuronserverthread.h"

NEURON_BEGIN_NAMESPACE

NeuronServerPrivate::NeuronServerPrivate(NeuronServer *parent) : q_ptr(parent),
    serverSocket(0), typeId(0), serverType(NeuronServer::SingleThread), hubId(0), reconnectTimeout(0)
{
}

NeuronServer::NeuronServer(QObject *parent) : NeuronAbstractHub(parent),
    d_ptr(new NeuronServerPrivate(this))
{
    Q_D(NeuronServer);

    d->serverSocket = new NeuronTcpSocketServer;
    d->serverSocket->setObjectName("serverSocket");

    K_REG_OBJECT(d->serverSocket);

    connect(d->serverSocket, &NeuronTcpSocketServer::newIncomingConnection,
            this, &NeuronServer::server_newIncomingConnection);
}

NeuronServer::NeuronServer(qint16 port, QObject *parent) : NeuronAbstractHub(parent),
     d_ptr(new NeuronServerPrivate(this))
{
    Q_D(NeuronServer);

    d->serverSocket = new NeuronTcpSocketServer;
    d->serverSocket->setObjectName("serverSocket");

    K_REG_OBJECT(d->serverSocket);

    connect(d->serverSocket, &NeuronTcpSocketServer::newIncomingConnection,
            this, &NeuronServer::server_newIncomingConnection);

    startServer(port);
}

NeuronServer::~NeuronServer()
{
    Q_D(NeuronServer);
    delete d;
}

QSet<NeuronPeer *> NeuronServer::peers() const
{
    Q_D(const NeuronServer);
    return d->peers;
}

void NeuronServer::startServer(qint16 port)
{
    Q_D(NeuronServer);

    bool ok = d->serverSocket->listen(QHostAddress::Any, port);
    if (!ok) {
       qWarning("Unable to start server. Error: %s", d->serverSocket->errorString().toUtf8().data());
    }
}

quint32 NeuronServer::reconnectTimeout() const
{
    Q_D(const NeuronServer);
    return d->reconnectTimeout;
}

bool NeuronServer::isListening() const
{
    Q_D(const NeuronServer);
    return d->serverSocket->isListening();
}

int NeuronServer::typeId() const
{
    Q_D(const NeuronServer);
    return d->typeId;
}

NeuronServer::ServerType NeuronServer::serverType() const
{
    Q_D(const NeuronServer);
    return d->serverType;
}

void NeuronServer::hub_connected()
{
    Q_D(NeuronServer);

    K_TRACE_DEBUG;
    NeuronServerHub *hub = qobject_cast<NeuronServerHub*>(sender());
    K_REG_OBJECT(hub);

    if(hub->hubId()){
        K_TRACE("is reconnect");

        NeuronAbstractHub *hub2 = d->hubs[hub->hubId()];

        if(!hub2)
            qFatal("reconnecting to an invalid hub");

    }else{
        K_TRACE("is new connect");
    }

    //TODO: delete peerNewCreatedObject
    const QMetaObject *metaObject = QMetaType::metaObjectForType(d->typeId);
    QObject *peerNewCreatedObject = metaObject->newInstance();
    NeuronPeer *peer = qobject_cast<NeuronPeer*>(peerNewCreatedObject);
    K_REG_OBJECT(peerNewCreatedObject);

    if(!peer){
        qWarning("Peer object is incorrect! Use peer-generator tool for peer generation.");
        peerNewCreatedObject->deleteLater();
        return;
    }

    //    hub->setPeer(peer);
    peer->setHub(hub);

    foreach (NeuronSharedObject *sharedObj, sharedObjects()){
        hub->attachSharedObject(sharedObj);
    }

    if(d->hubId++ >= LONG_LONG_MAX - 1)
        d->hubId = 1;

    hub->setHubId(d->hubId);

    d->hubs.insert(d->hubId, hub);
    d->peers.insert(peer);

    hub->setStatus(NeuronAbstractHub::Connected);
    emit peerConnected(peer);
}

void NeuronServer::hub_disconnected()
{
    Q_D(NeuronServer);

    NeuronServerHub *hub = qobject_cast<NeuronServerHub*>(sender());

    if(d->reconnectTimeout){
        QThread::sleep(d->reconnectTimeout);
        if(hub->status() == NeuronServerHub::Connected)
            return;
    }

    emit peerDisconnected(hub->peer());
    d->peers.remove(hub->peer());
    d->hubs.remove(hub->hubId());
//    QList<NeuronSharedObject *> sharedObjects = hub->sharedObjects();
//    foreach (NeuronSharedObject *so, sharedObjects){
//        hub->removeSharedObject(so);
//    }

    //TODO: correct lifetime
//    d->peers.remove(hub->peer());
//    d->hubs.remove(hub);
//    hub->peer()->deleteLater();
//    hub->deleteLater();

    if(d->serverType == NeuronServer::MultiThread && hub->serverThread()){
        hub->serverThread()->exit();
    } else {
        hub->deleteLater();
    }


    hub->peer()->deleteLater();
}

void NeuronServer::server_newIncomingConnection(qintptr socketDescriptor)
{
    initalizeMutex.lock();

    Q_D(NeuronServer);
    K_TRACE_DEBUG;

//    const QMetaObject *metaObject = QMetaType::metaObjectForType(d->typeId);
//    QObject *o = metaObject->newInstance();
//    NeuronPeer *peer = qobject_cast<NeuronPeer*>(o);

//    if(!peer){
//        qWarning("Peer object is incorrect! Use peer-generator tool for peer generation.");
//        o->deleteLater();
//        return;
//    }

//    K_REG_OBJECT(o);
    NeuronServerHub *hub;
    bool hubIsValid;
    if(d->serverType == NeuronServer::MultiThread){
        NeuronServerThread *thread = new NeuronServerThread(socketDescriptor, sender());

        connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        thread->start();

        while(!thread->isStarted()) ;

        hub = thread->hub();
        hub->setServerThread(thread);
        hub->setIsMultiThread(true);

        hubIsValid = (hub != 0);

        K_REG_OBJECT(thread);
    }else{
        hub = new NeuronServerHub(serializer(), this);
        hubIsValid = hub->setSocketDescriptor(socketDescriptor);
        K_REG_OBJECT(hub);
    }

    connect(hub, &NeuronAbstractHub::connected, this, &NeuronServer::hub_connected);
    connect(hub, &NeuronAbstractHub::disconnected, this, &NeuronServer::hub_disconnected);

    if (hub->status() == NeuronAbstractHub::Connected)
        emit hub->connected();

    /*
    hub = new NeuronServerHub;
    if(d->serverType == NeuronServer::MultiThread){
        QThread *t = new QThread(this);
        hub->moveToThread(t);
        t->start();
    }
    hubIsValid = hub->setSocketDescriptor(socketDescriptor);
    */

    if (!hubIsValid) {
        qWarning("NeuronServerHub creation faild");
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

void NeuronServer::setTypeId(int typeId)
{
    Q_D(NeuronServer);

    if (d->typeId == typeId)
        return;

    d->typeId = typeId;
    emit typeIdChanged(typeId);
}

void NeuronServer::setServerType(NeuronServer::ServerType serverType)
{
    Q_D(NeuronServer);

    if (d->serverType == serverType)
        return;

    d->serverType = serverType;
    emit serverTypeChanged(serverType);
}

void NeuronServer::setReconnectTimeout(quint32 reconnectTimeout)
{
    Q_D(NeuronServer);
    if (d->reconnectTimeout == reconnectTimeout)
        return;

    d->reconnectTimeout = reconnectTimeout;
    emit reconnectTimeoutChanged(reconnectTimeout);
}

NEURON_END_NAMESPACE
