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

#ifndef NEURONSERVER_H
#define NEURONSERVER_H

#include <QtCore/QObject>
#include "abstracthub.h"

NEURON_BEGIN_NAMESPACE

class Peer;
class ServerPrivate;
class AbstractSerializer;
class NEURON_EXPORT Server : public AbstractHub
{
    Q_OBJECT

    ServerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(Server)

    Q_PROPERTY(int typeId READ typeId WRITE setTypeId NOTIFY typeIdChanged)
    Q_PROPERTY(ServerType serverType READ serverType WRITE setServerType NOTIFY serverTypeChanged)
    Q_PROPERTY(quint32 reconnectTimeout READ reconnectTimeout WRITE setReconnectTimeout NOTIFY reconnectTimeoutChanged)

public:
    explicit Server(QObject *parent = 0);
    explicit Server(qint16 port, QObject *parent = 0);
    virtual ~Server();

    enum ServerType{
        SingleThread,
        MultiThread
    };
    Q_ENUM(ServerType)

    template <typename T> void registerType(){
        setTypeId(qRegisterMetaType<T>());
    }

    QSet<Peer *> peers() const;
    int typeId() const;
    ServerType serverType() const;
    void startServer(qint16 port);
    quint32 reconnectTimeout() const;
    bool isListening() const;

signals:
    void peerConnected(Peer *peer);
    void peerDisconnected(Peer *peer);
    void typeIdChanged(int typeId);
    void serverTypeChanged(ServerType serverType);

    void reconnectTimeoutChanged(quint32 reconnectTimeout);

private slots:
    void hub_connected();
    void hub_disconnected();
    void server_newIncomingConnection(qintptr socketDescriptor);

public slots:
    void setTypeId(int typeId);
    void setServerType(ServerType serverType);
    void setReconnectTimeout(quint32 reconnectTimeout);
};

NEURON_END_NAMESPACE

#endif // NEURONSERVER_H
