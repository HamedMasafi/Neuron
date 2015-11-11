#include "rpcremotecall_p.h"

QT_BEGIN_NAMESPACE

void RemoteCallBase::returnToCaller()
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

RemoteCallBase::RemoteCallBase(){
    this->type = None;
}

RemoteCallBase::RemoteCallBase(RemoteCallBase::ReturnType type)
{

    if(type == EventLoop){
        this->type = EventLoop;
        eventLoop = new QEventLoop();
    }
}

#if __cplusplus >= 201103L
RemoteCallBase::RemoteCallBase(std::function<void ()> func)
{
    this->type = Function;
    this->func = func;
}
#endif
#ifdef QT_QML_LIB
RemoteCallBase::RemoteCallBase(QJSValue jsvalue)
{
    this->type = JSValue;
    this->jsvalue = jsvalue;
}
#endif
RemoteCallBase::RemoteCallBase(QObject *obj, char *slotName)
{
    this->type = Slot;
    this->obj = obj;
    this->slotName = slotName;
}

RemoteCallBase::RemoteCallBase(QObject *obj, QMetaMethod *method)
{
    this->type = MetaMethod;
    this->obj = obj;
    this->method = method;
}

RemoteCallBase::~RemoteCallBase()
{

}




QT_END_NAMESPACE
