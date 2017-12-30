/**************************************************************************
**
** This file is part of Neuron.
** https://github.com/HamedMasafi/Neuron
**
** Neuron is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Neuron is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Neuron.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#ifndef NEURONCLIENTHUB_H
#define NEURONCLIENTHUB_H

#include <QtCore/qglobal.h>

#include "neuronabstracthub.h"

#ifdef QT_QML_LIB
class QJSEngine;
class QQmlEngine;
#endif

NEURON_BEGIN_NAMESPACE

class NeuronClientHubPrivate;
class NEURON_EXPORT NeuronClientHub : public NeuronAbstractHub
{
    Q_OBJECT

    NeuronClientHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(NeuronClientHub)

    Q_PROPERTY(QString serverAddress READ serverAddress WRITE setServerAddress NOTIFY serverAddressChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool isAutoReconnect READ isAutoReconnect WRITE setAutoReconnect NOTIFY isAutoReconnectChanged)

public:
    NeuronClientHub(QObject *parent = 0);
#ifdef QT_QML_LIB
    NeuronClientHub(QQmlEngine *qmlEngine, QJSEngine *jsEngine, QObject *parent = 0);
#endif

    virtual ~NeuronClientHub();

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
    void connectToHost(QString address = QString::null, quint16 port = 0, bool waitForConnected = false);
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

    // NeuronAbstractHub interface
protected:
    void beginConnection();
};

NEURON_END_NAMESPACE

#endif // NEURONCLIENTHUB_H
