#ifndef SYNTAX_SHAREDOBJECT_H
#define SYNTAX_SHAREDOBJECT_H

#   include "method_slot_peer.h"
#   include "decl_signal_peer.h"
//#ifdef NEURON_CLIENT
//#else
//#   include "method_slot_sharedobject.h"
//#   include "decl_signal_sharedobject.h"
//#endif

#include "syntax.h"

#ifdef N_CLASS_IMPL
#undef N_CLASS_IMPL
#endif

#define N_CLASS_IMPL(class) \
        class::class(QObject *parent) : NEURON_WRAP_NAMESPACE(NeuronSharedObject)(parent) \
        {  \
            setPeerName(#class); \
        }    \
        class::class(NEURON_WRAP_NAMESPACE(NeuronAbstractHub) *hub, QObject *parent) : NEURON_WRAP_NAMESPACE(NeuronSharedObject)(parent)    \
        {   \
            setPeerName(#class); \
            if(hub){    \
                setHub(hub);    \
                hub->attachSharedObject(this); \
            }   \
        }

#endif // SYNTAX_SHAREDOBJECT_H
