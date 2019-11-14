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

#ifndef NEURON_SHARED_OBJECT
#include "syntax/syntax_peer.h"
#endif

#ifndef NEURONPEER_H
#define NEURONPEER_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "abstracthub.h"
#include "global.h"
#include "call.h"

NEURON_BEGIN_NAMESPACE

class AbstractHub;
class RemoteCallBase;
class AbstractCall;
class NEURON_EXPORT Peer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(AbstractHub* hub READ hub WRITE setHub NOTIFY hubChanged)

    QString _peerName;

public:
    explicit Peer(QObject *parent = nullptr);
    Peer(AbstractHub *hub, QObject *parent = nullptr);
    virtual ~Peer();

    AbstractHub* hub() const;

    qlonglong invokeOnPeer(
            QString methodName,
            QVariant val0 = QVariant(),
            QVariant val1 = QVariant(),
            QVariant val2 = QVariant(),
            QVariant val3 = QVariant(),
            QVariant val4 = QVariant(),
            QVariant val5 = QVariant(),
            QVariant val6 = QVariant(),
            QVariant val7 = QVariant(),
            QVariant val8 = QVariant(),
            QVariant val9 = QVariant());

    const QString peerName() const;

protected:
    AbstractHub* m_hub;
    void addCall(qlonglong id, AbstractCall *call);
    void removeCall(qlonglong id);
    void setPeerName(const QString &name);

signals:
    void hubChanged(AbstractHub* hub);
    void propertyChanged(const QString &name, const QVariant &value);

private slots:
    void hub_disconnected();

public slots:
    void setHub(AbstractHub* hub);
    void setProperty(QString name, QVariant value);
};

NEURON_END_NAMESPACE

#endif // NEURONPEER_H
