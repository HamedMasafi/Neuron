#ifndef ABSTRACTCALL_H
#define ABSTRACTCALL_H

#include "global.h"
#include <QEventLoop>
#include <QObject>
#include <QVariant>
#include <functional>
#ifdef QT_QML_LIB
#   include <QtQml/QJSEngine>
#   include <QtQml/QQmlEngine>
#   include <QtQml/QJSValue>
#endif

NEURON_BEGIN_NAMESPACE

class AbstractCall //: public QObject
{
    Q_GADGET
    QEventLoop *eventLoop;

public:
    explicit AbstractCall(QObject *parent = nullptr);

    void wait();
    void finish();
protected:
    QVariant value;
    virtual void returnToCaller() = 0;
#ifdef QT_QML_LIB
    QQmlEngine *qmlEngine;
    QJSEngine *jsEngine;
    QJSValue jsvalue;

    QJSValue toJsValue(QVariant v);
    QJSValue toJsValue(QVariantMap map);
    QJSValue toJsValue(QVariantList list);
#endif

    friend class AbstractHubPrivate;
};



NEURON_END_NAMESPACE

#endif // ABSTRACTCALL_H
