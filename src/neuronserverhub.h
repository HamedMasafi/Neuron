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

#ifndef NEURONSERVERHUB_H
#define NEURONSERVERHUB_H

#include <QtCore/qglobal.h>

#include "neuronabstracthub.h"

NEURON_BEGIN_NAMESPACE

class NeuronServerThread;
class NeuronServerHubPrivate;
class NEURON_EXPORT NeuronServerHub : public NeuronAbstractHub
{
    Q_OBJECT

    NeuronServerHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(NeuronServerHub)

public:
    NeuronServerHub(QObject *parent = 0);
    NeuronServerHub(NeuronAbstractSerializer *serializer, QObject *parent = 0);
    NeuronServerHub(QTcpSocket *socket, QObject *parent = 0);

    virtual ~NeuronServerHub();

    NeuronServerThread *serverThread() const;

private slots:
    qlonglong hi(qlonglong hubId);

public slots:
    bool setSocketDescriptor(qintptr socketDescriptor, bool waitForConnect = false);
    void setServerThread(NeuronServerThread *serverThread);

    // NeuronAbstractHub interface
protected:
    void beginConnection();
};

NEURON_END_NAMESPACE

#endif // NEURONSERVERHUB_H
