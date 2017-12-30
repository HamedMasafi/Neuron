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

#ifndef NEURON_SHARED_OBJECT
#include "syntax/syntax_peer.h"
#endif

#ifndef NEURONPEER_H
#define NEURONPEER_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "neuronabstracthub.h"
#include "neuronglobal.h"
#include "neuronremotecall_p.h"

NEURON_BEGIN_NAMESPACE

class NeuronAbstractHub;
class NeuronRemoteCallBase;
class NEURON_EXPORT NeuronPeer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NeuronAbstractHub* hub READ hub WRITE setHub NOTIFY hubChanged)

    QString _peerName;

public:
    explicit NeuronPeer(QObject *parent = 0);
    NeuronPeer(NeuronAbstractHub *hub, QObject *parent = 0);
    virtual ~NeuronPeer();

    NeuronAbstractHub* hub() const;

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

    const QString peerName() const;

protected:
    NeuronAbstractHub* m_hub;
    void addCall(qlonglong id, NeuronRemoteCallBase *call);
    void removeCall(qlonglong id);
    void setPeerName(const QString &name);

signals:
    void hubChanged(NeuronAbstractHub* hub);

private slots:
    void hub_disconnected();

public slots:
    void setHub(NeuronAbstractHub* hub);
};

NEURON_END_NAMESPACE

#endif // NEURONPEER_H
