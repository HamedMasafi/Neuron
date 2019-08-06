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
#include <QtCore/QExplicitlySharedDataPointer>

#include "abstracthub.h"

NEURON_BEGIN_NAMESPACE

class ServerThread;
class ServerHubPrivate;
class NEURON_EXPORT ServerHub : public AbstractHub
{
    Q_OBJECT

    QExplicitlySharedDataPointer<ServerHubPrivate> d;

public:
    ServerHub(QObject *parent = nullptr);
    ServerHub(AbstractSerializer *serializer, QObject *parent = nullptr);
    ServerHub(QTcpSocket *socket, QObject *parent = nullptr);

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
