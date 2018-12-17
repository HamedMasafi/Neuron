#include "abstractcall.h"

NEURON_BEGIN_NAMESPACE

AbstractCall::AbstractCall(QObject *parent)// : QObject(parent)
  : eventLoop(nullptr)
{

}

void AbstractCall::wait()
{
    eventLoop = new QEventLoop;
    eventLoop->exec();
}

void AbstractCall::finish()
{
    returnToCaller();

    if (eventLoop != nullptr) {
        eventLoop->quit();
        eventLoop->deleteLater();
    }
}

#ifdef QT_QML_LIB

QJSValue AbstractCall::toJsValue(QVariant var)
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
QJSValue AbstractCall::toJsValue(QVariantMap map)
{
    QJSValue param1 = jsEngine->newObject();

    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        param1.setProperty(i.key(), toJsValue(i.value()));
    }

    return param1;
}
QJSValue AbstractCall::toJsValue(QVariantList list)
{
    QJSValue param1 = jsEngine->newArray(list.length());

    int i = 0;
    foreach (QVariant var, list)
        param1.setProperty(i++, toJsValue(var));

    return param1;
}

#endif

NEURON_END_NAMESPACE
