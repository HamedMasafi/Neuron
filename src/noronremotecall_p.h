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

#include "noronglobal.h"

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

NORON_BEGIN_NAMESPACE

class NoronRemoteCallBase{
public:
#if __cplusplus >= 201103L
    std::function<void()> func;
#endif
#ifdef QT_QML_LIB
    QJSValue jsvalue;
    QJSEngine *jsEngine;
    QQmlEngine *qmlEngine;
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
    NoronRemoteCallBase(QJSValue jsvalue, QQmlEngine *qmlEngine, QJSEngine *jsEngine);

    QJSValue toJsValue(QVariant v);
    QJSValue toJsValue(QVariantMap map);
    QJSValue toJsValue(QVariantList list);
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
    std::function<void(T)> _func;

    NoronRemoteCall(std::function<void(T)> func) : NoronRemoteCallBase(), _func(func){}
#endif
#ifdef QT_QML_LIB
    NoronRemoteCall(QJSValue jsvalue, QQmlEngine *qmlEngine, QJSEngine *jsEngine) : NoronRemoteCallBase(jsvalue, qmlEngine, jsEngine) {}
#endif
    NoronRemoteCall() : NoronRemoteCallBase() {}
    NoronRemoteCall(ReturnType type) : NoronRemoteCallBase(type) {}
    NoronRemoteCall(QObject *obj, char *slotName) : NoronRemoteCallBase(obj, slotName) {}
    NoronRemoteCall(QObject *obj, QMetaMethod *method) : NoronRemoteCallBase(obj, method) {}
    ~NoronRemoteCall(){}

    void returnToCaller(){
#if __cplusplus >= 201103L
        if(type == Function){
            _func(returnData.value<T>());
        }
#endif
#ifdef QT_QML_LIB
        if(type == JSValue/* && jsvalue.isCallable()*/) {
            QJSValueList values;
            /*if(returnData.type() == QVariant::List){
                QVariantList list = returnData.toList();
                QJSValue param1;
                int i = 0;
                param1 = jsEngine->newArray(list.length());

                foreach (QVariant var, list) {
                    if(QString(var.typeName()).endsWith("*")){
                        QObject *o = var.value<QObject*>();

                        K_REG_OBJECT(o);

                        if(!o)
                            qWarning("Object is not valid");
                        qmlEngine->setObjectOwnership(o, QQmlEngine::JavaScriptOwnership);
                        param1.setProperty(i, jsEngine->newQObject(o));
                    }else{
                        switch(var.type()){
                        case QVariant::Int:
                            param1.setProperty(i, QJSValue(var.toInt()));
                            break;

                        case QVariant::Bool:
                            param1.setProperty(i, QJSValue(var.toBool()));
                            break;

                        case QVariant::UInt:
                            param1.setProperty(i, QJSValue(var.toUInt()));
                            break;

                        case QVariant::Double:
                            param1.setProperty(i, QJSValue(var.toDouble()));
                            break;

                        default:
                            param1.setProperty(i, QJSValue(var.toString()));
                        }
                    }
                    i++;
                }

                values.append(param1);
            }else{
                if(QString(returnData.typeName()).endsWith("*")){
                    QObject *o = returnData.value<QObject*>();
                    if(!o)
                        qWarning("Object is not valid");
                    qmlEngine->setObjectOwnership(o, QQmlEngine::JavaScriptOwnership);
                    values.append(jsEngine->newQObject(o));
                }else{
                    switch(returnData.type()){
                    case QVariant::Int:
                        values.append(QJSValue(returnData.toInt()));
                        break;

                    case QVariant::Bool:
                        values.append(QJSValue(returnData.toBool()));
                        break;

                    case QVariant::UInt:
                        values.append(QJSValue(returnData.toUInt()));
                        break;

                    case QVariant::Double:
                        values.append(QJSValue(returnData.toDouble()));
                        break;

                    default:
                        values.append(QJSValue(returnData.toString()));
                    }
                }
            }*/

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
class NoronRemoteCallList : public NoronRemoteCallBase{

};

NORON_END_NAMESPACE

#endif // NORONREMOTECALL_H
