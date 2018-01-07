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

#ifndef NEURONABSTRACTHUB_H
#define NEURONABSTRACTHUB_H

#define THIS_HUB "::ThisHub"

#include "neuronglobal.h"

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QAbstractSocket>

#include <QMutex>

class QTcpSocket;
#ifdef QT_QML_LIB
class QJSEngine;
class QQmlEngine;
#endif

NEURON_BEGIN_NAMESPACE

class NeuronPeer;
class NeuronAbstractHubPrivate;
class NeuronAbstractSerializer;
class NeuronSharedObject;
class NeuronRemoteCallBase;
class NeuronAbstractDataEncoder;
class NEURON_EXPORT NeuronAbstractHub : public QObject
{
    Q_OBJECT

    NeuronAbstractHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(NeuronAbstractHub)

    Q_PROPERTY(NeuronPeer* peer READ peer WRITE setPeer NOTIFY peerChanged)
    Q_PROPERTY(NeuronAbstractSerializer* serializer READ serializer WRITE setSerializer NOTIFY serializerChanged)
    Q_PROPERTY(NeuronAbstractHub::Status status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(qlonglong hubId READ hubId WRITE setHubId NOTIFY hubIdChanged)
    Q_PROPERTY(NeuronAbstractDataEncoder* encoder READ encoder WRITE setEncoder NOTIFY encoderChanged)

#ifdef QT_QML_LIB
    Q_PROPERTY(QJSEngine* jsEngine READ jsEngine WRITE setJsEngine NOTIFY jsEngineChanged)
    Q_PROPERTY(QQmlEngine* qmlEngine READ qmlEngine WRITE setQmlEngine NOTIFY qmlEngineChanged)
#endif

public:
    enum Status{
        Unconnected,
        Connected,
        Reconnecting
    };
    Q_ENUM(Status)

    explicit NeuronAbstractHub(QObject *parent = 0);
    explicit NeuronAbstractHub(NeuronAbstractSerializer *serializer, QObject *parent = 0);
    virtual ~NeuronAbstractHub();

    QHash<const QString, NeuronSharedObject*> sharedObjectHash() const;
    QList<NeuronSharedObject *> sharedObjects() const;
    QList<NeuronSharedObject *> sharedObjects(QString peerName) const;
    NeuronAbstractSerializer* serializer() const;

    NeuronPeer* peer() const;
    bool isConnected() const;
    NeuronAbstractDataEncoder *encoder() const;

    bool isMultiThread() const;
    NeuronAbstractHub::Status status() const;
#ifdef QT_QML_LIB
    QJSEngine *jsEngine() const;
    QQmlEngine* qmlEngine() const;
#endif

    void waitForConnected(int timeout = 4000);
    Q_INVOKABLE void flushSocket();
    qlonglong hubId() const;

protected:
    QHash<qlonglong, NeuronRemoteCallBase*> _calls;
    QTcpSocket *socket;
    Q_INVOKABLE void setHubId(qlonglong id);

    QMutex initalizeMutex;
    QMutex bufferMutex;

signals:
    void connected();
    void disconnected();
    void reconnected();
    void error();

    void peerChanged(NeuronPeer* peer);
    void serializerChanged(NeuronAbstractSerializer* serializer);
    void statusChanged(NeuronAbstractHub::Status status);
#ifdef QT_QML_LIB
    void jsEngineChanged(QJSEngine *jsEngine);
    void qmlEngineChanged(QQmlEngine* qmlEngine);
#endif
    void hubIdChanged(qlonglong hubId);

    void encoderChanged(NeuronAbstractDataEncoder *encoder);

private slots:
    void socket_connected();
    void socket_disconnected();
    void socket_onReadyRead();
    void socket_error(QAbstractSocket::SocketError socketError);

public slots:
    void beginTransaction();
    bool isTransaction() const;
    void rollback();
    void commit();
    qlonglong invokeOnPeer(
            QString sender,
            QString methodName,
            QVariant val0 = QVariant(),
            QVariant val1 = QVariant(),
            QVariant val2 = QVariant(),
            QVariant val3 = QVariant(),
            QVariant val4 = QVariant(),
            QVariant val5 = QVariant(),
            QVariant val6 = QVariant(),
            QVariant val7 = QVariant(),
            QVariant val8 = QVariant(),
            QVariant val9 = QVariant());

    void attachSharedObject(NeuronSharedObject *o);
    void detachSharedObject(NeuronSharedObject *o);
    void setPeer(NeuronPeer* peer);
    void setSerializer(NeuronAbstractSerializer* serializer);
    void setEncoder(NeuronAbstractDataEncoder *encoder);

#ifdef QT_QML_LIB
    void setJsEngine(QJSEngine *jsEngine);
    void setQmlEngine(QQmlEngine* qmlEngine);
#endif


protected:
    virtual void beginConnection();
    void setIsMultiThread(bool isMultiThread);
    void setStatus(NeuronAbstractHub::Status status);

    friend class NeuronPeer;
    friend class NeuronServer;
};

NEURON_END_NAMESPACE

Q_DECLARE_METATYPE(NEURON_WRAP_NAMESPACE(NeuronAbstractHub::Status))

#endif // NEURONABSTRACTHUB_H
