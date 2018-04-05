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

#ifndef NEURONSERVERHUB_H
#define NEURONSERVERHUB_H

#include <QtCore/qglobal.h>

#include "abstracthub.h"

NEURON_BEGIN_NAMESPACE

class ServerThread;
class ServerHubPrivate;
class NEURON_EXPORT ServerHub : public AbstractHub
{
    Q_OBJECT

    ServerHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(ServerHub)

public:
    ServerHub(QObject *parent = 0);
    ServerHub(AbstractSerializer *serializer, QObject *parent = 0);
    ServerHub(QTcpSocket *socket, QObject *parent = 0);

    virtual ~ServerHub();

    ServerThread *serverThread() const;

private slots:
    qlonglong hi(qlonglong hubId);

public slots:
    bool setSocketDescriptor(qintptr socketDescriptor, bool waitForConnect = false);
    void setServerThread(ServerThread *serverThread);

    // AbstractHub interface
protected:
    void beginConnection();
};

NEURON_END_NAMESPACE

#endif // NEURONSERVERHUB_H
