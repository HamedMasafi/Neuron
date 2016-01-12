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

#ifndef NORONCLIENTHUB_P_H
#define NORONCLIENTHUB_P_H

#include "noronclienthub.h"

QT_BEGIN_NAMESPACE

class NoronClientHubPrivate{
    NoronClientHub *q_ptr;
    Q_DECLARE_PUBLIC(NoronClientHub)

public:
    NoronClientHubPrivate(NoronClientHub *parent);

    qint16 port;               // port
    QString serverAddress;     // address of server
    bool isAutoReconnect;
    int reconnectTimerId;

    void sync();
};

QT_END_NAMESPACE

#endif // NORONCLIENTHUB_P_H
