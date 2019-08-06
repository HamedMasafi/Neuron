#ifndef NEURONSERVERHUB_P_H
#define NEURONSERVERHUB_P_H

#include "global.h"
#include <QSharedData>

class QEventLoop;

NEURON_BEGIN_NAMESPACE

class ServerThread;
class ServerHubPrivate : public QSharedData {
public:
    ServerHubPrivate();

    ServerThread *serverThread;
    QEventLoop *connectionEventLoop;
};

NEURON_END_NAMESPACE

#endif // NEURONSERVERHUB_P_H
