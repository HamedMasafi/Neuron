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

#ifndef SERVERMODEL_H
#define SERVERMODEL_H

#include "global.h"
#include "peer.h"

#include <QAbstractListModel>
#include <functional>

NEURON_BEGIN_NAMESPACE

class Server;
class NEURON_EXPORT ServerModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool showAddress READ showAddress WRITE setShowAddress NOTIFY showAddressChanged)

    typedef std::function<QVariant(QVariant)> PropertyTranslator;

    QMap<QString, QString> _props;
    QString _addressText;
    QMap<QString, PropertyTranslator> _translators;

    QStringList _properties;
    Neuron::Server *_server;
    QList<Peer*> _peers;


    bool m_showAddress;

public:
    ServerModel(Neuron::Server *server);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setHeaderText(const QString &propertyName, const QString &text);

    Neuron::Peer *peer(const QModelIndex &index) const;

    void invalidateProperty(Peer *peer, const QString &propertyName);
    void installTranslator(const QString &propertyName, PropertyTranslator translator);

    bool showAddress() const;

public slots:
    void setShowAddress(bool showAddress);

private slots:
    void server_peerConnected(Peer *peer);
    void server_peerDisconnected(Peer *peer);

signals:
    void peerAdded(Peer *peer);
    void showAddressChanged(bool showAddress);
};

NEURON_END_NAMESPACE

#endif // SERVERMODEL_H
