#include "%3.h"

#include <QMetaObject>
#include <QMetaMethod>
%4
NORON_BEGIN_NAMESPACE

%1::%1(QObject *parent) : %6(parent)
{

}

%1::%1(NoronAbstractHub *hub, QObject *parent) : %6(parent)
{
    if(hub){
        setHub(hub);
        hub->addSharedObject(this);
    }
}

%2
NORON_END_NAMESPACE
