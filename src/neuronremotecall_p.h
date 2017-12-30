/**************************************************************************
**
** This file is part of Neuron.
** https://github.com/HamedMasafi/Neuron
**
** Neuron is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Neuron is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Neuron.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#ifndef NEURONREMOTECALL_H
#define NEURONREMOTECALL_H

#include "neuronglobal.h"

#include <QtCore/qglobal.h>
#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QEventLoop>
#include <QtCore/QMetaMethod>

#ifdef QT_QML_LIB
#   include <QtQml/QJSEngine>
#   include <QtQml/QQmlEngine>
#   include <QtQml/QJSValue>
#endif
#if __cplusplus >= 201103L
#   include <functional>
#endif

NEURON_BEGIN_NAMESPACE

class NeuronRemoteCallBase{
public:
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

    ReturnType type;
#if __cplusplus >= 201103L
    std::function<void()> func;
#endif
#ifdef QT_QML_LIB
    QQmlEngine *qmlEngine;
    QJSEngine *jsEngine;
    QJSValue jsvalue;
#endif
    char *slotName;
    QEventLoop *eventLoop;
    QObject *obj;
    QMetaMethod *method;
    QVariant returnData;

    NeuronRemoteCallBase();
    NeuronRemoteCallBase(ReturnType type);
    NeuronRemoteCallBase(QObject *obj, char *slotName);
    NeuronRemoteCallBase(QObject *obj, QMetaMethod *method);
#if __cplusplus >= 201103L
    NeuronRemoteCallBase(std::function<void()> func);
#endif
#ifdef QT_QML_LIB
    NeuronRemoteCallBase(QJSValue jsvalue, QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    QJSValue toJsValue(QVariant v);
    QJSValue toJsValue(QVariantMap map);
    QJSValue toJsValue(QVariantList list);
#endif
    void setReturnData(){

    }

    virtual ~NeuronRemoteCallBase();
    virtual void returnToCaller();
};

template <typename T>
class NeuronRemoteCall : public NeuronRemoteCallBase{

public:
#if __cplusplus >= 201103L
    std::function<void(T)> _func;

    NeuronRemoteCall(std::function<void(T)> func) : NeuronRemoteCallBase(), _func(func){}
#endif
#ifdef QT_QML_LIB
    NeuronRemoteCall(QJSValue jsvalue, QQmlEngine *qmlEngine, QJSEngine *jsEngine) : NeuronRemoteCallBase(jsvalue, qmlEngine, jsEngine) {}
#endif
    NeuronRemoteCall() : NeuronRemoteCallBase() {}
    NeuronRemoteCall(ReturnType type) : NeuronRemoteCallBase(type) {}
    NeuronRemoteCall(QObject *obj, char *slotName) : NeuronRemoteCallBase(obj, slotName) {}
    NeuronRemoteCall(QObject *obj, QMetaMethod *method) : NeuronRemoteCallBase(obj, method) {}
    ~NeuronRemoteCall(){}

    void returnToCaller(){
#if __cplusplus >= 201103L
        if(type == Function){
            _func(returnData.value<T>());
        }
#endif
#ifdef QT_QML_LIB
        if(type == JSValue/* && jsvalue.isCallable()*/) {
            QJSValueList values;

            values.append(toJsValue(returnData));

            QJSValue callResult = jsvalue.call(values);

            if(callResult.isError())
                qWarning("Uncaught exception at line n; message = %s",
//                         //qPrintable(callResult.property("fileName").toString()),
//                         callResult.property("lineNumber").toInt(),
                         qPrintable(callResult.toString()));
        }
#endif
        if(type == Slot){
            QGenericArgument arg(returnData.typeName(), returnData.data());
            QMetaObject::invokeMethod(obj, slotName, arg);
        }

        if(type == EventLoop){
            eventLoop->quit();
            eventLoop->deleteLater();
        }

        if(type == MetaMethod){
            QGenericArgument arg(returnData.typeName(), returnData.data());
            method->invoke(obj, arg);
        }
    }

};

template <typename T>
class NeuronRemoteCallList : public NeuronRemoteCallBase{

};

NEURON_END_NAMESPACE

#endif // NEURONREMOTECALL_H
