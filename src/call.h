#ifndef CALL_H
#define CALL_H

#include "abstractcall.h"
#include <QDebug>

NEURON_BEGIN_NAMESPACE

template <typename T>
class Call : public AbstractCall
{
    std::function<void(T)> callbackFunction;

public:
    Call(QObject *parent = nullptr) : AbstractCall(parent)
      , callbackFunction(nullptr)
    {}

    Call<T> *then(std::function<void(T)> callback)
    {
        callbackFunction = callback;
        return this;
    }

    T wait() {
        AbstractCall::wait();
        return value.value<T>();
    }

#ifdef QT_QML_LIB
    Call<T> *then(QJSValue callback)
    {
        jsvalue = callback;
        return this;
    }
#endif

protected:
    void returnToCaller() Q_DECL_OVERRIDE
    {
        if (callbackFunction != nullptr)
            callbackFunction(value.value<T>());

#ifdef QT_QML_LIB
        if (jsvalue.isCallable()) {
            qDebug() << "Value is" << value;
            QJSValueList args;
            args.append(toJsValue(value));
            QJSValue callResult = jsvalue.call(args);
            if(callResult.isError())
                qWarning("Uncaught exception at line n; message = %s",
    //                         //qPrintable(callResult.property("fileName").toString()),
    //                         callResult.property("lineNumber").toInt(),
                         qPrintable(callResult.toString()));
        }
#endif
    }
};

template <>
class Call<void> : public AbstractCall
{
    std::function<void()> callbackFunction;

public:
    Call(QObject *parent = nullptr) : AbstractCall(parent)
      , callbackFunction(nullptr)
    {}

    Call<void> *then(std::function<void()> callback)
    {
        callbackFunction = qMove(callback);
        return this;
    }

#ifdef QT_QML_LIB
    Call<void> *then(QJSValue callback)
    {
        jsvalue = callback;
        return this;
    }
#endif

protected:
    void returnToCaller() Q_DECL_OVERRIDE
    {
        if (callbackFunction != nullptr)
            callbackFunction();

#ifdef QT_QML_LIB

        if (jsvalue.isCallable())
            jsvalue.call();
#endif
    }
};

/*
//Call<T>
template <typename T>
Q_OUTOFLINE_TEMPLATE Call<T>::Call(QObject *parent) : AbstractCall(parent)
  , callbackFunction(nullptr)
{ }

template <typename T>
Q_OUTOFLINE_TEMPLATE Call<T> *Call<T>::then(std::function<void(T)> callback)
{
    callbackFunction = callback;
    return this;
}

template <typename T>
Q_OUTOFLINE_TEMPLATE void Call<T>::returnToCaller()
{
    if (callbackFunction != nullptr)
        callbackFunction(value.value<T>());
}


//Call<void>
Q_OUTOFLINE_TEMPLATE Call<void>::Call(QObject *parent = nullptr) : AbstractCall(parent)
  , callbackFunction(nullptr)
{}

Q_OUTOFLINE_TEMPLATE Call<void> *Call<void>::then(std::function<void()> callback)
{
    callbackFunction = callback;
    return this;
}

Q_OUTOFLINE_TEMPLATE void Call<void>::returnToCaller()
{
    if (callbackFunction != nullptr)
        callbackFunction();
}

*/

NEURON_END_NAMESPACE

#endif // CALL_H
