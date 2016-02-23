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

#include "noronserverhub.h"
#include "noronpeer.h"
#include "noronjsonbinaryserializer.h"
#include "norontcpsocketserver_p.h"
#include "noronserver_p.h"
#include "noronserver.h"
#include "noronserverthread.h"

QT_BEGIN_NAMESPACE

NoronServerPrivate::NoronServerPrivate(NoronServer *parent) : q_ptr(parent),
    serverSocket(0), typeId(0), serverType(NoronServer::SingleThread)
{
}

NoronServer::NoronServer(QObject *parent) : NoronAbstractHub(parent)
{
    Q_D(NoronServer);

    d->serverSocket = new NoronTcpSocketServer;
    d->serverSocket->setObjectName("serverSocket");

    connect(d->serverSocket, &NoronTcpSocketServer::newIncomingConnection,
            this, &NoronServer::server_newIncomingConnection);
}

NoronServer::NoronServer(qint16 port, QObject *parent) : NoronAbstractHub(parent),
     d_ptr(new NoronServerPrivate(this))
{
    Q_D(NoronServer);

    d->serverSocket = new NoronTcpSocketServer;
    d->serverSocket->listen(QHostAddress::Any, port);
    d->serverSocket->setObjectName("serverSocket");

    connect(d->serverSocket, &NoronTcpSocketServer::newIncomingConnection,
            this, &NoronServer::server_newIncomingConnection);
}

QSet<NoronPeer *> NoronServer::peers()
{
    Q_D(NoronServer);
    return d->peers;
}

void NoronServer::startServer(qint16 port)
{
    Q_D(NoronServer);

    d->serverSocket->listen(QHostAddress::Any, port);
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

void NoronServer::hub_disconnected()
{
    Q_D(NoronServer);

    NoronServerHub *hub = qobject_cast<NoronServerHub*>(sender());

    d->peers.remove(hub->peer());
    d->hubs.remove(hub);
    hub->peer()->deleteLater();
    hub->deleteLater();

    if(d->serverType == NoronServer::MultiThread && hub->serverThread()){
        hub->serverThread()->exit();
    }

    emit peerDisconnected(hub->peer());
}

void NoronServer::server_newIncomingConnection(qintptr socketDescriptor)
{
    Q_D(NoronServer);

    const QMetaObject *metaObject = QMetaType::metaObjectForType(d->typeId);
    QObject *o = metaObject->newInstance();
    NoronPeer *peer = qobject_cast<NoronPeer*>(o);

    if(!peer){
        qWarning("Peer object is incorrect! Use peer-generator tool for peer generation.");
        o->deleteLater();
        return;
    }

    NoronServerHub *hub;
    bool hubIsValid;
    if(d->serverType == NoronServer::MultiThread){
        NoronServerThread *thread = new NoronServerThread(socketDescriptor, sender());

        connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        thread->start();

        while(!thread->isStarted()) ;

        hub = thread->hub();
        hub->setServerThread(thread);

        hub->_isMultiThread = true;
        hubIsValid = (hub != 0);
    }else{
        hub = new NoronServerHub(this);
        hubIsValid = hub->setSocketDescriptor(socketDescriptor);
    }

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
        peer->deleteLater();
        return;
    }

    hub->setPeer(peer);
    peer->setHub(hub);

    hub->setSerializer(serializer());
    hub->setValidateToken(validateToken());
    foreach (NoronSharedObject *o, sharedObjects())
        hub->addSharedObject(o);

    connect(hub, &NoronAbstractHub::disconnected, this, &NoronServer::hub_disconnected);

    d->hubs.insert(hub);
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

void NoronServer::setServerType(NoronServer::ServerType serverType)
{
    Q_D(NoronServer);

    if (d->serverType == serverType)
        return;

    d->serverType = serverType;
    emit serverTypeChanged(serverType);
}

QT_END_NAMESPACE
