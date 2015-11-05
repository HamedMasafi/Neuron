#ifndef RPCTCPSOCKETSERVER_H
#define RPCTCPSOCKETSERVER_H

#include <QTcpServer>

class RpcPeer;
class QTcpServer;
class RpcServer;
class RpcTcpSocketServer : public QTcpServer
{
    Q_OBJECT

public:
    RpcTcpSocketServer(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:
	void newIncomingConnection(qintptr socketDescriptor);
};

#endif // RPCTCPSOCKETSERVER_H
