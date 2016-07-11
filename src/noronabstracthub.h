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

#ifndef NORONABSTRACTHUB_H
#define NORONABSTRACTHUB_H

#include "noronglobal.h"

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QVariant>

QT_BEGIN_NAMESPACE

class NoronPeer;
class NoronAbstractHubPrivate;
class NoronAbstractSerializer;
class NoronSharedObject;
class NoronRemoteCallBase;
class QTcpSocket;
#ifdef QT_QML_LIB
class QJSEngine;
class QQmlEngine;
#endif
class NORON_EXPORT NoronAbstractHub : public QObject
{
    Q_OBJECT

    NoronAbstractHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(NoronAbstractHub)

    Q_PROPERTY(NoronPeer* peer READ peer WRITE setPeer NOTIFY peerChanged)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(QString validateToken READ validateToken WRITE setValidateToken NOTIFY validateTokenChanged)
    Q_PROPERTY(NoronAbstractSerializer* serializer READ serializer WRITE setSerializer NOTIFY serializerChanged)
#ifdef QT_QML_LIB
    Q_PROPERTY(QJSEngine* jsEngine READ jsEngine WRITE setJsEngine NOTIFY jsEngineChanged)
    Q_PROPERTY(QQmlEngine* qmlEngine READ qmlEngine WRITE setQmlEngine NOTIFY qmlEngineChanged)
#endif

public:
    explicit NoronAbstractHub(QObject *parent = 0);
    ~NoronAbstractHub();

    QList<NoronSharedObject *> sharedObjects() const;
    QList<NoronSharedObject *> sharedObjects(QString peerName) const;
    NoronAbstractSerializer* serializer() const;

    NoronPeer* peer() const;
    bool isConnected() const;
    QString validateToken() const;

    bool isMultiThread() const;
#ifdef QT_QML_LIB
    QJSEngine *jsEngine() const;
    QQmlEngine* qmlEngine() const;
#endif


protected:
    QHash<long, NoronRemoteCallBase*> _calls;
    QTcpSocket *socket;
    qlonglong peerId() const;
    void setPeerId(qlonglong id);

signals:
    void disconnected();
    void peerChanged(NoronPeer* peer);
    void isConnectedChanged(bool isConnected);
    void validateTokenChanged(QString validateToken);
    void serializerChanged(NoronAbstractSerializer* serializer);
#ifdef QT_QML_LIB
    void jsEngineChanged(QJSEngine *jsEngine);
    void qmlEngineChanged(QQmlEngine* qmlEngine);
#endif


private slots:
    void socket_connected();
    void socket_disconnected();
    void socket_onReadyRead();

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

    void addSharedObject(NoronSharedObject *o);
    void removeSharedObject(NoronSharedObject *o);
    void setPeer(NoronPeer* peer);
    void setIsConnected(bool isConnected);
    void setValidateToken(QString validateToken);
    void setSerializer(NoronAbstractSerializer* serializer);
#ifdef QT_QML_LIB
    void setJsEngine(QJSEngine *jsEngine);
    void setQmlEngine(QQmlEngine* qmlEngine);
#endif


private:
    void setIsMultiThread(bool isMultiThread);

    friend class NoronPeer;
    friend class NoronServer;
};

QT_END_NAMESPACE

#endif // NORONABSTRACTHUB_H
