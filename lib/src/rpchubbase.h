#ifndef RPCHUBBASE_H
#define RPCHUBBASE_H

#include "rpcglobal.h"
#include "rpcremotecall_p.h"

QT_BEGIN_NAMESPACE

class RpcPeer;
class RpcSerializerBase;
class RpcHubBasePrivate;
class TOOJ_EXPORT RpcHubBase : public QObject
{
    Q_OBJECT

    RpcHubBasePrivate *d_ptr;
    Q_DECLARE_PRIVATE(RpcHubBase)

    Q_PROPERTY(qint16 port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString serverAddress READ serverAddress WRITE setServerAddress NOTIFY serverAddressChanged)
    Q_PROPERTY(bool autoReconnect READ autoReconnect WRITE setAutoReconnect NOTIFY autoReconnectChanged)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(QString validateToken READ validateToken WRITE setValidateToken NOTIFY validateTokenChanged)
    Q_PROPERTY(RpcSerializerBase* serializer READ serializer WRITE setSerializer NOTIFY serializerChanged)
    Q_PROPERTY(QThread* thread READ thread WRITE setThread NOTIFY threadChanged)

public:
    explicit RpcHubBase(QObject *parent = 0);

    Q_INVOKABLE virtual void addSharedObject(RpcPeer *o);
    QList<RpcPeer*> sharedObjects() const;

    virtual void connectToServer(QString address, qint16 port);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);

    virtual void beginTransaction() = 0;
    virtual void rollback() = 0;
    virtual void commit() = 0;

    qint16 port() const;
    QString serverAddress() const;
    bool autoReconnect() const;
    bool isConnected() const;
    QString validateToken() const;
    RpcSerializerBase *serializer() const;
    QThread* thread() const;

protected:
    QHash<long, RemoteCallBase*> _calls;
    QHash<QString, RpcPeer*> _classes;

signals:
    void portChanged(qint16 port);
    void serverAddressChanged(QString serverAddress);
    void autoReconnectChanged(bool autoReconnect);
    void isConnectedChanged(bool isConnected);
    void validateTokenChanged(QString validateToken);
    void serializerChanged(RpcSerializerBase *serializer);
    void threadChanged(QThread* thread);

public slots:
    virtual qlonglong invokeOnPeer(
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
            QVariant val9 = QVariant()) = 0;

    void setPort(qint16 port);
    void setServerAddress(QString serverAddress);
    void setAutoReconnect(bool autoReconnect);
    void setIsConnected(bool isConnected);
    void setValidateToken(QString validateToken);
    void setSerializer(RpcSerializerBase *serializerObject);
    void setThread(QThread* thread);

    friend class RpcPeer;
};

QT_END_NAMESPACE

#endif // RPCHUBBASE_H
