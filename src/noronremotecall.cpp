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

NORON_BEGIN_NAMESPACE

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

    if(type == EventLoop){
        eventLoop->quit();
        eventLoop->deleteLater();
    }

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
        K_REG_OBJECT(eventLoop);
    }else{
        qFatal("Call me by an another constructor");
    }
}

#if __cplusplus >= 201103L
NoronRemoteCallBase::NoronRemoteCallBase(std::function<void ()> func) : type(Function), func(func)
{
}
#endif
#ifdef QT_QML_LIB
NoronRemoteCallBase::NoronRemoteCallBase(QJSValue jsvalue, QQmlEngine *qmlEngine, QJSEngine *engine) :
    type(JSValue), qmlEngine(qmlEngine), jsEngine(engine), jsvalue(jsvalue)
{
}


QJSValue NoronRemoteCallBase::toJsValue(QVariant var)
{
    qDebug() << "toJson" << var << var.type();
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
                return QJSValue(var.toString());
            }

        }
    }
}
QJSValue NoronRemoteCallBase::toJsValue(QVariantMap map)
{
    qDebug() << "decompiling map"<<map;
    QJSValue param1 = jsEngine->newObject();

    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        param1.setProperty(i.key(), toJsValue(i.value()));
    }

    return param1;
}
QJSValue NoronRemoteCallBase::toJsValue(QVariantList list)
{
    QJSValue param1 = jsEngine->newArray(list.length());

    int i = 0;
    foreach (QVariant var, list)
        param1.setProperty(i++, toJsValue(var));

    return param1;
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




NORON_END_NAMESPACE
