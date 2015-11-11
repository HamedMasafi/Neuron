#ifndef RPCREMOTECALL_H
#define RPCREMOTECALL_H

#include <QtCore/qglobal.h>

#include <QVariant>
#include <QEventLoop>
#include <QMetaMethod>

#ifdef QT_QML_LIB
#   include <QJSValue>
#endif
#if __cplusplus >= 201103L
#   include <functional>
#endif

QT_BEGIN_NAMESPACE

class RemoteCallBase{
public:
#if __cplusplus >= 201103L
    std::function<void()> func;
#endif
#ifdef QT_QML_LIB
    QJSValue jsvalue;
#endif

    enum ReturnType{
        None,
#if __cplusplus >= 201103L
        Function,
#endif
#ifdef QT_QML_LIB
        JSValue,
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
#ifdef QT_QML_LIB
    RemoteCallBase(QJSValue jsvalue);
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
#ifdef QT_QML_LIB
    RemoteCall(QJSValue jsvalue) : RemoteCallBase(jsvalue) {}
#endif
    RemoteCall() : RemoteCallBase() {}
    RemoteCall(QObject *obj, char *slotName) : RemoteCallBase(obj, slotName) {}
    RemoteCall(QObject *obj, QMetaMethod *method) : RemoteCallBase(obj, method) {}
    ~RemoteCall(){}

    void returnToCaller(){
#if __cplusplus >= 201103L
        if(type == Function)
            func(returnData.value<T>());
#endif
#ifdef QT_QML_LIB
        if(type == JSValue){
            QJSValueList values;
            values.append(QJSValue(returnData.toString()));
            jsvalue.call(values);
        }
#endif
        if(type == Slot)
            obj->metaObject()->invokeMethod(obj, slotName, Q_ARG(T, returnData.value<T>()));

        if(type == EventLoop)
            eventLoop->quit();

        if(type == MetaMethod)
            method->invoke(obj, Q_ARG(T, returnData.value<T>()));
    }

};

QT_END_NAMESPACE

#endif // RPCREMOTECALL_H
