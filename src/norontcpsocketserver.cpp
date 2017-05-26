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

#include <QtCore/QDebug>
#include <QtCore/QDebug>

#include "norontcpsocketserver_p.h"

NORON_BEGIN_NAMESPACE

NoronTcpSocketServer::NoronTcpSocketServer(QObject *parent) : QTcpServer(parent)
{
#ifdef NORON_MAX_PENDING_CONNECTIONS
    setMaxPendingConnections(NORON_MAX_PENDING_CONNECTIONS);
#else
    setMaxPendingConnections(100);
#endif
}

void NoronTcpSocketServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "NoronTcpSocketServer::incomingConnection";
    emit newIncomingConnection(socketDescriptor);
}

NORON_END_NAMESPACE
