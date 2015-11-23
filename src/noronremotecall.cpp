#include "noronremotecall_p.h"

QT_BEGIN_NAMESPACE

void NoronRemoteCallBase::returnToCaller()
{
#if __cplusplus >= 201103L
    if(type == Function)
        func();
#endif
#ifdef QT_QML_LIB
    if(type == JSValue)
        jsvalue.call();
#endif
    if(type == Slot)
        obj->metaObject()->invokeMethod(const_cast<QObject*>(obj), slotName);

    if(type == EventLoop)
        eventLoop->quit();

    if(type == MetaMethod)
        method->invoke(const_cast<QObject*>(obj));
}

NoronRemoteCallBase::NoronRemoteCallBase(){
    this->type = None;
}

NoronRemoteCallBase::NoronRemoteCallBase(NoronRemoteCallBase::ReturnType type)
{

    if(type == EventLoop){
        this->type = EventLoop;
        eventLoop = new QEventLoop();
    }
}

#if __cplusplus >= 201103L
NoronRemoteCallBase::NoronRemoteCallBase(std::function<void ()> func)
{
    this->type = Function;
    this->func = func;
}
#endif
#ifdef QT_QML_LIB
NoronRemoteCallBase::NoronRemoteCallBase(QJSValue jsvalue)
{
    this->type = JSValue;
    this->jsvalue = jsvalue;
}
#endif
NoronRemoteCallBase::NoronRemoteCallBase(QObject *obj, char *slotName)
{
    this->type = Slot;
    this->obj = obj;
    this->slotName = slotName;
}

NoronRemoteCallBase::NoronRemoteCallBase(QObject *obj, QMetaMethod *method)
{
    this->type = MetaMethod;
    this->obj = obj;
    this->method = method;
}

NoronRemoteCallBase::~NoronRemoteCallBase()
{

}




QT_END_NAMESPACE
