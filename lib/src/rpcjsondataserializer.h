#ifndef RPCJSONDATASERIALIZER_H
#define RPCJSONDATASERIALIZER_H

#include "rpcglobal.h"
#include "rpcserializerbase_p.h"

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class TOOJ_EXPORT RpcJsonDataSerializer : public RpcSerializerBase
{
    Q_OBJECT
public:
    explicit RpcJsonDataSerializer(QObject *parent = 0);

    QByteArray serialize(QVariant v);
    QByteArray serialize(QVariantList list);
    QByteArray serialize(QVariantMap map);

    QVariant deserialize(QByteArray bytes);

    QJsonObject toJson(QVariant v);
    QJsonObject toJson(QVariantList list);
    QJsonObject toJson(QStringList list);
    QJsonObject toJson(QVariantMap map);

    QVariant fromJson(QJsonObject object);
    QVariant fromJson(QJsonArray array);

    QJsonObject serializeQObject(QObject *obj);
    void deserializeQObject(QObject *obj, QJsonObject jsonObject);
public slots:
};

#endif // RPCJSONDATASERIALIZER_H
