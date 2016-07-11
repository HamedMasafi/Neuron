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

#ifndef NORONSERVER_H
#define NORONSERVER_H

#include <QtCore/QObject>
#include "noronabstracthub.h"

QT_BEGIN_NAMESPACE

class NoronPeer;
class NoronServerPrivate;
class NoronAbstractSerializer;
class NORON_EXPORT NoronServer : public NoronAbstractHub
{
    Q_OBJECT

    NoronServerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(NoronServer)

    Q_PROPERTY(int typeId READ typeId WRITE setTypeId NOTIFY typeIdChanged)
    Q_PROPERTY(ServerType serverType READ serverType WRITE setServerType NOTIFY serverTypeChanged)

public:
    explicit NoronServer(QObject *parent = 0);
    explicit NoronServer(qint16 port, QObject *parent = 0);
    virtual ~NoronServer();

    enum ServerType{
        SingleThread,
        MultiThread
    };
    Q_ENUM(ServerType);

    template <typename T> void registerType(){
        setTypeId(qRegisterMetaType<T>());
    }

    QSet<NoronPeer *> peers();
    int typeId() const;
    ServerType serverType() const;

    void startServer(qint16 port);

signals:
    void peerConnected(NoronPeer *peer);
    void peerDisconnected(NoronPeer *peer);
    void typeIdChanged(int typeId);
    void serverTypeChanged(ServerType serverType);

private slots:
    void hub_disconnected();
    void server_newIncomingConnection(qintptr socketDescriptor);

public slots:
    void setTypeId(int typeId);
    void setServerType(ServerType serverType);
};

QT_END_NAMESPACE

#endif // NORONSERVER_H
