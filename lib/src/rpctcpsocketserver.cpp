#include "rpcserver.h"
#include "rpcpeer.h"
#include "rpctcpsocketserver_p.h"

#include <QSet>

QT_BEGIN_NAMESPACE

RpcTcpSocketServer::RpcTcpSocketServer(QObject *parent) : QTcpServer(parent)
{
#ifdef RPC_MAX_PENDING_CONNECTIONS
    setMaxPendingConnections(RPC_MAX_PENDING_CONNECTIONS);
#else
    setMaxPendingConnections(100);
#endif
}

void RpcTcpSocketServer::incomingConnection(qintptr socketDescriptor)
{
    emit newIncomingConnection(socketDescriptor);
}

QT_END_NAMESPACE
