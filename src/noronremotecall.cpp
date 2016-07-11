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
NoronRemoteCallBase::NoronRemoteCallBase(QJSValue jsvalue, QQmlEngine *qmlEngine, QJSEngine *engine) :
    type(JSValue), qmlEngine(qmlEngine), jsEngine(engine), jsvalue(jsvalue)
{
//    this->type = JSValue;
//    this->jsEngine = engine;
//    this->qmlEngine = qmlEngine;
//    this->jsvalue = jsvalue;
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
