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

#include <QtNetwork/QTcpSocket>

#include "noronabstracthub_p.h"
#include "noronclienthub_p.h"
#include "noronclienthub.h"
#include "noronabstractserializer.h"
#include "noronpeer.h"
#include "noronsharedobject.h"

#ifdef QT_QML_LIB
#   include <QtQml>
#endif

NORON_BEGIN_NAMESPACE

NoronClientHubPrivate::NoronClientHubPrivate(NoronClientHub *parent) : q_ptr(parent),
    port(0), serverAddress(QString::null), isAutoReconnect(false), connectionEventLoop(0)
{

}

NoronClientHub::NoronClientHub(QObject *parent) : NoronAbstractHub(parent),
    d_ptr(new NoronClientHubPrivate(this))
{
    qRegisterMetaType<Status>();
    connect(this, &NoronAbstractHub::statusChanged, this, &NoronClientHub::onStatusChanged);
}

#ifdef QT_QML_LIB
NoronClientHub::NoronClientHub(QQmlEngine *qmlEngine, QJSEngine *engine, QObject *parent) : NoronAbstractHub(parent),
    d_ptr(new NoronClientHubPrivate(this))
{
    setJsEngine(engine);
    setQmlEngine(qmlEngine);
    qRegisterMetaType<Status>();
    connect(this, &NoronAbstractHub::statusChanged, this, &NoronClientHub::onStatusChanged);
}
#endif

NoronClientHub::~NoronClientHub()
{
    Q_D(NoronClientHub);
    delete d;
}

QString NoronClientHub::serverAddress() const
{
    Q_D(const NoronClientHub);
    return d->serverAddress;
}

quint16 NoronClientHub::port() const
{
    Q_D(const NoronClientHub);
    return d->port;
}

bool NoronClientHub::isAutoReconnect() const
{
    Q_D(const NoronClientHub);
    return d->isAutoReconnect;
}

#ifdef QT_QML_LIB
static QObject* create_singelton_object_client_hub(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new NoronClientHub(qmlEngine, jsEngine);
}

int NoronClientHub::registerQml(const char *uri, int versionMajor, int versionMinor)
{
    qmlRegisterUncreatableType<NoronAbstractHub>    (uri, versionMajor, versionMinor, "AbstractHub", "Abstract class for ClientHub base");
    qmlRegisterUncreatableType<NoronPeer>           (uri, versionMajor, versionMinor, "Peer", "Abstract type used by custom generated peer");
    qmlRegisterUncreatableType<NoronSharedObject>   (uri, versionMajor, versionMinor, "SharedObject", "Abstract type used by ClientHub");
    return qmlRegisterType<NoronClientHub>          (uri, versionMajor, versionMinor, "ClientHub");
}

int NoronClientHub::registerQmlSingleton(const char *uri, int versionMajor, int versionMinor)
{
    qmlRegisterUncreatableType<NoronAbstractHub>    (uri, versionMajor, versionMinor, "AbstractHub", "Abstract class for ClientHub base");
    qmlRegisterUncreatableType<NoronPeer>           (uri, versionMajor, versionMinor, "Peer", "Abstract type used by custom generated peer");
    qmlRegisterUncreatableType<NoronSharedObject>   (uri, versionMajor, versionMinor, "SharedObject", "Abstract type used by ClientHub");
    return qmlRegisterSingletonType<NoronClientHub> (uri, versionMajor, versionMinor, "ClientHub", create_singelton_object_client_hub);
}
#endif

void NoronClientHub::timerEvent(QTimerEvent *)
{
    Q_D(NoronClientHub);

    if(socket->state() == QAbstractSocket::UnconnectedState){
        connectToHost();
        setStatus(Reconnecting);
//        qDebug() << "reconnecting...";
    }else if(socket->state() == QAbstractSocket::ConnectedState){
        killTimer(d->reconnectTimerId);
//        d->sync();
        setStatus(Connected);
    }
}

void NoronClientHub::connectToHost(bool waitForConnected)
{
    connectToHost(QString::null, 0, waitForConnected);
}

void NoronClientHub::connectToHost(QString address, quint16 port, bool waitForConnected)
{
    if(!address.isNull())
        setServerAddress(address);

    if(port)
        setPort(port);

    socket->connectToHost(this->serverAddress(), this->port());

    if(waitForConnected)
        this->waitForConnected();

    if (socket->state() != QAbstractSocket::ConnectedState) {
        qWarning("Unable to start client socket. Error: %s", socket->errorString().toUtf8().data());
        emit disconnected();
    }
}

void NoronClientHub::disconnectFromHost()
{
    Q_D(NoronClientHub);
    d->isAutoReconnect = false;
    socket->disconnectFromHost();
}

void NoronClientHub::setServerAddress(QString serverAddress)
{
    Q_D(NoronClientHub);

    if (d->serverAddress == serverAddress)
        return;

    d->serverAddress = serverAddress;
    emit serverAddressChanged(serverAddress);
}

void NoronClientHub::setPort(quint16 port)
{
    Q_D(NoronClientHub);

    if (d->port == port)
        return;

    d->port = port;
    emit portChanged(port);
}

void NoronClientHub::setAutoReconnect(bool isAutoReconnect)
{
    Q_D(NoronClientHub);

    if (d->isAutoReconnect == isAutoReconnect)
        return;

    d->isAutoReconnect = isAutoReconnect;
    emit isAutoReconnectChanged(isAutoReconnect);
}

void NoronClientHub::onStatusChanged(Status status)
{
    Q_D(NoronClientHub);

    if(status == Unconnected){
        if(isAutoReconnect()){
            connectToHost();
            d->reconnectTimerId = startTimer(500);
            setStatus(Reconnecting);
        }else{
            setStatus(Unconnected);
        }
    }
}

void NoronClientHub::hi(qlonglong hubId)
{
    Q_D(NoronClientHub);

    setStatus(Connected);
    if(hubId == this->hubId()){
        //reconnected
        emit reconnected();
        emit connected();
    }else{
        emit connected();
    }

    if(d->connectionEventLoop){
        d->connectionEventLoop->exit();
        d->connectionEventLoop->deleteLater();
    }
}

void NoronClientHub::beginConnection()
{
    qlonglong __call_id = invokeOnPeer(THIS_HUB, "hi", QVariant::fromValue(hubId()));

    if(__call_id){
        NoronRemoteCall<qlonglong> *call = new NoronRemoteCall<qlonglong>(this, "hi");
       // addCall(__call_id, call);
        _calls.insert(__call_id, call);
    }
}

NORON_END_NAMESPACE
