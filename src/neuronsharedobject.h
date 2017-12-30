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

#ifndef NEURONSHAREDOBJECT_H
#define NEURONSHAREDOBJECT_H

#include <QtCore/QMutex>
#include <QtCore/QSet>

#define NEURON_SHARED_OBJECT
#include "syntax/syntax_sharedobject.h"
#include "neuronabstracthub.h"
#include "neuronpeer.h"
#undef NEURON_SHARED_OBJECT

NEURON_BEGIN_NAMESPACE

//TODO: generate private class for me :-)
class NEURON_EXPORT NeuronSharedObject : public NeuronPeer
{
    Q_OBJECT

    NeuronAbstractHub *_activeHub;
    NeuronAbstractHub *_deactiveHub;
    bool _autoDelete;
    QMutex hubsLock;

public:
    NeuronSharedObject(QObject *parent = 0);
    NeuronSharedObject(NeuronAbstractHub *hub, QObject *parent = 0);

    void attachHub(NeuronAbstractHub *hub);
    void detachHub(NeuronAbstractHub *hub);
    bool setActiveHub(NeuronAbstractHub *hub);
    bool setAllHubsActiveExcept(NeuronAbstractHub *hub);

    QSet<NeuronAbstractHub*> hubs;

//    void setHub(NeuronAbstractHub* hub) /*Q_DECL_OVERRIDE*/;

    //BC
//    virtual const QString peerName() /*Q_DECL_OVERRIDE*/;
    virtual void hubAdded(NeuronAbstractHub *hub);
    virtual void hubRemoved(NeuronAbstractHub *hub);

    bool autoDelete() const;
    void setAutoDelete(bool autoDelete);

private slots:
    void hub_statusChanged(NeuronAbstractHub::Status status);

protected:
    qlonglong invokeOnPeer(
            QString methodName,
            QVariant val0 = QVariant(),
            QVariant val1 = QVariant(),
            QVariant val2 = QVariant(),
            QVariant val3 = QVariant(),
            QVariant val4 = QVariant(),
            QVariant val5 = QVariant(),
            QVariant val6 = QVariant(),
            QVariant val7 = QVariant(),
            QVariant val8 = QVariant(),
            QVariant val9 = QVariant());

    void sync(NeuronAbstractHub *hub);
signals:
#ifdef NEURON_CLIENT
    void attached();
    void detached();
#endif
};

NEURON_END_NAMESPACE

#endif // NEURONSHAREDOBJECT_H
