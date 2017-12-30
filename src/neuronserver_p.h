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

#ifndef NEURONSERVER_P_H
#define NEURONSERVER_P_H

#include "neuronserver.h"

NEURON_BEGIN_NAMESPACE

class NeuronServerPrivate{
    NeuronServer *q_ptr;
    Q_DECLARE_PUBLIC(NeuronServer)

public:
    NeuronServerPrivate(NeuronServer *parent);

    NeuronTcpSocketServer *serverSocket;
    QSet<NeuronPeer*> peers;
    QHash<qlonglong, NeuronAbstractHub*> hubs;
    QHash<QString, NeuronSharedObject*> sharedPeers;

    int typeId;
    NeuronAbstractSerializer* serializer;
    NeuronServer::ServerType serverType;
    qlonglong hubId;
    quint32 reconnectTimeout;
};

NEURON_END_NAMESPACE

#endif // NEURONSERVER_P_H
