#include "rpcserver.h"
#include "rpcpeer.h"
#include "rpctcpsocketserver_p.h"

#include <QSet>

RpcTcpSocketServer::RpcTcpSocketServer(QObject *parent) : QTcpServer(parent)
{
    setMaxPendingConnections(300);
}

void RpcTcpSocketServer::incomingConnection(qintptr socketDescriptor)
{
    emit newIncomingConnection(socketDescriptor);
}
