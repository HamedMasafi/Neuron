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

#include "noronabstracthub.h"
#include "noronsharedobject.h"

#include <QtCore/QDebug>

#include <NoronServer>

NORON_BEGIN_NAMESPACE

bool NoronSharedObject::autoDelete() const
{
    return _autoDelete;
}

void NoronSharedObject::setAutoDelete(bool autoDelete)
{
    _autoDelete = autoDelete;
}

NoronSharedObject::NoronSharedObject(QObject *parent) : NoronPeer(parent),
    _activeHub(0), _deactiveHub(0)
{

}

NoronSharedObject::NoronSharedObject(NoronAbstractHub *hub, QObject *parent) :
    NoronPeer(parent), _activeHub(0), _deactiveHub(0)
{
    attachHub(hub);
}

void NoronSharedObject::attachHub(NoronAbstractHub *hub)
{    
    if(hubs.contains(hub)) {
        return;
    }

//    if(!qobject_cast<NoronServer*>(hub)){
        hubs.insert(hub);
        hubAdded(hub);
        sync(hub);

        qRegisterMetaType<NoronAbstractHub::Status>();
        connect(hub, &NoronAbstractHub::statusChanged,
                this, &NoronSharedObject::hub_statusChanged);
//    }
    hub->attachSharedObject(this);

#ifdef NORON_SERVER
    invokeOnPeer("attached");
#endif
}

void NoronSharedObject::detachHub(NoronAbstractHub *hub)
{
    if (!hub)
        return;

//    if(qobject_cast<NoronServer*>(hub))
//        return;

    //hubsLock.lock();
    if (hubs.remove(hub)){
        hubRemoved(hub);
        hub->detachSharedObject(this);

        if(!hubs.count() && autoDelete()){
            deleteLater();
        }

#ifdef NORON_SERVER
    invokeOnPeer("detached");
#endif
    }
    //hubsLock.unlock();
}

bool NoronSharedObject::setActiveHub(NoronAbstractHub *hub)
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

bool NoronSharedObject::setAllHubsActiveExcept(NoronAbstractHub *hub)
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

//void NoronSharedObject::setHub(NoronAbstractHub *hub)
//{
//    if (m_hub == hub)
//        return;

//    m_hub = hub;
//    emit hubChanged(hub);
//    hub->addSharedObject(this);
//}

//BC
//const QString NoronSharedObject::peerName()
//{
//    return NoronPeer::peerName();
//}

void NoronSharedObject::hubAdded(NoronAbstractHub *hub)
{
    Q_UNUSED(hub);
}

void NoronSharedObject::hubRemoved(NoronAbstractHub *hub)
{
    Q_UNUSED(hub);
}

void NoronSharedObject::hub_statusChanged(NoronAbstractHub::Status status)
{
    Q_UNUSED(status);
    NoronAbstractHub *hub = qobject_cast<NoronAbstractHub*>(sender());

    if (hub->inherits("NoronServer"))
        return;

    if(hub && hub->status() == NoronAbstractHub::Unconnected)
        detachHub(hub);
}

qlonglong NoronSharedObject::invokeOnPeer(QString methodName,
                                          QVariant val0, QVariant val1,
                                          QVariant val2, QVariant val3,
                                          QVariant val4, QVariant val5,
                                          QVariant val6, QVariant val7,
                                          QVariant val8, QVariant val9)
{
    //hubsLock.lock();

    QSet<NoronAbstractHub*> tmpHubs;;

    if(_activeHub){
        tmpHubs.insert(_activeHub);
    }else{
        tmpHubs = hubs;
        if(hub())
            tmpHubs.insert(hub());

        if(_deactiveHub)
            tmpHubs.remove(_deactiveHub);
    }

    foreach (NoronAbstractHub *hub, tmpHubs) {
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

void NoronSharedObject::sync(NoronAbstractHub *hub)
{
    if (hub->status() != NoronAbstractHub::Connected)
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

NORON_END_NAMESPACE
