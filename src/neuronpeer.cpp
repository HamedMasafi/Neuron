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

#include <QtCore/QMetaObject>
#include <QtCore/QDebug>

#include "neuronpeer.h"
#include "neuronabstracthub.h"
#include "neuronsharedobject.h"

NEURON_BEGIN_NAMESPACE

/*!
 * \brief NeuronPeer
 * This is base class of all peers.
 */

NeuronPeer::NeuronPeer(QObject *parent)
    : QObject(parent), _peerName(QString::null), m_hub(0)
{
}

NeuronPeer::NeuronPeer(NeuronAbstractHub *hub, QObject *parent)
    : QObject(parent), _peerName(QString::null), m_hub(0)
{
    setHub(hub);
}

NeuronPeer::~NeuronPeer()
{
    //    if(hub())
    //        hub()->deleteLater();
}

NeuronAbstractHub *NeuronPeer::hub() const
{
    return m_hub;
}

qlonglong NeuronPeer::invokeOnPeer(QString methodName, QVariant val0,
                                  QVariant val1, QVariant val2, QVariant val3,
                                  QVariant val4, QVariant val5, QVariant val6,
                                  QVariant val7, QVariant val8, QVariant val9)
{
    // Object is transfered!!!
    if (!hub())
        return 0;

    if (hub()->status() != NeuronAbstractHub::Connected)
        return 0;

    if (hub()->isMultiThread()) {
        //        qlonglong ret;
        bool ok = hub()->metaObject()->invokeMethod(
            hub(), QT_STRINGIFY(invokeOnPeer),
            //                                          Qt::DirectConnection,
            //                                          Q_RETURN_ARG(qlonglong,
            //                                          ret),
            Q_ARG(QString, peerName()), Q_ARG(QString, methodName),
            Q_ARG(QVariant, val0), Q_ARG(QVariant, val1), Q_ARG(QVariant, val2),
            Q_ARG(QVariant, val3), Q_ARG(QVariant, val4), Q_ARG(QVariant, val5),
            Q_ARG(QVariant, val6), Q_ARG(QVariant, val7) /*,
                                                                        QGenericArgument(val8.typeName(), val8.data()),
                                                                        QGenericArgument(val9.typeName(), val9.data())*/);
        //        return ret;
        if (!ok)
            qWarning("Unable to invoke method: %s::%s", qPrintable(peerName()),
                     qPrintable(methodName));
        return 0;
    } else {
        return hub()->invokeOnPeer(metaObject()->className(), methodName, val0,
                                   val1, val2, val3, val4, val5, val6, val7,
                                   val8, val9);
    }
}

const QString NeuronPeer::peerName() const
{
    return _peerName;
}

void NeuronPeer::addCall(qlonglong id, NeuronRemoteCallBase *call)
{
    hub()->_calls.insert(id, call);
}

void NeuronPeer::removeCall(qlonglong id)
{
    delete hub()->_calls[id];
    hub()->_calls.remove(id);
}

void NeuronPeer::setPeerName(const QString &name)
{
    _peerName = name;
}

void NeuronPeer::hub_disconnected()
{
    m_hub = 0;
}

void NeuronPeer::setHub(NeuronAbstractHub *hub)
{
    if (m_hub == hub)
        return;

    m_hub = hub;

    if (hub) {
        connect(hub, &NeuronAbstractHub::disconnected, this,
                &NeuronPeer::hub_disconnected);

        NeuronSharedObject *so = qobject_cast<NeuronSharedObject *>(this);

        if (so)
            hub->attachSharedObject(so);
        else
            hub->setPeer(this);

        emit hubChanged(hub);
    }
}

NEURON_END_NAMESPACE
