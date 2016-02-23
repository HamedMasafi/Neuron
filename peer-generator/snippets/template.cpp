#include "%3.h"

#include <QMetaObject>
#include <QMetaMethod>
%4
QT_BEGIN_NAMESPACE

%1::%1(QObject *parent) : %6(parent)
{

}

%1::%1(NoronAbstractHub *hub, QObject *parent) : %6(parent)
{
    if(hub)
        setHub(hub);
}

%2
QT_END_NAMESPACE
