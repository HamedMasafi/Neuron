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

#ifndef NORON_SHARED_OBJECT
#include "syntax/syntax_peer.h"
#endif

#ifndef NORONPEER_H
#define NORONPEER_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "noronabstracthub.h"
#include "noronglobal.h"
#include "noronremotecall_p.h"

NORON_BEGIN_NAMESPACE

class NoronAbstractHub;
class NoronRemoteCallBase;
class NORON_EXPORT NoronPeer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NoronAbstractHub* hub READ hub WRITE setHub NOTIFY hubChanged)

    QString _peerName;

public:
    explicit NoronPeer(QObject *parent = 0);
    NoronPeer(NoronAbstractHub *hub, QObject *parent = 0);
    virtual ~NoronPeer();

    NoronAbstractHub* hub() const;

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
    NoronAbstractHub* m_hub;
    void addCall(qlonglong id, NoronRemoteCallBase *call);
    void removeCall(qlonglong id);
    void setPeerName(const QString &name);

signals:
    void hubChanged(NoronAbstractHub* hub);

public slots:
    void setHub(NoronAbstractHub* hub);
};

NORON_END_NAMESPACE

#endif // NORONPEER_H
