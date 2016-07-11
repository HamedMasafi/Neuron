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

#include <QtCore/QMetaObject>
#include "noronpeer.h"
#include "noronabstracthub.h"

QT_BEGIN_NAMESPACE

/*!
 * \brief NoronPeer
 * This is base class of all peers.
 */

NoronPeer::NoronPeer(QObject *parent) : QObject(parent), m_hub(0)
{

}

NoronPeer::NoronPeer(NoronAbstractHub *hub, QObject *parent) : QObject(parent), m_hub(0)
{
    setHub(hub);
}

NoronAbstractHub *NoronPeer::hub() const
{
    return m_hub;
}

qlonglong NoronPeer::invokeOnPeer(QString methodName, QVariant val0, QVariant val1, QVariant val2, QVariant val3, QVariant val4, QVariant val5, QVariant val6, QVariant val7, QVariant val8, QVariant val9)
{
    //Object is transfered!!!
    if(!hub())
        return 0;

    if(hub()->isMultiThread()){
//        qlonglong ret;
        hub()->metaObject()->invokeMethod(hub(),
                                          QT_STRINGIFY(invokeOnPeer),
//                                          Qt::DirectConnection,
//                                          Q_RETURN_ARG(qlonglong, ret),
                                          Q_ARG(QString, peerName()),
                                          Q_ARG(QString, methodName),
                                          Q_ARG(QVariant, val0),
                                          Q_ARG(QVariant, val1),
                                          Q_ARG(QVariant, val2),
                                          Q_ARG(QVariant, val3),
                                          Q_ARG(QVariant, val4),
                                          Q_ARG(QVariant, val5),
                                          Q_ARG(QVariant, val6),
                                          Q_ARG(QVariant, val7)/*,
                                                                        QGenericArgument(val8.typeName(), val8.data()),
                                                                        QGenericArgument(val9.typeName(), val9.data())*/);
//        return ret;
        return 0;
    }else{
        return hub()->invokeOnPeer(
                    metaObject()->className(),
                    methodName,
                    val0, val1, val2, val3, val4,
                    val5, val6, val7, val8, val9);
    }
}

const QString NoronPeer::peerName()
{
    return QString("");
}

void NoronPeer::addCall(long id, NoronRemoteCallBase *call)
{
    hub()->_calls.insert(id, call);
}

void NoronPeer::removeCall(long id)
{
    hub()->_calls.remove(id);
}

void NoronPeer::setHub(NoronAbstractHub *hub)
{
    if (m_hub == hub)
        return;

    m_hub = hub;
    hub->setPeer(this);
    emit hubChanged(hub);
}

QT_END_NAMESPACE
