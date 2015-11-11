#ifndef %3_H
#define %3_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#if __cplusplus >= 201103L
#   include <functional>
#endif

#ifdef QT_QML_LIB
#   include <QJSValue>
#endif

#include <ToojRpc>
%4

QT_BEGIN_NAMESPACE

class %1 : public ToojRpc
{
    Q_OBJECT

public:
    Q_INVOKABLE %1(QObject *parent = 0);
%2
};

QT_END_NAMESPACE

#endif // %3_H
