#ifndef SYNTAX_SHAREDOBJECT_H
#define SYNTAX_SHAREDOBJECT_H

#include "method_slot_sharedobject.h"
#include "decl_signal_sharedobject.h"

#include "syntax.h"

#ifdef N_CLASS_IMPL
#undef N_CLASS_IMPL
#endif

#define N_CLASS_IMPL(class) \
        class::class(QObject *parent) : NoronSharedObject(parent) \
        {  \
            setPeerName(#class); \
        }    \
        class::class(NoronAbstractHub *hub, QObject *parent) : NoronSharedObject(parent)    \
        {   \
            if(hub){    \
                setHub(hub);    \
                hub->addSharedObject(this); \
            }   \
            setPeerName(#class); \
        }

#endif // SYNTAX_SHAREDOBJECT_H
