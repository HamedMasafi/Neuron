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

#ifndef NEURONABSTRACTHUB_H
#define NEURONABSTRACTHUB_H

#define THIS_HUB "::ThisHub"

#include "global.h"

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

class Peer;
class AbstractHubPrivate;
class AbstractSerializer;
class SharedObject;
class AbstractCall;
class AbstractDataEncoder;
class NEURON_EXPORT AbstractHub : public QObject
{
    Q_OBJECT

    AbstractHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(AbstractHub)

    Q_PROPERTY(Peer* peer READ peer WRITE setPeer NOTIFY peerChanged)
    Q_PROPERTY(AbstractSerializer* serializer READ serializer WRITE setSerializer NOTIFY serializerChanged)
    Q_PROPERTY(AbstractHub::Status status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(qlonglong hubId READ hubId WRITE setHubId NOTIFY hubIdChanged)
    Q_PROPERTY(AbstractDataEncoder* encoder READ encoder WRITE setEncoder NOTIFY encoderChanged)

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

    explicit AbstractHub(QObject *parent = nullptr);
    explicit AbstractHub(AbstractSerializer *serializer, QObject *parent = nullptr);
    virtual ~AbstractHub();

    QHash<const QString, SharedObject*> sharedObjectHash() const;
    QList<SharedObject *> sharedObjects() const;
    QList<SharedObject *> sharedObjects(QString peerName) const;
    AbstractSerializer* serializer() const;

    Peer* peer() const;
    bool isConnected() const;
    AbstractDataEncoder *encoder() const;

    bool isMultiThread() const;
    AbstractHub::Status status() const;
#ifdef QT_QML_LIB
    QJSEngine *jsEngine() const;
    QQmlEngine* qmlEngine() const;
#endif

    void waitForConnected(int timeout = 4000);
    Q_INVOKABLE void flushSocket();
    qlonglong hubId() const;

protected:
    QHash<qlonglong, AbstractCall*> _calls;
    QTcpSocket *socket;
    Q_INVOKABLE void setHubId(qlonglong id);

    QMutex initalizeMutex;
    QMutex bufferMutex;

signals:
    void connected();
    void disconnected();
    void reconnected();
    void error();

    void peerChanged(Peer* peer);
    void serializerChanged(AbstractSerializer* serializer);
    void statusChanged(AbstractHub::Status status);
#ifdef QT_QML_LIB
    void jsEngineChanged(QJSEngine *jsEngine);
    void qmlEngineChanged(QQmlEngine* qmlEngine);
#endif
    void hubIdChanged(qlonglong hubId);

    void encoderChanged(AbstractDataEncoder *encoder);

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

    void attachSharedObject(SharedObject *o);
    void detachSharedObject(SharedObject *o);
    void setPeer(Peer* peer);
    void setSerializer(AbstractSerializer* serializer);
    void setEncoder(AbstractDataEncoder *encoder);

#ifdef QT_QML_LIB
    void setJsEngine(QJSEngine *jsEngine);
    void setQmlEngine(QQmlEngine* qmlEngine);
#endif


protected:
    virtual void beginConnection();
    void setIsMultiThread(bool isMultiThread);
    void setStatus(AbstractHub::Status status);

    friend class Peer;
    friend class Server;
};

NEURON_END_NAMESPACE

//Q_DECLARE_METATYPE(NEURON_WRAP_NAMESPACE(AbstractHub::Status))

#endif // NEURONABSTRACTHUB_H
