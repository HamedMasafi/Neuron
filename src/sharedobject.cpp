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

#include "abstracthub.h"
#include "sharedobject.h"

#include <QtCore/QDebug>
#include <QtCore/QThread>

#include <QMetaProperty>
#include <Server>

NEURON_BEGIN_NAMESPACE

bool SharedObject::autoDelete() const
{
    return _autoDelete;
}

void SharedObject::setAutoDelete(bool autoDelete)
{
    _autoDelete = autoDelete;
}

void SharedObject::registerSender(QThread *t, Peer *peer)
{
    qDebug() << "register sender" << t << peer;
    senderPeers.insert(t, peer);
}

void SharedObject::unregisterSender(QThread *t)
{
    senderPeers.remove(t);
}

Peer *SharedObject::senderPeer() const
{
    qDebug() << "get sender" << QThread::currentThread();
    return senderPeers.value(QThread::currentThread());
}

SharedObject::SharedObject(QObject *parent) : Peer(parent),
    _activeHub(nullptr), _deactiveHub(nullptr)
{

}

SharedObject::SharedObject(AbstractHub *hub, QObject *parent) :
    Peer(parent), _activeHub(nullptr), _deactiveHub(nullptr)
{
    attachHub(hub);
}

void SharedObject::attachHub(AbstractHub *hub)
{    
    if(hubs.contains(hub)) {
        return;
    }

//    if(!qobject_cast<Server*>(hub)){
        hubs.insert(hub);
        hubAdded(hub);
        sync(hub);

//        qRegisterMetaType<NEURON_WRAP_NAMESPACE(AbstractHub::Status)>("AbstractHub::Status");
        connect(hub, &AbstractHub::statusChanged,
                this, &SharedObject::hub_statusChanged);
//    }
    hub->attachSharedObject(this);

#ifdef NEURON_SERVER
    invokeOnPeer("attached");
#endif
}

void SharedObject::detachHub(AbstractHub *hub)
{
    if (!hub)
        return;

//    if(qobject_cast<Server*>(hub))
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

bool SharedObject::setActiveHub(AbstractHub *hub)
{
    if(!hub){
        _activeHub = nullptr;
        return true;
    }

    if(hubs.contains(hub)){
        _activeHub = hub;
        _deactiveHub = nullptr;
        return true;
    }
    return false;
}

bool SharedObject::setAllHubsActiveExcept(AbstractHub *hub)
{
    if(!hub){
        _deactiveHub = nullptr;
        return true;
    }

    if(hubs.contains(hub)){
        _deactiveHub = hub;
        _activeHub = nullptr;
        return true;
    }
    return false;
}

//void SharedObject::setHub(AbstractHub *hub)
//{
//    if (m_hub == hub)
//        return;

//    m_hub = hub;
//    emit hubChanged(hub);
//    hub->addSharedObject(this);
//}

//BC
//const QString SharedObject::peerName()
//{
//    return Peer::peerName();
//}

void SharedObject::hubAdded(AbstractHub *hub)
{
    Q_UNUSED(hub);
}

void SharedObject::hubRemoved(AbstractHub *hub)
{
    Q_UNUSED(hub);
}

void SharedObject::hub_statusChanged(AbstractHub::Status status)
{
    Q_UNUSED(status);
    AbstractHub *hub = qobject_cast<AbstractHub*>(sender());

    if (hub->inherits("Server"))
        return;

    if(hub && hub->status() == AbstractHub::Unconnected)
        detachHub(hub);
}

qlonglong SharedObject::invokeOnPeer(QString methodName,
                                          QVariant val0, QVariant val1,
                                          QVariant val2, QVariant val3,
                                          QVariant val4, QVariant val5,
                                          QVariant val6, QVariant val7,
                                          QVariant val8, QVariant val9)
{
    //hubsLock.lock();

    QSet<AbstractHub*> tmpHubs;;

    if(_activeHub){
        tmpHubs.insert(_activeHub);
    }else{
        tmpHubs = hubs;
        if(hub())
            tmpHubs.insert(hub());

        if(_deactiveHub)
            tmpHubs.remove(_deactiveHub);
    }

    foreach (AbstractHub *hub, tmpHubs) {
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

void SharedObject::sync(AbstractHub *hub)
{
    if (hub->status() != AbstractHub::Connected)
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
