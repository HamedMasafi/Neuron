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

#include "neuronabstracthub.h"
#include "neuronsharedobject.h"

#include <QtCore/QDebug>
#include <QtCore/QThread>

#include <NeuronServer>

NEURON_BEGIN_NAMESPACE

bool NeuronSharedObject::autoDelete() const
{
    return _autoDelete;
}

void NeuronSharedObject::setAutoDelete(bool autoDelete)
{
    _autoDelete = autoDelete;
}

void NeuronSharedObject::registerSender(QThread *t, NeuronPeer *peer)
{
    senderPeers.insert(t, peer);
}

void NeuronSharedObject::unregisterSender(QThread *t)
{
    senderPeers.remove(t);
}

NeuronPeer *NeuronSharedObject::senderPeer() const
{
    return senderPeers.value(QThread::currentThread());
}

NeuronSharedObject::NeuronSharedObject(QObject *parent) : NeuronPeer(parent),
    _activeHub(0), _deactiveHub(0)
{

}

NeuronSharedObject::NeuronSharedObject(NeuronAbstractHub *hub, QObject *parent) :
    NeuronPeer(parent), _activeHub(0), _deactiveHub(0)
{
    attachHub(hub);
}

void NeuronSharedObject::attachHub(NeuronAbstractHub *hub)
{    
    if(hubs.contains(hub)) {
        return;
    }

//    if(!qobject_cast<NeuronServer*>(hub)){
        hubs.insert(hub);
        hubAdded(hub);
        sync(hub);

        qRegisterMetaType<NeuronAbstractHub::Status>();
        connect(hub, &NeuronAbstractHub::statusChanged,
                this, &NeuronSharedObject::hub_statusChanged);
//    }
    hub->attachSharedObject(this);

#ifdef NEURON_SERVER
    invokeOnPeer("attached");
#endif
}

void NeuronSharedObject::detachHub(NeuronAbstractHub *hub)
{
    if (!hub)
        return;

//    if(qobject_cast<NeuronServer*>(hub))
//        return;

    //hubsLock.lock();
    if (hubs.remove(hub)){
        hubRemoved(hub);
        hub->detachSharedObject(this);

        if(!hubs.count() && autoDelete()){
            deleteLater();
        }

#ifdef NEURON_SERVER
    invokeOnPeer("detached");
#endif
    }
    //hubsLock.unlock();
}

bool NeuronSharedObject::setActiveHub(NeuronAbstractHub *hub)
{
    if(!hub){
        _activeHub = 0;
        return true;
    }

    if(hubs.contains(hub)){
        _activeHub = hub;
        _deactiveHub = 0;
        return true;
    }
    return false;
}

bool NeuronSharedObject::setAllHubsActiveExcept(NeuronAbstractHub *hub)
{
    if(!hub){
        _deactiveHub = 0;
        return true;
    }

    if(hubs.contains(hub)){
        _deactiveHub = hub;
        _activeHub = 0;
        return true;
    }
    return false;
}

//void NeuronSharedObject::setHub(NeuronAbstractHub *hub)
//{
//    if (m_hub == hub)
//        return;

//    m_hub = hub;
//    emit hubChanged(hub);
//    hub->addSharedObject(this);
//}

//BC
//const QString NeuronSharedObject::peerName()
//{
//    return NeuronPeer::peerName();
//}

void NeuronSharedObject::hubAdded(NeuronAbstractHub *hub)
{
    Q_UNUSED(hub);
}

void NeuronSharedObject::hubRemoved(NeuronAbstractHub *hub)
{
    Q_UNUSED(hub);
}

void NeuronSharedObject::hub_statusChanged(NeuronAbstractHub::Status status)
{
    Q_UNUSED(status);
    NeuronAbstractHub *hub = qobject_cast<NeuronAbstractHub*>(sender());

    if (hub->inherits("NeuronServer"))
        return;

    if(hub && hub->status() == NeuronAbstractHub::Unconnected)
        detachHub(hub);
}

qlonglong NeuronSharedObject::invokeOnPeer(QString methodName,
                                          QVariant val0, QVariant val1,
                                          QVariant val2, QVariant val3,
                                          QVariant val4, QVariant val5,
                                          QVariant val6, QVariant val7,
                                          QVariant val8, QVariant val9)
{
    //hubsLock.lock();

    QSet<NeuronAbstractHub*> tmpHubs;;

    if(_activeHub){
        tmpHubs.insert(_activeHub);
    }else{
        tmpHubs = hubs;
        if(hub())
            tmpHubs.insert(hub());

        if(_deactiveHub)
            tmpHubs.remove(_deactiveHub);
    }

    foreach (NeuronAbstractHub *hub, tmpHubs) {
        if(hub->isMultiThread()) {
            hub->metaObject()->invokeMethod(hub,
                                            QT_STRINGIFY(invokeOnPeer),
                                            Q_ARG(QString, peerName()),
                                            Q_ARG(QString, methodName),
                                            Q_ARG(QVariant, val0),
                                            Q_ARG(QVariant, val1),
                                            Q_ARG(QVariant, val2),
                                            Q_ARG(QVariant, val3),
                                            Q_ARG(QVariant, val4),
                                            Q_ARG(QVariant, val5),
                                            Q_ARG(QVariant, val6),
                                            Q_ARG(QVariant, val7));
        } else {
            qlonglong v = hub->invokeOnPeer(
                        peerName(),
                        methodName,
                        val0, val1, val2, val3, val4,
                        val5, val6, val7, val8, val9);
            if (tmpHubs.count() == 1)
                return v;
        }
    }

    //hubsLock.unlock();
    return 0;
}

void NeuronSharedObject::sync(NeuronAbstractHub *hub)
{
    if (hub->status() != NeuronAbstractHub::Connected)
        return;

    hub->beginTransaction();

    int pcount = metaObject()->propertyCount();
    for (int i = 0; i < pcount; i++) {
        QMetaProperty p = metaObject()->property(i);

        if (!p.isUser())
            continue;

        QString w = p.name();
        w[0] = w[0].toUpper();

        hub->invokeOnPeer(peerName(), "set" + w, p.read(this));
    }
    QMetaObject::invokeMethod(hub, "commit", Qt::QueuedConnection);
}

NEURON_END_NAMESPACE
