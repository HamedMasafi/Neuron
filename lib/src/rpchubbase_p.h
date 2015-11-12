#ifndef RPCHUBBASE_P_H
#define RPCHUBBASE_P_H

#include "rpchubbase.h"

QT_BEGIN_NAMESPACE

class RpcHubBasePrivate
{
    RpcHubBase *q_ptr;
    Q_DECLARE_PUBLIC(RpcHubBase)

public:
    RpcHubBasePrivate(RpcHubBase *parent);

    qint16 port;
    QString serverAddress;
    bool autoReconnect;
    bool isConnected;
    QString validateToken;
    RpcSerializerBase *serializer;
    QThread* thread;
};

QT_END_NAMESPACE

#endif // RPCHUBBASE_P_H

