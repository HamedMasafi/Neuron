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

#include <QEvent>
#include <QTimer>
#include <QUdpSocket>

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

ClientHubPrivate::ClientHubPrivate() :
    port(0), isAutoReconnect(false), connectionEventLoop(nullptr)
{

}

ClientHub::ClientHub(QObject *parent) : AbstractHub(parent),
    d(new ClientHubPrivate)
{
    qRegisterMetaType<Status>("AbstractHub::Status");
    connect(this, &AbstractHub::statusChanged, this, &ClientHub::onStatusChanged);
}

#ifdef QT_QML_LIB
ClientHub::ClientHub(QQmlEngine *qmlEngine, QJSEngine *engine, QObject *parent) : AbstractHub(parent),
    d(new ClientHubPrivate)
{
    setJsEngine(engine);
    setQmlEngine(qmlEngine);
    qRegisterMetaType<Status>("AbstractHub::Status");
    connect(this, &AbstractHub::statusChanged, this, &ClientHub::onStatusChanged);
}
#endif

ClientHub::~ClientHub()
{
}

QString ClientHub::serverAddress() const
{
    return d->serverAddress;
}

quint16 ClientHub::port() const
{
    return d->port;
}

bool ClientHub::isAutoReconnect() const
{
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

void ClientHub::timerEvent(QTimerEvent *e)
{
    if(status() == Unconnected){
        connectToHost();
        setStatus(Reconnecting);
    }else if(status() == Connected){
        killTimer(e->timerId());// d->reconnectTimerId);
//        d->sync();
//        setStatus(Connected);
    }
}

void ClientHub::connectToHost(bool waitForConnected)
{
    connectToHost(QString(), 0, waitForConnected);
}

void ClientHub::connectToHost(QString address, quint16 port, bool waitForConnected)
{
    if (status() != Unconnected)
        return;

    if(!address.isNull())
        setServerAddress(address);

    if(port)
        setPort(port);

    socket->connectToHost(this->serverAddress(), this->port());

    if(waitForConnected) {
        this->waitForConnected();

        if (!isConnected()) {
            qWarning("Unable to start client socket. Error: %s", socket->errorString().toUtf8().data());

            setStatus(Unconnected);
            onStatusChanged(Unconnected);
        }
    }
}

void ClientHub::disconnectFromHost()
{
    d->isAutoReconnect = false;
    socket->disconnectFromHost();
}

void ClientHub::setServerAddress(QString serverAddress)
{
    if (d->serverAddress == serverAddress)
        return;

    d->serverAddress = serverAddress;
    emit serverAddressChanged(serverAddress);
}

void ClientHub::setPort(quint16 port)
{
    if (d->port == port)
        return;

    d->port = port;
    emit portChanged(port);
}

void ClientHub::setAutoReconnect(bool isAutoReconnect)
{
    if (d->isAutoReconnect == isAutoReconnect)
        return;

    d->isAutoReconnect = isAutoReconnect;
    emit isAutoReconnectChanged(isAutoReconnect);
}

bool ClientHub::findDataFromBroadcast(const quint16 &broadcastPort, quint16 &port, QString &serverAddress, const int &timeout)
{
    bool ret = false;
    QEventLoop loop;
    auto udpSocket = new QUdpSocket(this);
    connect(udpSocket, &QUdpSocket::readyRead, [this, &loop, &ret, &port, &serverAddress, udpSocket](){
        while (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(int(udpSocket->pendingDatagramSize()));
            udpSocket->readDatagram(datagram.data(), datagram.size());

            QVariant var = serializer()->deserialize(datagram);
            qDebug() << var;
            if (var.type() != QVariant::Map)
                return;

            auto map = var.toMap();
            port = static_cast<quint16>(map.value("port").toInt());
            serverAddress = map.value("address").toString();
            ret = true;
            loop.quit();
        }
        if (ret) {
            udpSocket->close();
            udpSocket->deleteLater();
        }
    });
    bool ok = udpSocket->bind(broadcastPort, QUdpSocket::ShareAddress);

    if (!ok) {
        qDebug() << "Unable to bind broadcast";
        return false;
    }
    if (timeout > 0)
        QTimer::singleShot(timeout, &loop, &QEventLoop::quit);
    loop.exec();

    return ret;
}

void ClientHub::onStatusChanged(Status status)
{
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
    qDebug() << "hi recived";
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
    qlonglong __call_id = invokeOnPeer(THIS_HUB, "hi", InvokeMethod, QVariant::fromValue(hubId()));

    if(__call_id){
        Call<qlonglong> *call = new Call<qlonglong>(this);
        qDebug() << "Sending hi";
        call->then([=](qlonglong hubId){
            setStatus(Connected);
            qDebug() << "hi recived";
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
    } else {
        qDebug() << "call id for 'hi' is invalid";
    }
}

NEURON_END_NAMESPACE
