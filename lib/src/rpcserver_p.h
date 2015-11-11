#ifndef RPCSERVER_P_H
#define RPCSERVER_P_H

#include "rpcserver.h"

QT_BEGIN_NAMESPACE

class RpcServerPrivate{
    RpcServer *q_ptr;
    Q_DECLARE_PUBLIC(RpcServer)

public:
    RpcServerPrivate(RpcServer *parent);

    RpcTcpSocketServer *serverSocket;
    QSet<RpcPeer*> peers;
    int typeId;
    QHash<QString, RpcPeer*> classes;
    bool isMultiThread;
};

QT_END_NAMESPACE

#endif // RPCSERVER_P_H

