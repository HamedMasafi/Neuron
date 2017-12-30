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

#include "neuronserverthread.h"
#include "neuronserverhub.h"

#include <QTcpSocket>

NEURON_BEGIN_NAMESPACE

NeuronServerThread::NeuronServerThread(qintptr socketDescriptor, QObject *parent) : QThread(parent),
    _hub(0), _isStarted(false)
{
    this->socketDescriptor = socketDescriptor;
}

NeuronServerThread::~NeuronServerThread()
{
//    if(_hub)
//        _hub->deleteLater();
}

bool NeuronServerThread::isStarted() const
{
    return _isStarted;
}

void NeuronServerThread::run()
{
    K_TRACE_DEBUG;
    //TODO: pass serializer to here!
    _hub = new NeuronServerHub;
    _hub->setSocketDescriptor(this->socketDescriptor, false);
    _hub->setServerThread(this);

    K_REG_OBJECT(_hub);

    _isStarted = true;

    exec();

    K_TRACE_DEBUG;
}

NeuronServerHub *NeuronServerThread::hub()
{
    return _hub;
}

NEURON_END_NAMESPACE
