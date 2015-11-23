#ifndef RPCSERVER_P_H
#define RPCSERVER_P_H

#include "noronserver.h"

QT_BEGIN_NAMESPACE

class NoronServerPrivate{
    NoronServer *q_ptr;
    Q_DECLARE_PUBLIC(NoronServer)

public:
    NoronServerPrivate(NoronServer *parent);

    NoronTcpSocketServer *serverSocket;
    QSet<NoronPeer*> peers;
    int typeId;
    QHash<QString, NoronPeer*> classes;
    bool isMultiThread;
};

QT_END_NAMESPACE

#endif // RPCSERVER_P_H

