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

#include <QtCore/QThread>

#include <NoronSharedObject>

#include "noronserverhub.h"
#include "noronpeer.h"
#include "noronjsonbinaryserializer.h"
#include "norontcpsocketserver_p.h"
#include "noronserver_p.h"
#include "noronserver.h"
#include "noronserverthread.h"

NORON_BEGIN_NAMESPACE

NoronServerPrivate::NoronServerPrivate(NoronServer *parent) : q_ptr(parent),
    serverSocket(0), typeId(0), serverType(NoronServer::SingleThread), hubId(0), reconnectTimeout(0)
{
}

NoronServer::NoronServer(QObject *parent) : NoronAbstractHub(parent),
    d_ptr(new NoronServerPrivate(this))
{
    Q_D(NoronServer);

    d->serverSocket = new NoronTcpSocketServer;
    d->serverSocket->setObjectName("serverSocket");

    K_REG_OBJECT(d->serverSocket);

    connect(d->serverSocket, &NoronTcpSocketServer::newIncomingConnection,
            this, &NoronServer::server_newIncomingConnection);
}

NoronServer::NoronServer(qint16 port, QObject *parent) : NoronAbstractHub(parent),
     d_ptr(new NoronServerPrivate(this))
{
    Q_D(NoronServer);

    d->serverSocket = new NoronTcpSocketServer;
    d->serverSocket->setObjectName("serverSocket");

    K_REG_OBJECT(d->serverSocket);

    connect(d->serverSocket, &NoronTcpSocketServer::newIncomingConnection,
            this, &NoronServer::server_newIncomingConnection);

    startServer(port);
}

NoronServer::~NoronServer()
{
    Q_D(NoronServer);
    delete d;
}

QSet<NoronPeer *> NoronServer::peers()
{
    Q_D(NoronServer);
    return d->peers;
}

void NoronServer::startServer(qint16 port)
{
    Q_D(NoronServer);

    bool ok = d->serverSocket->listen(QHostAddress::Any, port);
    if (!ok) {
       qWarning("Unable to start server. Error: %s", d->serverSocket->errorString().toUtf8().data());
    }
}

int NoronServer::reconnectTimeout() const
{
    Q_D(const NoronServer);
    return d->reconnectTimeout;
}

bool NoronServer::isListening() const
{
    Q_D(const NoronServer);
    return d->serverSocket->isListening();
}

int NoronServer::typeId() const
{
    Q_D(const NoronServer);
    return d->typeId;
}

NoronServer::ServerType NoronServer::serverType() const
{
    Q_D(const NoronServer);
    return d->serverType;
}

void NoronServer::hub_connected()
{
    Q_D(NoronServer);

    K_TRACE_DEBUG;
    NoronServerHub *hub = qobject_cast<NoronServerHub*>(sender());
    K_REG_OBJECT(hub);

    if(hub->hubId()){
        K_TRACE("is reconnect");

        NoronAbstractHub *hub2 = d->hubs[hub->hubId()];

        if(!hub2)
            qFatal("reconnecting to an invalid hub");

    }else{
        K_TRACE("is new connect");
    }

    //TODO: delete peerNewCreatedObject
    const QMetaObject *metaObject = QMetaType::metaObjectForType(d->typeId);
    QObject *peerNewCreatedObject = metaObject->newInstance();
    NoronPeer *peer = qobject_cast<NoronPeer*>(peerNewCreatedObject);
    K_REG_OBJECT(peerNewCreatedObject);

    if(!peer){
        qWarning("Peer object is incorrect! Use peer-generator tool for peer generation.");
        peerNewCreatedObject->deleteLater();
        return;
    }

    //    hub->setPeer(peer);
    peer->setHub(hub);

    foreach (NoronSharedObject *sharedObj, sharedObjects()){
        hub->attachSharedObject(sharedObj);
        qDebug() << "so" << sharedObj->objectName() << "added to new hub";
    }

    if(d->hubId++ >= LONG_LONG_MAX - 1)
        d->hubId = 1;

    hub->setHubId(d->hubId);

    d->hubs.insert(d->hubId, hub);
    d->peers.insert(peer);

    hub->setStatus(NoronAbstractHub::Connected);
    emit peerConnected(peer);
}

void NoronServer::hub_disconnected()
{
    Q_D(NoronServer);

    NoronServerHub *hub = qobject_cast<NoronServerHub*>(sender());

    if(d->reconnectTimeout){
        QThread::sleep(d->reconnectTimeout);
        if(hub->status() == NoronServerHub::Connected)
            return;
    }

    emit peerDisconnected(hub->peer());
    d->peers.remove(hub->peer());
    d->hubs.remove(hub->hubId());
//    QList<NoronSharedObject *> sharedObjects = hub->sharedObjects();
//    foreach (NoronSharedObject *so, sharedObjects){
//        hub->removeSharedObject(so);
//    }

    //TODO: correct lifetime
//    d->peers.remove(hub->peer());
//    d->hubs.remove(hub);
//    hub->peer()->deleteLater();
//    hub->deleteLater();

    if(d->serverType == NoronServer::MultiThread && hub->serverThread()){
        hub->serverThread()->exit();
    } else {
        hub->deleteLater();
    }


    hub->peer()->deleteLater();
}

void NoronServer::server_newIncomingConnection(qintptr socketDescriptor)
{
    initalizeMutex.lock();

    Q_D(NoronServer);
    K_TRACE_DEBUG;

//    const QMetaObject *metaObject = QMetaType::metaObjectForType(d->typeId);
//    QObject *o = metaObject->newInstance();
//    NoronPeer *peer = qobject_cast<NoronPeer*>(o);

//    if(!peer){
//        qWarning("Peer object is incorrect! Use peer-generator tool for peer generation.");
//        o->deleteLater();
//        return;
//    }

//    K_REG_OBJECT(o);
    NoronServerHub *hub;
    bool hubIsValid;
    if(d->serverType == NoronServer::MultiThread){
        NoronServerThread *thread = new NoronServerThread(socketDescriptor, sender());

        connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        thread->start();

        while(!thread->isStarted()) ;

        hub = thread->hub();
        hub->setServerThread(thread);
        hub->setIsMultiThread(true);

        hubIsValid = (hub != 0);

        K_REG_OBJECT(thread);
    }else{
        hub = new NoronServerHub(serializer(), this);
        hubIsValid = hub->setSocketDescriptor(socketDescriptor);
        K_REG_OBJECT(hub);
    }

    connect(hub, &NoronAbstractHub::connected, this, &NoronServer::hub_connected);
    connect(hub, &NoronAbstractHub::disconnected, this, &NoronServer::hub_disconnected);

    if (hub->status() == NoronAbstractHub::Connected)
        emit hub->connected();

    /*
    hub = new NoronServerHub;
    if(d->serverType == NoronServer::MultiThread){
        QThread *t = new QThread(this);
        hub->moveToThread(t);
        t->start();
    }
    hubIsValid = hub->setSocketDescriptor(socketDescriptor);
    */

    if (!hubIsValid) {
        qWarning("NoronServerHub creation faild");
        hub->deleteLater();
//        peer->deleteLater();
        return;
    }

    hub->setSerializer(serializer());
    hub->setValidateToken(validateToken());
    K_TRACE_DEBUG;

    initalizeMutex.unlock();
}

void NoronServer::setTypeId(int typeId)
{
    Q_D(NoronServer);

    if (d->typeId == typeId)
        return;

    d->typeId = typeId;
    emit typeIdChanged(typeId);
}

void NoronServer::setServerType(NoronServer::ServerType serverType)
{
    Q_D(NoronServer);

    if (d->serverType == serverType)
        return;

    d->serverType = serverType;
    emit serverTypeChanged(serverType);
}

void NoronServer::setReconnectTimeout(int reconnectTimeout)
{
    Q_D(NoronServer);
    if (d->reconnectTimeout == reconnectTimeout)
        return;

    d->reconnectTimeout = reconnectTimeout;
    emit reconnectTimeoutChanged(reconnectTimeout);
}

NORON_END_NAMESPACE
