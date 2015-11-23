#ifndef RPCSERIALIZERBASE_H
#define RPCSERIALIZERBASE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include <QVariant>

QT_BEGIN_NAMESPACE

class QByteArray;
class NoronSerializerBase : public QObject
{
    Q_OBJECT

public:
    explicit NoronSerializerBase(QObject *parent = 0);


    virtual QByteArray serialize(QVariant v) = 0;
    virtual QByteArray serialize(QVariantList list) = 0;
    virtual QByteArray serialize(QVariantMap map) = 0;

    virtual QVariant deserialize(QByteArray bytes) = 0;

};

QT_END_NAMESPACE

#endif // RPCSERIALIZERBASE_H
