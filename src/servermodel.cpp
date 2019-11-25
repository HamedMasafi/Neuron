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
#include <QHostAddress>

NEURON_BEGIN_NAMESPACE

ServerModel::ServerModel(Server *server) :
    QAbstractListModel(server), _server(server)
{

    auto mo = QMetaType::metaObjectForType(server->typeId());
    for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
        auto p = mo->property(i);
        _properties.append(p.name());
        _props.insert(p.name(), p.name());
    }
    connect(server, &Server::peerConnected, this, &ServerModel::server_peerConnected);
    connect(server, &Server::peerDisconnected, this, &ServerModel::server_peerDisconnected);
}

int ServerModel::rowCount(const QModelIndex &parent) const
{
    return _peers.count();
}

QVariant ServerModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole || !index.isValid())
        return QVariant();

    auto peer = _peers.at(index.row());

    QString propName;
    QVariant value;
    if (m_showAddress && index.column() == 0) {
        propName = ":address";
        return peer->hub()->localAddress().toString();
    } else {
        propName = _props.keys().at(index.column() - (m_showAddress ? 1 : 0));
        value = peer->property(propName.toLatin1());
        if (_translators.contains(propName))
            return _translators.value(propName)(value);
    }

    return value;
}

int ServerModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _properties.count() + (m_showAddress ? 1 : 0);
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

    emit peerAdded(peer);
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

    if (orientation == Qt::Horizontal) {
        if (section == 0 && m_showAddress)
            return _addressText;
        return _props.values().at(section - (m_showAddress ? 1 : 0));
    } else {
        return section + 1;
    }
}

void ServerModel::setHeaderText(const QString &propertyName, const QString &text)
{
    if (propertyName == ":address")
        _addressText = text;
    if (_props.contains(propertyName))
        _props[propertyName] = text;
}

Peer *ServerModel::peer(const QModelIndex &index) const
{
    if (!index.isValid())
        return nullptr;
    if (index.row() < 0 || index.row() > _peers.count() - 1)
        return nullptr;
    return _peers.at(index.row());
}

void ServerModel::invalidateProperty(Peer *peer, const QString &propertyName)
{
    auto peerIndex = _peers.indexOf(peer);
    auto propIndex = _props.values().indexOf(propertyName);

    if (peerIndex != -1 && propIndex != -1) {
        auto idx = index(peerIndex, propIndex);
        emit dataChanged(idx, idx);
    }
}

void ServerModel::installTranslator(const QString &propertyName, ServerModel::PropertyTranslator translator)
{
    _translators.insert(propertyName, translator);
}

bool ServerModel::showAddress() const
{
    return m_showAddress;
}

void ServerModel::setShowAddress(bool showAddress)
{
    if (m_showAddress == showAddress)
        return;

    m_showAddress = showAddress;
    emit showAddressChanged(m_showAddress);
}

NEURON_END_NAMESPACE
