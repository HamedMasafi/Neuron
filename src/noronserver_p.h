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

#ifndef NORONSERVER_P_H
#define NORONSERVER_P_H

#include "noronserver.h"

QT_BEGIN_NAMESPACE

class NoronServerPrivate{
    NoronServer *q_ptr;
    Q_DECLARE_PUBLIC(NoronServer)

public:
    NoronServerPrivate(NoronServer *parent);

    NoronTcpSocketServer *serverSocket;
    QSet<NoronPeer*> peers;
    QSet<NoronAbstractHub*> hubs;
    QHash<QString, NoronSharedObject*> sharedPeers;
    int typeId;
    NoronAbstractSerializer* serializer;
    NoronServer::ServerType serverType;
    qlonglong peerId;
};

QT_END_NAMESPACE

#endif // NORONSERVER_P_H
