#ifndef RPCREMOTECALL_H
#define RPCREMOTECALL_H

#include <QtCore/qglobal.h>

#include <QVariant>
#include <QEventLoop>
#include <QMetaMethod>

#if __cplusplus >= 201103L
#   include <functional>
#endif

class RemoteCallBase{
public:
#if __cplusplus >= 201103L
    std::function<void()> func;
#endif

    enum ReturnType{
        None,
#if __cplusplus >= 201103L
        Function,
#endif
        Slot,
        EventLoop,
        MetaMethod
    };

    char *slotName;
    QEventLoop *eventLoop;
    QObject *obj;
    ReturnType type;
    QMetaMethod *method;
    QVariant returnData;

    RemoteCallBase();
    RemoteCallBase(ReturnType type);
    RemoteCallBase(QObject *obj, char *slotName);
    RemoteCallBase(QObject *obj, QMetaMethod *method);
#if __cplusplus >= 201103L
    RemoteCallBase(std::function<void()> func);
#endif

    void setReturnData(){

    }

    virtual ~RemoteCallBase();
    virtual void returnToCaller();


};

template <typename T>
class RemoteCall : public RemoteCallBase{

public:
#if __cplusplus >= 201103L
    std::function<void(T)> func;

    RemoteCall(std::function<void(T)> func){}
#endif
    RemoteCall(){}
    RemoteCall(QObject *obj, char *slotName){}
    RemoteCall(QObject *obj, QMetaMethod *method){}
    ~RemoteCall(){}

    void returnToCaller(){
#if __cplusplus >= 201103L
    if(type == Function)
        func(returnData.value<T>());
#endif

    if(type == Slot)
        obj->metaObject()->invokeMethod(obj,
                                        slotName,
                                        Q_ARG(T, returnData.value<T>()));

    if(type == EventLoop)
        eventLoop->quit();

    if(type == MetaMethod)
        method->invoke(obj,
                       Q_ARG(T, returnData.value<T>()));

    //        RemoteCallBase::returnToCaller();
}

};

class RpcRemoteCall{
    enum ReturnType{
        None,
#if __cplusplus >= 201103L
        Function,
#endif
        Slot,
        EventLoop,
        MetaMethod
    };

    char *_slotName;
    QEventLoop *eventLoop;
    QObject *_target;
    ReturnType returnType;
    QVariant returnData;
    QMetaMethod *_method;
    QVariant::Type _type;
#if __cplusplus >= 201103L
    std::function<void()> _funcVoid;
    std::function<void(QVariant)> _func;
#endif

public:
    RpcRemoteCall(QVariant::Type type);
#if __cplusplus >= 201103L
    RpcRemoteCall(QVariant::Type type, std::function<void()> func);
    RpcRemoteCall(QVariant::Type type, std::function<void(QVariant)> func);

    template<typename T>
    RpcRemoteCall(QVariant::Type type, std::function<void(T)> func);
#endif
    RpcRemoteCall(QVariant::Type type, QObject *obj, char *slotName);
    RpcRemoteCall(QVariant::Type type, QObject *obj, QMetaMethod *method);

    void returnToCaller();
};

#endif // RPCREMOTECALL_H
