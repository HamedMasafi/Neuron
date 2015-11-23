#include "noronserver.h"
#include "noronpeer.h"
#include "norontcpsocketserver_p.h"

#include <QSet>

QT_BEGIN_NAMESPACE

NoronTcpSocketServer::NoronTcpSocketServer(QObject *parent) : QTcpServer(parent)
{
#ifdef NORON_MAX_PENDING_CONNECTIONS
    setMaxPendingConnections(NORON_MAX_PENDING_CONNECTIONS);
#else
    setMaxPendingConnections(100);
#endif
}

void NoronTcpSocketServer::incomingConnection(qintptr socketDescriptor)
{
    emit newIncomingConnection(socketDescriptor);
}

QT_END_NAMESPACE
