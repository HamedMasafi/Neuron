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

#include "server.h"
#include "servermodel.h"

#include <QMetaProperty>
#include <QDebug>

NEURON_BEGIN_NAMESPACE

ServerModel::ServerModel(Server *server) :
    QAbstractListModel(server), _server(server)
{

    auto mo = QMetaType::metaObjectForType(server->typeId());
    for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
        _properties.append(mo->property(i).name());
    }
    qDebug() << _properties;
    connect(server, &Server::peerConnected, this, &ServerModel::server_peerConnected);
    connect(server, &Server::peerDisconnected, this, &ServerModel::server_peerDisconnected);


    connect(server, &Neuron::Server::peerConnected, [this](Neuron::Peer *peer){
        qDebug() << ("Peer connected");
    });
}

int ServerModel::rowCount(const QModelIndex &parent) const
{
    return _peers.count();
}

QVariant ServerModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    return _peers.at(index.row())->property(_properties.at(index.column()).toLatin1());
}

int ServerModel::columnCount(const QModelIndex &parent) const
{
    return _properties.count();
}

void ServerModel::server_peerConnected(Peer *peer)
{
    auto i = _peers.count();
    connect(peer, &Peer::propertyChanged, [this, i](const QString &, const QVariant &){
        emit this->dataChanged(index(i, 0), index(i, _properties.count()));
    });
    beginInsertRows(QModelIndex(), i, i);
    _peers.append(peer);
    endInsertRows();
}

void ServerModel::server_peerDisconnected(Peer *peer)
{
    auto i = _peers.indexOf(peer);
    if (i == -1)
        return;
    beginRemoveRows(QModelIndex(), i, i);
    _peers.removeAt(i);
    endRemoveRows();
}

QVariant ServerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return _properties.at(section);
    else
        return section + 1;
}

Peer *ServerModel::peer(const QModelIndex &index) const
{
    if (!index.isValid())
        return nullptr;
    if (index.row() < 0 || index.row() > _peers.count() - 1)
        return nullptr;
    return _peers.at(index.row());
}

NEURON_END_NAMESPACE
