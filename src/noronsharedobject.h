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

#ifndef NORONSHAREDOBJECT_H
#define NORONSHAREDOBJECT_H

#include <QtCore/QSet>

#include "noronpeer.h"

QT_BEGIN_NAMESPACE

class NORON_EXPORT NoronSharedObject : public NoronPeer
{
    Q_OBJECT
    NoronAbstractHub *_activeHub;

public:
    NoronSharedObject(QObject *parent = 0);
    NoronSharedObject(NoronAbstractHub *hub, QObject *parent = 0);

    void addHub(NoronAbstractHub *hub);
    void removeHub(NoronAbstractHub *hub);
    bool setActiveHub(NoronAbstractHub *hub);

    QSet<NoronAbstractHub*> hubs;

    void setHub(NoronAbstractHub* hub) /*Q_DECL_OVERRIDE*/;

    virtual const QString peerName() /*Q_DECL_OVERRIDE*/;
    virtual void hubAdded(NoronAbstractHub *hub);
    virtual void hubRemoved(NoronAbstractHub *hub);

protected:
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

signals:
};

QT_END_NAMESPACE

#endif // NORONSHAREDOBJECT_H
