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

#ifndef NORONCLIENTHUB_H
#define NORONCLIENTHUB_H

#include <QtCore/qglobal.h>

#include "noronabstracthub.h"

QT_BEGIN_NAMESPACE

class NoronClientHubPrivate;
class NORON_EXPORT NoronClientHub : public NoronAbstractHub
{
    Q_OBJECT

    NoronClientHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(NoronClientHub)

    Q_PROPERTY(QString serverAddress READ serverAddress WRITE setServerAddress NOTIFY serverAddressChanged)
    Q_PROPERTY(qint16 port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool isAutoReconnect READ isAutoReconnect WRITE setAutoReconnect NOTIFY isAutoReconnectChanged)

public:
    NoronClientHub(QObject *parent = 0);
    QString serverAddress() const;
    qint16 port() const;
    bool isAutoReconnect() const;

protected:
    void timerEvent(QTimerEvent *);

public slots:
    void connectToHost(bool waitForConnected);
    void connectToHost(QString address = QString::null, qint16 port = 0, bool waitForConnected = false);
    void disconnectFromHost();
    void setServerAddress(QString serverAddress);
    void setPort(qint16 port);
    void setAutoReconnect(bool isAutoReconnect);

private slots:
    void isConnectedChanged(bool isConnected);

signals:
    void serverAddressChanged(QString serverAddress);
    void portChanged(qint16 port);
    void isAutoReconnectChanged(bool isAutoReconnect);
};

QT_END_NAMESPACE

#endif // NORONCLIENTHUB_H
