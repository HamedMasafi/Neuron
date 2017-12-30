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

#include <QtNetwork/QTcpSocket>

#include "neuronabstracthub_p.h"
#include "neuronclienthub_p.h"
#include "neuronclienthub.h"
#include "neuronabstractserializer.h"
#include "neuronpeer.h"
#include "neuronsharedobject.h"

#ifdef QT_QML_LIB
#   include <QtQml>
#endif

NEURON_BEGIN_NAMESPACE

NeuronClientHubPrivate::NeuronClientHubPrivate(NeuronClientHub *parent) : q_ptr(parent),
    port(0), serverAddress(QString::null), isAutoReconnect(false), connectionEventLoop(0)
{

}

NeuronClientHub::NeuronClientHub(QObject *parent) : NeuronAbstractHub(parent),
    d_ptr(new NeuronClientHubPrivate(this))
{
    qRegisterMetaType<Status>();
    connect(this, &NeuronAbstractHub::statusChanged, this, &NeuronClientHub::onStatusChanged);
}

#ifdef QT_QML_LIB
NeuronClientHub::NeuronClientHub(QQmlEngine *qmlEngine, QJSEngine *engine, QObject *parent) : NeuronAbstractHub(parent),
    d_ptr(new NeuronClientHubPrivate(this))
{
    setJsEngine(engine);
    setQmlEngine(qmlEngine);
    qRegisterMetaType<Status>();
    connect(this, &NeuronAbstractHub::statusChanged, this, &NeuronClientHub::onStatusChanged);
}
#endif

NeuronClientHub::~NeuronClientHub()
{
    Q_D(NeuronClientHub);
    delete d;
}

QString NeuronClientHub::serverAddress() const
{
    Q_D(const NeuronClientHub);
    return d->serverAddress;
}

quint16 NeuronClientHub::port() const
{
    Q_D(const NeuronClientHub);
    return d->port;
}

bool NeuronClientHub::isAutoReconnect() const
{
    Q_D(const NeuronClientHub);
    return d->isAutoReconnect;
}

#ifdef QT_QML_LIB
static QObject* create_singelton_object_client_hub(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    return new NeuronClientHub(qmlEngine, jsEngine);
}

int NeuronClientHub::registerQml(const char *uri, int versionMajor, int versionMinor)
{
    qmlRegisterUncreatableType<NeuronAbstractHub>    (uri, versionMajor, versionMinor, "AbstractHub", "Abstract class for ClientHub base");
    qmlRegisterUncreatableType<NeuronPeer>           (uri, versionMajor, versionMinor, "Peer", "Abstract type used by custom generated peer");
    qmlRegisterUncreatableType<NeuronSharedObject>   (uri, versionMajor, versionMinor, "SharedObject", "Abstract type used by ClientHub");
    return qmlRegisterType<NeuronClientHub>          (uri, versionMajor, versionMinor, "ClientHub");
}

int NeuronClientHub::registerQmlSingleton(const char *uri, int versionMajor, int versionMinor)
{
    qmlRegisterUncreatableType<NeuronAbstractHub>    (uri, versionMajor, versionMinor, "AbstractHub", "Abstract class for ClientHub base");
    qmlRegisterUncreatableType<NeuronPeer>           (uri, versionMajor, versionMinor, "Peer", "Abstract type used by custom generated peer");
    qmlRegisterUncreatableType<NeuronSharedObject>   (uri, versionMajor, versionMinor, "SharedObject", "Abstract type used by ClientHub");
    return qmlRegisterSingletonType<NeuronClientHub> (uri, versionMajor, versionMinor, "ClientHub", create_singelton_object_client_hub);
}
#endif

void NeuronClientHub::timerEvent(QTimerEvent *)
{
    Q_D(NeuronClientHub);

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

void NeuronClientHub::connectToHost(bool waitForConnected)
{
    connectToHost(QString::null, 0, waitForConnected);
}

void NeuronClientHub::connectToHost(QString address, quint16 port, bool waitForConnected)
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

void NeuronClientHub::disconnectFromHost()
{
    Q_D(NeuronClientHub);
    d->isAutoReconnect = false;
    socket->disconnectFromHost();
}

void NeuronClientHub::setServerAddress(QString serverAddress)
{
    Q_D(NeuronClientHub);

    if (d->serverAddress == serverAddress)
        return;

    d->serverAddress = serverAddress;
    emit serverAddressChanged(serverAddress);
}

void NeuronClientHub::setPort(quint16 port)
{
    Q_D(NeuronClientHub);

    if (d->port == port)
        return;

    d->port = port;
    emit portChanged(port);
}

void NeuronClientHub::setAutoReconnect(bool isAutoReconnect)
{
    Q_D(NeuronClientHub);

    if (d->isAutoReconnect == isAutoReconnect)
        return;

    d->isAutoReconnect = isAutoReconnect;
    emit isAutoReconnectChanged(isAutoReconnect);
}

void NeuronClientHub::onStatusChanged(Status status)
{
    Q_D(NeuronClientHub);

    if(status == Unconnected){
        if(isAutoReconnect()){
            connectToHost();
            d->reconnectTimerId = startTimer(500);
            setStatus(Reconnecting);
        }
    }
}

void NeuronClientHub::hi(qlonglong hubId)
{
    Q_D(NeuronClientHub);

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

void NeuronClientHub::beginConnection()
{
    qlonglong __call_id = invokeOnPeer(THIS_HUB, "hi", QVariant::fromValue(hubId()));

    if(__call_id){
        NeuronRemoteCall<qlonglong> *call = new NeuronRemoteCall<qlonglong>(this, (char*)"hi");
       // addCall(__call_id, call);
        _calls.insert(__call_id, call);
    }
}

NEURON_END_NAMESPACE
