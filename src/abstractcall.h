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

class AbstractCall : public QObject
{
    Q_OBJECT
    QEventLoop *eventLoop;

public:
    explicit AbstractCall(QObject *parent = nullptr);

    void wait();
    void finish();
protected:
    QVariant value;
    virtual void returnToCaller()
    {}

#ifdef QT_QML_LIB
    QQmlEngine *qmlEngine;
    QJSEngine *jsEngine;
    QJSValue jsvalue;

    QJSValue toJsValue(QVariant v);
    QJSValue toJsValue(QVariantMap map);
    QJSValue toJsValue(QVariantList list);
public slots:
    Neuron::AbstractCall *then(QJSValue callback)
    {
        jsvalue = callback;
        return this;
    }
#endif

    friend class AbstractHubPrivate;
};

NEURON_END_NAMESPACE

Q_DECLARE_METATYPE(Neuron::AbstractCall*)

#endif // ABSTRACTCALL_H
