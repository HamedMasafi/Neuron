#ifndef NEURONSERVERHUB_P_H
#define NEURONSERVERHUB_P_H

#include "serverhub.h"

class QEventLoop;

NEURON_BEGIN_NAMESPACE

class ServerHubPrivate{
    ServerHub *q_ptr;
    Q_DECLARE_PUBLIC(ServerHub)

public:
    ServerHubPrivate(ServerHub *parent);

    ServerThread *serverThread;
    QEventLoop *connectionEventLoop;
};

NEURON_END_NAMESPACE

#endif // NEURONSERVERHUB_P_H
