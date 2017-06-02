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

#include <QEventLoop>
#include <QtCore/QDebug>
#include <QtNetwork/QTcpSocket>

#include "noronabstracthub_p.h"
#include "noronserverhub.h"
#include "noronserverhub_p.h"

NORON_BEGIN_NAMESPACE

NoronServerHubPrivate::NoronServerHubPrivate(NoronServerHub *parent) : q_ptr(parent), serverThread(0), connectionEventLoop(0)
{

}

NoronServerHub::NoronServerHub(QObject *parent) : NoronAbstractHub(parent),
    d_ptr(new NoronServerHubPrivate(this))
{

}

NoronServerHub::NoronServerHub(NoronAbstractSerializer *serializer, QObject *parent) : NoronAbstractHub(serializer, parent),
    d_ptr(new NoronServerHubPrivate(this))
{
}

NoronServerHub::NoronServerHub(QTcpSocket *socket, QObject *parent) : NoronAbstractHub(parent),
    d_ptr(new NoronServerHubPrivate(this))
{
    this->socket = socket;
}

NoronServerHub::~NoronServerHub()
{
    Q_D(NoronServerHub);

//    QList<NoronSharedObject *> soList = sharedObjects();
//    foreach (NoronSharedObject *so, soList) {
//        if(so)
//        removeSharedObject(so);
//    }

//    while(sharedObjects().count()){
//        qDebug() << "removing " << sharedObjects().at(0);
//        removeSharedObject(sharedObjects().at(0));
//    }
    auto so = sharedObjectHash();
    QHashIterator<const QString, NoronSharedObject*> i(so);
    while (i.hasNext()) {
        i.next();
//        cout << i.key() << ": " << i.value() << endl;
        qDebug() << "removing " << i.key() << "from" << objectName();
        detachSharedObject(i.value());
    }

    delete d_ptr;
}

NoronServerThread *NoronServerHub::serverThread() const
{
    Q_D(const NoronServerHub);

    return d->serverThread;
}

qlonglong NoronServerHub::hi(qlonglong hubId)
{
    initalizeMutex.lock();
    Q_D(NoronServerHub);

    setHubId(hubId);
    emit connected();

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

bool NoronServerHub::setSocketDescriptor(qintptr socketDescriptor, bool waitForConnect)
{
    bool ok = socket->setSocketDescriptor(socketDescriptor);

    if(waitForConnect)
        socket->waitForReadyRead();

    return ok;
}

void NoronServerHub::setServerThread(NoronServerThread *serverThread)
{
    Q_D(NoronServerHub);

    if(d->serverThread != serverThread)
        d->serverThread = serverThread;
}

void NoronServerHub::beginConnection()
{
    K_TRACE_DEBUG;
    Q_D(NoronServerHub);
    d->connectionEventLoop = new QEventLoop;
    K_REG_OBJECT(d->connectionEventLoop);
    d->connectionEventLoop->exec();
}

NORON_END_NAMESPACE
