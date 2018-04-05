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

#ifndef NEURONCLIENTHUB_P_H
#define NEURONCLIENTHUB_P_H

#include "clienthub.h"

class QEventLoop;

NEURON_BEGIN_NAMESPACE

class ClientHubPrivate{
    ClientHub *q_ptr;
    Q_DECLARE_PUBLIC(ClientHub)

public:
    ClientHubPrivate(ClientHub *parent);

    quint16 port;               // port
    QString serverAddress;     // address of server
    bool isAutoReconnect;
    int reconnectTimerId;
    //TODO: delete event loop
    QEventLoop *connectionEventLoop;
};

NEURON_END_NAMESPACE

#endif // NEURONCLIENTHUB_P_H
