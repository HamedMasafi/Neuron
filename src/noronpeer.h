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

#ifndef NORONPEER_H
#define NORONPEER_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "noronglobal.h"
#include "noronremotecall_p.h"
#include "syntax_p.h"

QT_BEGIN_NAMESPACE

#define NORON_PEER_CTOR_DECL(c) c(NoronAbstractHub *hub, QObject *parent = 0); \
                          Q_INVOKABLE c(QObject *parent = 0);

#define NORON_PEER_CTOR_IMPL(c) c::c(NoronAbstractHub *hub, QObject *parent) : Peer(hub, parent)  \
{}  \
c::c(QObject *parent) : Peer(parent)  \
{}

class NoronAbstractHub;
class NoronRemoteCallBase;
class NORON_EXPORT NoronPeer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NoronAbstractHub* hub READ hub WRITE setHub NOTIFY hubChanged)


public:
    explicit NoronPeer(QObject *parent = 0);
    NoronPeer(NoronAbstractHub *hub, QObject *parent = 0);
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

    virtual const QString peerName();// = 0;

protected:
    NoronAbstractHub* m_hub;
    void addCall(long id, NoronRemoteCallBase *call);
    void removeCall(long id);

signals:
    void hubChanged(NoronAbstractHub* hub);

public slots:
    virtual void setHub(NoronAbstractHub* hub);
};

QT_END_NAMESPACE

#endif // NORONPEER_H
