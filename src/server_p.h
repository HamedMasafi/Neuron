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

#ifndef NEURONSERVER_P_H
#define NEURONSERVER_P_H

#include "server.h"
#include <QSharedData>

NEURON_BEGIN_NAMESPACE

class TcpSocketServer;
class ServerPrivate : public QSharedData {
    Server *q_ptr;
    Q_DECLARE_PUBLIC(Server)

public:
    ServerPrivate(Server *parent);

    TcpSocketServer *serverSocket;
    QSet<Peer*> peers;
    QHash<qlonglong, AbstractHub*> hubs;
    QHash<QString, SharedObject*> sharedPeers;

    int typeId;
    AbstractSerializer* serializer;
    Server::ServerType serverType;
    qlonglong hubId;
    quint32 reconnectTimeout;
};

NEURON_END_NAMESPACE

#endif // NEURONSERVER_P_H
