#ifndef <CLASSNAME/>_H
#define <CLASSNAME/>_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#if __cplusplus >= 201103L
#   include <functional>
#endif

#ifdef QT_QML_LIB
#   include <QJSValue>
#endif

#include <NoronAbstractHub>
<includes>
#include <<IncludeName/>>
</includes>

QT_BEGIN_NAMESPACE

class <ClassName/> : public <BaseType/>
{
    Q_OBJECT
%5

public:
    Q_INVOKABLE <ClassName/>(QObject *parent = 0);
    <ClassName/>(NoronAbstractHub *hub, QObject *parent = 0);

<methods>
<group/>
<method>
    <returnType/> <methodName/>();
    <returnType/> <methodName/>(<signature/><sep/>const QObject *obj, char *callbackSlot);
    <returnType/> <methodName/>(<signature/><sep/>const QObject *obj, const QMetaMethod *callbackMethod);
#if __cplusplus >= 201103L
    <returnType/> <methodName/>(<signature/><sep/>std::function<void(<returnType/>)> callbackFunction);
#endif
#ifdef QT_QML_LIB
    <returnType/> <methodName/>(<signature/><sep/>QJSValue callbackFunction);
#endif
</method>
</methods>

};

QT_END_NAMESPACE

#endif // %3_H
