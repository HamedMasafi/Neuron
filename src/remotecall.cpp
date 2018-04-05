/**************************************************************************
**
** This file is part of .
** https://github.com/HamedMasafi/
**
**  is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
**  is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with .  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#include "remotecall_p.h"

NEURON_BEGIN_NAMESPACE

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

    if(type == EventLoop){
        eventLoop->quit();
        eventLoop->deleteLater();
    }

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
        K_REG_OBJECT(eventLoop);
    }else{
        qFatal("Call me by an another constructor");
    }
}

#if __cplusplus >= 201103L
RemoteCallBase::RemoteCallBase(std::function<void ()> func) : type(Function), func(func)
{
}
#endif
#ifdef QT_QML_LIB
RemoteCallBase::RemoteCallBase(QJSValue jsvalue, QQmlEngine *qmlEngine, QJSEngine *engine) :
    type(JSValue), qmlEngine(qmlEngine), jsEngine(engine), jsvalue(jsvalue)
{
}


QJSValue RemoteCallBase::toJsValue(QVariant var)
{
    if (var.type() == QVariant::List) {
       return toJsValue(var.toList());
    } else if (var.type() == QVariant::Map) {
       return toJsValue(var.toMap());
    } else {
        if(QString(var.typeName()).endsWith("*")){
            QObject *o = var.value<QObject*>();
            if(!o)
                qWarning("Object is not valid");
            qmlEngine->setObjectOwnership(o, QQmlEngine::JavaScriptOwnership);
            return jsEngine->newQObject(o);
        }else{
            switch(var.type()){
            case QVariant::Int:
                return QJSValue(var.toInt());

            case QVariant::Bool:
                return QJSValue(var.toBool());

            case QVariant::UInt:
                return QJSValue(var.toUInt());

            case QVariant::Double:
                return QJSValue(var.toDouble());

            default:
                return jsEngine->toScriptValue(var);

//                return QJSValue(var.toString());
            }

        }
    }
}
QJSValue RemoteCallBase::toJsValue(QVariantMap map)
{
    QJSValue param1 = jsEngine->newObject();

    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        param1.setProperty(i.key(), toJsValue(i.value()));
    }

    return param1;
}
QJSValue RemoteCallBase::toJsValue(QVariantList list)
{
    QJSValue param1 = jsEngine->newArray(list.length());

    int i = 0;
    foreach (QVariant var, list)
        param1.setProperty(i++, toJsValue(var));

    return param1;
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




NEURON_END_NAMESPACE
