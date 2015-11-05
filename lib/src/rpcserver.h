#ifndef PRCSERVER_H
#define PRCSERVER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QSet>
#include <QTcpServer>

#include "rpctcpsocketserver_p.h"
#include "rpchubbase.h"
#include "rpcglobal.h"


class RpcPeer;
class TOOJ_EXPORT RpcServer : public RpcHubBase
{
    Q_OBJECT
    Q_PROPERTY(int typeId READ typeId WRITE setTypeId NOTIFY typeIdChanged)
    Q_PROPERTY(bool isMultiThread READ isMultiThread WRITE setIsMultiThread NOTIFY isMultiThreadChanged)

    RpcTcpSocketServer *serverSocket;
    QSet<RpcPeer*> _peers;

    int m_typeId;

    QHash<QString, RpcPeer*> _classes;

    bool m_isMultiThread;

public:
    explicit RpcServer(qint16 port, QObject *parent = 0);

    QSet<RpcPeer*> peers();

    int typeId() const;
    bool isMultiThread() const;
    template <typename T> void registerType(){
        m_typeId = qRegisterMetaType<T>();
    }

public slots:
	void server_newIncomingConnection(qintptr socketDescriptor);
    void setTypeId(int typeId);
    void setIsMultiThread(bool isMultiThread);

signals:
    void peerConnected(RpcPeer *peer);
    void peerDisconnected(RpcPeer *peer);
    void typeIdChanged(int typeId);
    void isMultiThreadChanged(bool isMultiThread);

private slots:
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
    void peer_disconnected();
};


#endif // PRCSERVER_H
