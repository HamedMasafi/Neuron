/**************************************************************************
**
** This file is part of Noron.
** https://github.com/HamedMasafi/Noron
**
** Noron is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Noron is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Noron.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#ifndef NORONREMOTECALL_H
#define NORONREMOTECALL_H

#include <QtCore/qglobal.h>
#include <QtCore/QVariant>
#include <QtCore/QEventLoop>
#include <QtCore/QMetaMethod>

#ifdef QT_QML_LIB
#   include <QtQml/QJSValue>
#endif
#if __cplusplus >= 201103L
#   include <functional>
#endif

QT_BEGIN_NAMESPACE

class NoronRemoteCallBase{
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

    NoronRemoteCallBase();
    NoronRemoteCallBase(ReturnType type);
    NoronRemoteCallBase(QObject *obj, char *slotName);
    NoronRemoteCallBase(QObject *obj, QMetaMethod *method);
#if __cplusplus >= 201103L
    NoronRemoteCallBase(std::function<void()> func);
#endif
#ifdef QT_QML_LIB
    NoronRemoteCallBase(QJSValue jsvalue);
#endif
    void setReturnData(){

    }

    virtual ~NoronRemoteCallBase();
    virtual void returnToCaller();


};

template <typename T>
class NoronRemoteCall : public NoronRemoteCallBase{

public:
#if __cplusplus >= 201103L
    std::function<void(T)> func;

    NoronRemoteCall(std::function<void(T)> func){}
#endif
#ifdef QT_QML_LIB
    NoronRemoteCall(QJSValue jsvalue) : NoronRemoteCallBase(jsvalue) {}
#endif
    NoronRemoteCall() : NoronRemoteCallBase() {}
    NoronRemoteCall(QObject *obj, char *slotName) : NoronRemoteCallBase(obj, slotName) {}
    NoronRemoteCall(QObject *obj, QMetaMethod *method) : NoronRemoteCallBase(obj, method) {}
    ~NoronRemoteCall(){}

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

#endif // NORONREMOTECALL_H
