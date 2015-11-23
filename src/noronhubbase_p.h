#ifndef RPCHUBBASE_P_H
#define RPCHUBBASE_P_H

#include "noronhubbase.h"

QT_BEGIN_NAMESPACE

class NoronHubBasePrivate
{
    NoronHubBase *q_ptr;
    Q_DECLARE_PUBLIC(NoronHubBase)

public:
    NoronHubBasePrivate(NoronHubBase *parent);

    qint16 port;
    QString serverAddress;
    bool autoReconnect;
    bool isConnected;
    QString validateToken;
    NoronSerializerBase *serializer;
    QThread* thread;
};

QT_END_NAMESPACE

#endif // RPCHUBBASE_P_H

