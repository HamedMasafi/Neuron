#ifndef RPCJSONDATASERIALIZER_H
#define RPCJSONDATASERIALIZER_H

#include "noronglobal.h"
#include "noronserializerbase_p.h"

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

QT_BEGIN_NAMESPACE

class TOOJ_EXPORT NoronJsonDataSerializer : public NoronSerializerBase
{
    Q_OBJECT
public:
    explicit NoronJsonDataSerializer(QObject *parent = 0);

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

    QVariantMap serializeQObject(QObject *obj);
    void deserializeQObject(QObject *obj, QVariantMap jsonObject);
public slots:
};

QT_END_NAMESPACE

#endif // RPCJSONDATASERIALIZER_H
