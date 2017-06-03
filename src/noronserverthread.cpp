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

#include "noronserverthread.h"
#include "noronserverhub.h"

#include <QTcpSocket>

NORON_BEGIN_NAMESPACE

NoronServerThread::NoronServerThread(qintptr socketDescriptor, QObject *parent) : QThread(parent),
    _hub(0), _isStarted(false)
{
    this->socketDescriptor = socketDescriptor;
}

NoronServerThread::~NoronServerThread()
{
//    if(_hub)
//        _hub->deleteLater();
}

bool NoronServerThread::isStarted() const
{
    return _isStarted;
}

void NoronServerThread::run()
{
    K_TRACE_DEBUG;
    //TODO: pass serializer to here!
    _hub = new NoronServerHub;
    _hub->setSocketDescriptor(this->socketDescriptor, false);
    _hub->setServerThread(this);

    K_REG_OBJECT(_hub);

    _isStarted = true;

    exec();

    K_TRACE_DEBUG;
}

NoronServerHub *NoronServerThread::hub()
{
    return _hub;
}

NORON_END_NAMESPACE
