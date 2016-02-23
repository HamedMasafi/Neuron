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

#include "noronabstracthub.h"
#include "noronsharedobject.h"

#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

NoronSharedObject::NoronSharedObject(QObject *parent) : NoronPeer(parent)
{

}

NoronSharedObject::NoronSharedObject(NoronAbstractHub *hub, QObject *parent) : NoronPeer(parent)
{
    addHub(hub);
}

void NoronSharedObject::addHub(NoronAbstractHub *hub)
{    
    if(!hub->inherits(QT_STRINGIFY(NoronServer)))
        hubs.insert(hub);
}

void NoronSharedObject::removeHub(NoronAbstractHub *hub)
{
    hubs.remove(hub);
}

qlonglong NoronSharedObject::invokeOnPeer(QString methodName, QVariant val0, QVariant val1, QVariant val2, QVariant val3, QVariant val4, QVariant val5, QVariant val6, QVariant val7, QVariant val8, QVariant val9)
{
    foreach (NoronAbstractHub *hub, hubs) {

        if(hub->isMultiThread())
            hub->metaObject()->invokeMethod(hub,
                                            QT_STRINGIFY(invokeOnPeer),
                                            Q_ARG(QString, metaObject()->className()),
                                            Q_ARG(QString, methodName),
                                            Q_ARG(QVariant, val0),
                                            Q_ARG(QVariant, val1),
                                            Q_ARG(QVariant, val2),
                                            Q_ARG(QVariant, val3),
                                            Q_ARG(QVariant, val4),
                                            Q_ARG(QVariant, val5),
                                            Q_ARG(QVariant, val6),
                                            Q_ARG(QVariant, val7));
        else
            hub->invokeOnPeer(
                        metaObject()->className(),
                        methodName,
                        val0, val1, val2, val3, val4,
                        val5, val6, val7, val8, val9);
    }

    return 1;
}

QT_END_NAMESPACE
