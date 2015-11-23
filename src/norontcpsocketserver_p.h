#ifndef RPCTCPSOCKETSERVER_H
#define RPCTCPSOCKETSERVER_H

#include <QTcpServer>

QT_BEGIN_NAMESPACE

class NoronPeer;
class QTcpServer;
class NoronServer;
class NoronTcpSocketServer : public QTcpServer
{
    Q_OBJECT

public:
    NoronTcpSocketServer(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor);

signals:
	void newIncomingConnection(qintptr socketDescriptor);
};

QT_END_NAMESPACE

#endif // RPCTCPSOCKETSERVER_H
