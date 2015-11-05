#ifndef RPCHUBBASE_H
#define RPCHUBBASE_H

#include "rpcglobal.h"
#include "rpcremotecall_p.h"

class RpcPeer;
class RpcSerializerBase;
class TOOJ_EXPORT RpcHubBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint16 port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString serverAddress READ serverAddress WRITE setServerAddress NOTIFY serverAddressChanged)
    Q_PROPERTY(bool autoReconnect READ autoReconnect WRITE setAutoReconnect NOTIFY autoReconnectChanged)
    Q_PROPERTY(bool isConnected READ isConnected WRITE setIsConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(QString validateToken READ validateToken WRITE setValidateToken NOTIFY validateTokenChanged)
    Q_PROPERTY(RpcSerializerBase* serializer READ serializer WRITE setSerializer NOTIFY serializerChanged)

    qint16 m_port;
    QString m_serverAddress;
    bool m_autoReconnect;
    bool m_isConnected;
    QString m_validateToken;

    RpcSerializerBase *m_serializer;

public:
    explicit RpcHubBase(QObject *parent = 0);

    Q_INVOKABLE virtual void addSharedObject(RpcPeer *o);
    virtual void connectToServer(QString address, qint16 port);
    virtual bool setSocketDescriptor(qintptr socketDescriptor);

    virtual void beginTransaction();
    virtual void rollback();
    virtual void commit();

    Q_INVOKABLE qint16 port() const;
    Q_INVOKABLE QString serverAddress() const;
    Q_INVOKABLE bool autoReconnect() const;
    Q_INVOKABLE bool isConnected() const;
    Q_INVOKABLE QString validateToken() const;
    Q_INVOKABLE RpcSerializerBase *serializer() const;

protected:
    QHash<long, RemoteCallBase*> _calls;
    QHash<QString, QObject*> _classes;

signals:
    void disconnected();
    void portChanged(qint16 port);
    void serverAddressChanged(QString serverAddress);
    void autoReconnectChanged(bool autoReconnect);
    void isConnectedChanged(bool isConnected);
    void validateTokenChanged(QString validateToken);

    void serializerChanged(RpcSerializerBase *serializer);

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

    friend class RpcPeer;
};

#endif // RPCHUBBASE_H
