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

#include <QEventLoop>
#include <QtCore/QDebug>
#include <QtNetwork/QTcpSocket>

#include "neuronabstracthub_p.h"
#include "neuronserverhub.h"
#include "neuronserverhub_p.h"

NEURON_BEGIN_NAMESPACE

NeuronServerHubPrivate::NeuronServerHubPrivate(NeuronServerHub *parent) : q_ptr(parent), serverThread(0), connectionEventLoop(0)
{

}

NeuronServerHub::NeuronServerHub(QObject *parent) : NeuronAbstractHub(parent),
    d_ptr(new NeuronServerHubPrivate(this))
{

}

NeuronServerHub::NeuronServerHub(NeuronAbstractSerializer *serializer, QObject *parent) : NeuronAbstractHub(serializer, parent),
    d_ptr(new NeuronServerHubPrivate(this))
{
}

NeuronServerHub::NeuronServerHub(QTcpSocket *socket, QObject *parent) : NeuronAbstractHub(parent),
    d_ptr(new NeuronServerHubPrivate(this))
{
    this->socket = socket;
}

NeuronServerHub::~NeuronServerHub()
{
//    QList<NeuronSharedObject *> soList = sharedObjects();
//    foreach (NeuronSharedObject *so, soList) {
//        if(so)
//        removeSharedObject(so);
//    }

//    while(sharedObjects().count()){
//        removeSharedObject(sharedObjects().at(0));
//    }
    auto so = sharedObjectHash();
    QHashIterator<const QString, NeuronSharedObject*> i(so);
    while (i.hasNext()) {
        i.next();
//        cout << i.key() << ": " << i.value() << endl;
        detachSharedObject(i.value());
    }

    delete d_ptr;
}

NeuronServerThread *NeuronServerHub::serverThread() const
{
    Q_D(const NeuronServerHub);

    return d->serverThread;
}

qlonglong NeuronServerHub::hi(qlonglong hubId)
{
    initalizeMutex.lock();
    Q_D(NeuronServerHub);

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

bool NeuronServerHub::setSocketDescriptor(qintptr socketDescriptor, bool waitForConnect)
{
    bool ok = socket->setSocketDescriptor(socketDescriptor);

    if(waitForConnect)
        socket->waitForReadyRead();

    return ok;
}

void NeuronServerHub::setServerThread(NeuronServerThread *serverThread)
{
    Q_D(NeuronServerHub);

    if(d->serverThread != serverThread)
        d->serverThread = serverThread;
}

void NeuronServerHub::beginConnection()
{
    K_TRACE_DEBUG;
    Q_D(NeuronServerHub);
    d->connectionEventLoop = new QEventLoop;
    K_REG_OBJECT(d->connectionEventLoop);
    d->connectionEventLoop->exec();
}

NEURON_END_NAMESPACE
