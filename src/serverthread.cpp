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

#include "serverthread.h"
#include "serverhub.h"

#include <QTcpSocket>

NEURON_BEGIN_NAMESPACE

ServerThread::ServerThread(qintptr socketDescriptor, QObject *parent) : QThread(parent),
    _hub(0), _isStarted(false)
{
    this->socketDescriptor = socketDescriptor;
}

ServerThread::~ServerThread()
{
//    if(_hub)
//        _hub->deleteLater();
}

bool ServerThread::isStarted() const
{
    return _isStarted;
}

void ServerThread::run()
{
    K_TRACE_DEBUG;
    //TODO: pass serializer to here!
    _hub = new ServerHub;
    _hub->setSocketDescriptor(this->socketDescriptor, false);
    _hub->setServerThread(this);

    K_REG_OBJECT(_hub);

    _isStarted = true;

    exec();

    K_TRACE_DEBUG;
}

ServerHub *ServerThread::hub()
{
    return _hub;
}

NEURON_END_NAMESPACE
