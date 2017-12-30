#ifndef SYNTAX_PEER_H
#define SYNTAX_PEER_H

#include "method_slot_peer.h"
#include "decl_signal_peer.h"

#include "syntax.h"

#ifdef N_CLASS_IMPL
#undef N_CLASS_IMPL
#endif

#define N_CLASS_IMPL(class) \
        class::class(QObject *parent) : NeuronPeer(parent) \
        {  \
            setPeerName(#class); \
        }    \
        class::class(NeuronAbstractHub *hub, QObject *parent) : NeuronPeer(parent)    \
        {   \
            setPeerName(#class); \
            if(hub)    \
                setHub(hub);    \
        }

#endif // SYNTAX_PEER_H
