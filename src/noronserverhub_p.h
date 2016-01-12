#ifndef NORONSERVERHUB_P_H
#define NORONSERVERHUB_P_H

#include "noronserverhub.h"

QT_BEGIN_NAMESPACE

class NoronServerHubPrivate{
    NoronServerHub *q_ptr;
    Q_DECLARE_PUBLIC(NoronServerHub)

public:
    NoronServerHubPrivate(NoronServerHub *parent);

    NoronServerThread *serverThread;
};

QT_END_NAMESPACE

#endif // NORONSERVERHUB_P_H
