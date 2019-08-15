/**************************************************************************
**
** This file is part of .
** https://github.com/HamedMasafi/
**
**  is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
**  is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with .  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#include <QtCore/QDebug>
#include <QtCore/QDebug>

#include "tcpsocketserver_p.h"

NEURON_BEGIN_NAMESPACE

TcpSocketServer::TcpSocketServer(QObject *parent) : QTcpServer(parent)
{
#ifdef NEURON_MAX_PENDING_CONNECTIONS
    setMaxPendingConnections(NEURON_MAX_PENDING_CONNECTIONS);
#else
    setMaxPendingConnections(100);
#endif
}

void TcpSocketServer::incomingConnection(qintptr socketDescriptor)
{
    emit newIncomingConnection(socketDescriptor);
}

NEURON_END_NAMESPACE
