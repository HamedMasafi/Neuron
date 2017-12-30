#include "%3.h"

#include <QMetaObject>
#include <QMetaMethod>
%4
NEURON_BEGIN_NAMESPACE

%1::%1(QObject *parent) : %6(parent)
{

}

%1::%1(NeuronAbstractHub *hub, QObject *parent) : %6(parent)
{
    if(hub){
        setHub(hub);
        hub->addSharedObject(this);
    }
}

%2
NEURON_END_NAMESPACE
