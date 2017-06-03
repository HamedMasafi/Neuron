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

NORON_BEGIN_NAMESPACE

bool NoronSharedObject::autoDelete() const
{
    return _autoDelete;
}

void NoronSharedObject::setAutoDelete(bool autoDelete)
{
    _autoDelete = autoDelete;
}

NoronSharedObject::NoronSharedObject(QObject *parent) : NoronPeer(parent), _activeHub(0), _deactiveHub(0)
{

}

NoronSharedObject::NoronSharedObject(NoronAbstractHub *hub, QObject *parent) : NoronPeer(parent), _activeHub(0), _deactiveHub(0)
{
    attachHub(hub);
}

void NoronSharedObject::attachHub(NoronAbstractHub *hub)
{    
    if(hubs.contains(hub))
        return;

    if(!hub->inherits(QT_STRINGIFY(NoronServer))){
        hubs.insert(hub);
        hubAdded(hub);

        connect(hub, &NoronAbstractHub::statusChanged, this, &NoronSharedObject::hub_statusChanged);
    }
    hub->attachSharedObject(this);
}

void NoronSharedObject::detachHub(NoronAbstractHub *hub)
{
    if (!hub)
        return;

    if (hubs.remove(hub)){
        hubRemoved(hub);
        hub->detachSharedObject(this);

        qDebug() << "NoronSharedObject::detachHub" << objectName() <<"; " << hub->objectName();
        if(!hubs.count() && autoDelete()){
            qDebug() << "Object" << objectName() <<"market for deletation";
            deleteLater();
        }
    }
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
    NoronAbstractHub *hub = qobject_cast<NoronAbstractHub*>(sender());

    if(hub && status == NoronAbstractHub::Unconnected){
        detachHub(hub);
    }
}

qlonglong NoronSharedObject::invokeOnPeer(QString methodName, QVariant val0, QVariant val1, QVariant val2, QVariant val3, QVariant val4, QVariant val5, QVariant val6, QVariant val7, QVariant val8, QVariant val9)
{
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
        qDebug() << "invoking on" << hub->objectName() << hub->metaObject()->className();
        if(hub->isMultiThread())
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
        else
            return hub->invokeOnPeer(
                        peerName(),
                        methodName,
                        val0, val1, val2, val3, val4,
                        val5, val6, val7, val8, val9);
    }

    return 0;
}

NORON_END_NAMESPACE
