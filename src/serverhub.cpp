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

#include <QEventLoop>
#include <QtCore/QDebug>
#include <QtNetwork/QTcpSocket>

#include "abstracthub_p.h"
#include "serverhub.h"
#include "serverhub_p.h"

NEURON_BEGIN_NAMESPACE

ServerHubPrivate::ServerHubPrivate(ServerHub *parent) : q_ptr(parent), serverThread(0), connectionEventLoop(0)
{

}

ServerHub::ServerHub(QObject *parent) : AbstractHub(parent),
    d_ptr(new ServerHubPrivate(this))
{

}

ServerHub::ServerHub(AbstractSerializer *serializer, QObject *parent) : AbstractHub(serializer, parent),
    d_ptr(new ServerHubPrivate(this))
{
}

ServerHub::ServerHub(QTcpSocket *socket, QObject *parent) : AbstractHub(parent),
    d_ptr(new ServerHubPrivate(this))
{
    this->socket = socket;
}

ServerHub::~ServerHub()
{
//    QList<SharedObject *> soList = sharedObjects();
//    foreach (SharedObject *so, soList) {
//        if(so)
//        removeSharedObject(so);
//    }

//    while(sharedObjects().count()){
//        removeSharedObject(sharedObjects().at(0));
//    }
    auto so = sharedObjectHash();
    QHashIterator<const QString, SharedObject*> i(so);
    while (i.hasNext()) {
        i.next();
//        cout << i.key() << ": " << i.value() << endl;
        detachSharedObject(i.value());
    }

    delete d_ptr;
}

ServerThread *ServerHub::serverThread() const
{
    Q_D(const ServerHub);

    return d->serverThread;
}

qlonglong ServerHub::hi(qlonglong hubId)
{
    initalizeMutex.lock();
    Q_D(ServerHub);

    setHubId(hubId);
//    emit connected();

    K_TRACE_DEBUG;
//    invokeOnPeer(THIS_HUB, "hi", hubId);
    if (d->connectionEventLoop) {
        d->connectionEventLoop->quit();
        d->connectionEventLoop->deleteLater();
    }

    initalizeMutex.unlock();
    setStatus(Connected);
    return this->hubId();
}

bool ServerHub::setSocketDescriptor(qintptr socketDescriptor, bool waitForConnect)
{
    bool ok = socket->setSocketDescriptor(socketDescriptor);

    if(waitForConnect)
        socket->waitForReadyRead();

    return ok;
}

void ServerHub::setServerThread(ServerThread *serverThread)
{
    Q_D(ServerHub);

    if(d->serverThread != serverThread)
        d->serverThread = serverThread;
}

void ServerHub::beginConnection()
{
    K_TRACE_DEBUG;
    Q_D(ServerHub);
    d->connectionEventLoop = new QEventLoop;
    K_REG_OBJECT(d->connectionEventLoop);
    d->connectionEventLoop->exec();
}

NEURON_END_NAMESPACE
