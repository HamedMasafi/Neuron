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

#include <QtNetwork/QTcpSocket>

#include "abstracthub_p.h"
#include "clienthub_p.h"
#include "clienthub.h"
#include "abstractserializer.h"
#include "peer.h"
#include "sharedobject.h"

#ifdef QT_QML_LIB
#   include <QtQml>
#endif

NEURON_BEGIN_NAMESPACE

ClientHubPrivate::ClientHubPrivate(ClientHub *parent) : q_ptr(parent),
    port(0), serverAddress(QString::null), isAutoReconnect(false), connectionEventLoop(0)
{

}

ClientHub::ClientHub(QObject *parent) : AbstractHub(parent),
    d_ptr(new ClientHubPrivate(this))
{
    qRegisterMetaType<Status>("AbstractHub::Status");
    connect(this, &AbstractHub::statusChanged, this, &ClientHub::onStatusChanged);
}

#ifdef QT_QML_LIB
ClientHub::ClientHub(QQmlEngine *qmlEngine, QJSEngine *engine, QObject *parent) : AbstractHub(parent),
    d_ptr(new ClientHubPrivate(this))
{
    setJsEngine(engine);
    setQmlEngine(qmlEngine);
    qRegisterMetaType<Status>("AbstractHub::Status");
    connect(this, &AbstractHub::statusChanged, this, &ClientHub::onStatusChanged);
}
#endif

ClientHub::~ClientHub()
{
    Q_D(ClientHub);
    delete d;
}

QString ClientHub::serverAddress() const
{
    Q_D(const ClientHub);
    return d->serverAddress;
}

quint16 ClientHub::port() const
{
    Q_D(const ClientHub);
    return d->port;
}

bool ClientHub::isAutoReconnect() const
{
    Q_D(const ClientHub);
    return d->isAutoReconnect;
}

#ifdef QT_QML_LIB
static QObject* create_singelton_object_client_hub(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new ClientHub(qmlEngine, jsEngine);
}

int ClientHub::registerQml(const char *uri, int versionMajor, int versionMinor)
{
    qmlRegisterUncreatableType<AbstractHub>    (uri, versionMajor, versionMinor, "AbstractHub", "Abstract class for ClientHub base");
    qmlRegisterUncreatableType<Peer>           (uri, versionMajor, versionMinor, "Peer", "Abstract type used by custom generated peer");
    qmlRegisterUncreatableType<SharedObject>   (uri, versionMajor, versionMinor, "SharedObject", "Abstract type used by ClientHub");
    return qmlRegisterType<ClientHub>          (uri, versionMajor, versionMinor, "ClientHub");
}

int ClientHub::registerQmlSingleton(const char *uri, int versionMajor, int versionMinor)
{
    qmlRegisterUncreatableType<AbstractHub>    (uri, versionMajor, versionMinor, "AbstractHub", "Abstract class for ClientHub base");
    qmlRegisterUncreatableType<Peer>           (uri, versionMajor, versionMinor, "Peer", "Abstract type used by custom generated peer");
    qmlRegisterUncreatableType<SharedObject>   (uri, versionMajor, versionMinor, "SharedObject", "Abstract type used by ClientHub");
    return qmlRegisterSingletonType<ClientHub> (uri, versionMajor, versionMinor, "ClientHub", create_singelton_object_client_hub);
}
#endif

void ClientHub::timerEvent(QTimerEvent *)
{
    Q_D(ClientHub);

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

void ClientHub::connectToHost(bool waitForConnected)
{
    connectToHost(QString::null, 0, waitForConnected);
}

void ClientHub::connectToHost(QString address, quint16 port, bool waitForConnected)
{
    if(!address.isNull())
        setServerAddress(address);

    if(port)
        setPort(port);

    socket->connectToHost(this->serverAddress(), this->port());

    if(waitForConnected) {
        this->waitForConnected();

        if (socket->state() != QAbstractSocket::ConnectedState) {
            qWarning("Unable to start client socket. Error: %s", socket->errorString().toUtf8().data());
            setStatus(Unconnected);
        }
    }
}

void ClientHub::disconnectFromHost()
{
    Q_D(ClientHub);
    d->isAutoReconnect = false;
    socket->disconnectFromHost();
}

void ClientHub::setServerAddress(QString serverAddress)
{
    Q_D(ClientHub);

    if (d->serverAddress == serverAddress)
        return;

    d->serverAddress = serverAddress;
    emit serverAddressChanged(serverAddress);
}

void ClientHub::setPort(quint16 port)
{
    Q_D(ClientHub);

    if (d->port == port)
        return;

    d->port = port;
    emit portChanged(port);
}

void ClientHub::setAutoReconnect(bool isAutoReconnect)
{
    Q_D(ClientHub);

    if (d->isAutoReconnect == isAutoReconnect)
        return;

    d->isAutoReconnect = isAutoReconnect;
    emit isAutoReconnectChanged(isAutoReconnect);
}

void ClientHub::onStatusChanged(Status status)
{
    Q_D(ClientHub);

    if(status == Unconnected){
        if(isAutoReconnect()){
            connectToHost();
            d->reconnectTimerId = startTimer(500);
            setStatus(Reconnecting);
        }
    }
}

void ClientHub::hi(qlonglong hubId)
{
    Q_D(ClientHub);

    setStatus(Connected);
    if(hubId == this->hubId()){
        //reconnected
        emit reconnected();
    }else{
    }

    if(d->connectionEventLoop){
        d->connectionEventLoop->exit();
        d->connectionEventLoop->deleteLater();
    }
}

void ClientHub::beginConnection()
{
    Q_D(ClientHub);
    qlonglong __call_id = invokeOnPeer(THIS_HUB, "hi", QVariant::fromValue(hubId()));

    if(__call_id){
        Call<qlonglong> *call = new Call<qlonglong>(this);
        call->then([=](qlonglong hubId){
            setStatus(Connected);
            if (hubId == this->hubId()){
                //reconnected
                emit reconnected();
            }else{
            }

            if(d->connectionEventLoop){
                d->connectionEventLoop->exit();
                d->connectionEventLoop->deleteLater();
            }
        });
//        addCall(__call_id, call);
        _calls.insert(__call_id, call);
    }
}

NEURON_END_NAMESPACE
