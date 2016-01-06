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

#include <QtCore/QDebug>
#include <QtNetwork/QTcpSocket>

#include "noronabstracthub_p.h"
#include "noronserverhub.h"
#include "noronserverhub_p.h"

QT_BEGIN_NAMESPACE

NoronServerHubPrivate::NoronServerHubPrivate(NoronServerHub *parent) : q_ptr(parent)
{

}

NoronServerHub::NoronServerHub(QObject *parent) : NoronAbstractHub(parent),
    d_ptr(new NoronServerHubPrivate(this))
{

}

NoronServerHub::NoronServerHub(NoronAbstractSerializer *serializer, QObject *parent) : NoronAbstractHub(parent),
    d_ptr(new NoronServerHubPrivate(this))
{
    setSerializer(serializer);
}

NoronServerHub::NoronServerHub(QTcpSocket *socket, QObject *parent) : NoronAbstractHub(parent),
    d_ptr(new NoronServerHubPrivate(this))
{
    this->socket = socket;
}

bool NoronServerHub::setSocketDescriptor(qintptr socketDescriptor, bool waitForConnect)
{
    bool ok = socket->setSocketDescriptor(socketDescriptor);

    if(waitForConnect)
        socket->waitForReadyRead();

    return ok;
}

QT_BEGIN_NAMESPACE
