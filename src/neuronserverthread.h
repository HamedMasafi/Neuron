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

#ifndef NEURONSERVERTHREAD_H
#define NEURONSERVERTHREAD_H

#include <QThread>

#include "neuronserverhub.h"
#include "neuronglobal.h"

NEURON_BEGIN_NAMESPACE

class NeuronServerThread : public QThread
{
    qintptr socketDescriptor;
    NeuronServerHub *_hub;
    bool _isStarted;

public:
    explicit NeuronServerThread(qintptr socketDescriptor, QObject *parent = 0);
    ~NeuronServerThread();

    bool isStarted() const;
    void run();
    NeuronServerHub *hub();
};

NEURON_END_NAMESPACE

#endif // NEURONSERVERTHREAD_H
