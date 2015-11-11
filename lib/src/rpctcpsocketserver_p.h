#ifndef RPCTCPSOCKETSERVER_H
#define RPCTCPSOCKETSERVER_H

#include <QTcpServer>

QT_BEGIN_NAMESPACE

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

QT_END_NAMESPACE

#endif // RPCTCPSOCKETSERVER_H
