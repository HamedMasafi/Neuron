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

#ifndef NORONSERVERHUB_H
#define NORONSERVERHUB_H

#include <QtCore/qglobal.h>

#include "noronabstracthub.h"

QT_BEGIN_NAMESPACE

class NoronServerThread;
class NoronServerHubPrivate;
class NORON_EXPORT NoronServerHub : public NoronAbstractHub
{
    Q_OBJECT

    NoronServerHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(NoronServerHub)

public:
    NoronServerHub(QObject *parent = 0);
    NoronServerHub(NoronAbstractSerializer *serializer, QObject *parent = 0);
    NoronServerHub(QTcpSocket *socket, QObject *parent = 0);

    ~NoronServerHub();

    NoronServerThread *serverThread() const;

public slots:
    bool setSocketDescriptor(qintptr socketDescriptor, bool waitForConnect = false);
    void setServerThread(NoronServerThread *serverThread);
};

QT_END_NAMESPACE

#endif // NORONSERVERHUB_H
