#ifndef NEURONSERVERHUB_P_H
#define NEURONSERVERHUB_P_H

#include "neuronserverhub.h"

class QEventLoop;

NEURON_BEGIN_NAMESPACE

class NeuronServerHubPrivate{
    NeuronServerHub *q_ptr;
    Q_DECLARE_PUBLIC(NeuronServerHub)

public:
    NeuronServerHubPrivate(NeuronServerHub *parent);

    NeuronServerThread *serverThread;
    QEventLoop *connectionEventLoop;
};

NEURON_END_NAMESPACE

#endif // NEURONSERVERHUB_P_H
