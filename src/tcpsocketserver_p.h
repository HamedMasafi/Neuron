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

#ifndef NEURONTCPSOCKETSERVER_H
#define NEURONTCPSOCKETSERVER_H

#include <QtNetwork/QTcpServer>

#include "global.h"

NEURON_BEGIN_NAMESPACE

class TcpSocketServer : public QTcpServer
{
    Q_OBJECT

public:
    TcpSocketServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:
    void newIncomingConnection(qintptr socketDescriptor);
};

NEURON_END_NAMESPACE

#endif // NEURONTCPSOCKETSERVER_H
