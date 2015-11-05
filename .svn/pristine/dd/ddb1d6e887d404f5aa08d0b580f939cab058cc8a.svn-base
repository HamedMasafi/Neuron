#ifndef RPCSERIALIZERBASE_H
#define RPCSERIALIZERBASE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include <QVariant>

class QByteArray;
class RpcSerializerBase : public QObject
{
    Q_OBJECT

public:
    explicit RpcSerializerBase(QObject *parent = 0);


    virtual QByteArray serialize(QVariant v) = 0;
    virtual QByteArray serialize(QVariantList list) = 0;
    virtual QByteArray serialize(QVariantMap map) = 0;

    virtual QVariant deserialize(QByteArray bytes) = 0;

};

#endif // RPCSERIALIZERBASE_H
