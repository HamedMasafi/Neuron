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
    const QObject *obj;
    ReturnType type;
    QVariant returnData;
    const QMetaMethod *method;

    RemoteCallBase();
    RemoteCallBase(ReturnType type);
    RemoteCallBase(const QObject *obj, char *slotName);
    RemoteCallBase(const QObject *obj, const QMetaMethod &method);
#if __cplusplus >= 201103L
    RemoteCallBase(std::function<void()> func);
#endif

    virtual ~RemoteCallBase();
    virtual void returnToCaller();


};

template <typename T>
class RemoteCall : public RemoteCallBase{

public:
#if __cplusplus >= 201103L
    std::function<void(T)> func;

    RemoteCall(std::function<void(T)> func);
#endif

    RemoteCall(const QObject *obj, char *slotName);
    RemoteCall(const QObject *obj, const QMetaMethod &method);
    ~RemoteCall();

    void returnToCaller();
};

#endif // RPCREMOTECALL_H
