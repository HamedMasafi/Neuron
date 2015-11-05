#include "rpcremotecall_p.h"



void RemoteCallBase::returnToCaller()
{
#if __cplusplus >= 201103L
    if(type == Function)
        func();
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

//#if __cplusplus >= 201103L
//template <typename T>
//RemoteCall<T>::RemoteCall(std::function<void (T)> func) : RemoteCallBase()
//{
//    this->type = Function;
//    this->func = func;
//}
//#endif

//template <typename T>
//RemoteCall<T>::RemoteCall() : RemoteCallBase()
//{

//}

//template <typename T>
//RemoteCall<T>::RemoteCall(QObject *obj, char *slotName) : RemoteCallBase(obj, slotName)
//{
//}

//template <typename T>
//RemoteCall<T>::RemoteCall(QObject *obj, QMetaMethod *method) : RemoteCallBase(obj, method)
//{
//}

//template <typename T>
//RemoteCall<T>::~RemoteCall()
//{

//}

//template <typename T>
//void RemoteCall<T>::returnToCaller(){
//#if __cplusplus >= 201103L
//    if(type == Function)
//        func(returnData.value<T>());
//#endif

//    if(type == Slot)
//        obj->metaObject()->invokeMethod(obj,
//                                        slotName,
//                                        Q_ARG(T, returnData.value<T>()));

//    if(type == EventLoop)
//        eventLoop->quit();

//    if(type == MetaMethod)
//        method->invoke(obj,
//                       Q_ARG(T, returnData.value<T>()));

//    //        RemoteCallBase::returnToCaller();
//}



RpcRemoteCall::RpcRemoteCall(QVariant::Type type) : returnType(RpcRemoteCall::EventLoop)
{
    eventLoop = new QEventLoop();
}

RpcRemoteCall::RpcRemoteCall(QVariant::Type type, std::function<void ()> func) : returnType(RpcRemoteCall::Function),
    _funcVoid(func)
{

}

RpcRemoteCall::RpcRemoteCall(QVariant::Type type, std::function<void (QVariant)> func) : returnType(RpcRemoteCall::Function),
    _func(func)
{
}

RpcRemoteCall::RpcRemoteCall(QVariant::Type type, QObject *obj, char *slotName) : returnType(RpcRemoteCall::Slot),
    _slotName(slotName), _target(obj)
{

}

RpcRemoteCall::RpcRemoteCall(QVariant::Type type, QObject *obj, QMetaMethod *method) : returnType(RpcRemoteCall::MetaMethod),
    _target(obj)//, _method(method)
{

}


void RpcRemoteCall::returnToCaller()
{
    RemoteCall<QStringList> *rpc = new RemoteCall<QStringList>([] (QStringList){

    });
    RpcRemoteCall *rpc2 = new RpcRemoteCall(QVariant::StringList, [](QVariant){

    });

    QGenericArgument arg;
    if(_type != QVariant::Invalid){
        const void *data = returnData.data();
        const char *name = returnData.typeName();

        arg = QGenericArgument(name, data);
    }
    switch(returnType){
#if __cplusplus >= 201103L
    case RpcRemoteCall::Function:
        if(_type == QVariant::Invalid)
            _funcVoid();
        else
            _func(returnData);
        break;
#endif

    case RpcRemoteCall::Slot:
        if(_type == QVariant::Invalid)
            _target->metaObject()->invokeMethod(_target, _slotName);
        else
            _target->metaObject()->invokeMethod(_target, _slotName, arg);
        break;
    case RpcRemoteCall::EventLoop:
        eventLoop->quit();
        break;

    case RpcRemoteCall::MetaMethod:
        if(_type == QVariant::Invalid)
            _method->invoke(_target);
        else
            _method->invoke(_target, arg);
        break;
    }
}

template<typename T>
RpcRemoteCall::RpcRemoteCall(QVariant::Type type, std::function<void (T)> func)
{

}
