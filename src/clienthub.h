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

#ifndef NEURONCLIENTHUB_H
#define NEURONCLIENTHUB_H

#include <QtCore/qglobal.h>

#include "abstracthub.h"

#ifdef QT_QML_LIB
class QJSEngine;
class QQmlEngine;
#endif

NEURON_BEGIN_NAMESPACE

class ClientHubPrivate;
class NEURON_EXPORT ClientHub : public AbstractHub
{
    Q_OBJECT

    ClientHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(ClientHub)

    Q_PROPERTY(QString serverAddress READ serverAddress WRITE setServerAddress NOTIFY serverAddressChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool isAutoReconnect READ isAutoReconnect WRITE setAutoReconnect NOTIFY isAutoReconnectChanged)

public:
    ClientHub(QObject *parent = nullptr);
#ifdef QT_QML_LIB
    ClientHub(QQmlEngine *qmlEngine, QJSEngine *jsEngine, QObject *parent = 0);
#endif

    virtual ~ClientHub();

    QString serverAddress() const;
    quint16 port() const;
    bool isAutoReconnect() const;

#ifdef QT_QML_LIB
    static int registerQml(const char *uri, int versionMajor, int versionMinor);
    static int registerQmlSingleton(const char *uri, int versionMajor, int versionMinor);
#endif

protected:
    void timerEvent(QTimerEvent *);

public slots:
    void connectToHost(bool waitForConnected);
    void connectToHost(QString address = QString(), quint16 port = 0, bool waitForConnected = false);
    void disconnectFromHost();
    void setServerAddress(QString serverAddress);
    void setPort(quint16 port);
    void setAutoReconnect(bool isAutoReconnect);

private slots:
    void onStatusChanged(Status status);
    void hi(qlonglong hubId);

signals:
    void serverAddressChanged(QString serverAddress);
    void portChanged(int port);
    void isAutoReconnectChanged(bool isAutoReconnect);

    // AbstractHub interface
protected:
    void beginConnection();
};

NEURON_END_NAMESPACE

#endif // NEURONCLIENTHUB_H
