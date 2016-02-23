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

#include <QtCore/QBuffer>
#include <QtCore/QDataStream>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QMetaMethod>
#include <QtCore/QVariant>

#include "noronjsonbinaryserializer.h"

#define VARIANT_TYPE "_type"
#define VARIANT_VALUE "_value"
#define CLASS_NAME(x) QString(#x)

QT_BEGIN_NAMESPACE

NoronJsonBinarySerializer::NoronJsonBinarySerializer(QObject *parent) : NoronAbstractSerializer(parent)
{

}

QByteArray NoronJsonBinarySerializer::serialize(QVariant v)
{
    QJsonValue val = toJson(v);
    QJsonDocument doc;

    doc.setObject(val.toObject());

    return doc.toJson();
}

QByteArray NoronJsonBinarySerializer::serialize(QVariantList list)
{
    QJsonValue val = toJson(list);
    QJsonDocument doc;

    doc.setObject(val.toObject());

    return doc.toJson();
}

QByteArray NoronJsonBinarySerializer::serialize(QVariantMap map)
{
    QJsonValue val = toJson(map);
    QJsonDocument doc;

    doc.setObject(val.toObject());

    return doc.toJson();
}

QVariant NoronJsonBinarySerializer::deserialize(QByteArray bytes)
{
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    if(doc.isArray())
        return fromJson(QJsonDocument::fromJson(bytes).array());
    if(doc.isObject())
        return fromJson(QJsonDocument::fromJson(bytes).object());

    qWarning("Input string is not valid serialized json");
    qWarning(bytes);
    return QVariant();
}

QVariantMap NoronJsonBinarySerializer::serializeQObject(QObject *obj)
{
    QVariantMap map;

    for(int i = 0; i < obj->metaObject()->propertyCount(); i++){
        QMetaProperty property = obj->metaObject()->property(i);
        if(property.isReadable() && property.isWritable())
            map.insert(property.name(), property.read(obj).toString());
    }

    return map;
}

void NoronJsonBinarySerializer::deserializeQObject(QObject *obj, QVariantMap map)
{
    for(int i = 0; i < obj->metaObject()->propertyCount(); i++){
        QMetaProperty property = obj->metaObject()->property(i);
        if(property.isReadable() && property.isWritable())
            property.write(obj, map[property.name()].toString());
    }
}

QJsonObject NoronJsonBinarySerializer::toJson(QVariant v)
{
    switch(v.type()){
    case QVariant::Map:
        return toJson(v.toMap());
    case QVariant::StringList:
        return toJson(v.toStringList());
    case QVariant::List:
        return toJson(v.toList());

    case QVariant::Invalid:
        qWarning("QVariant type is Invalid!");
        break;
    default:
        // disable compiler warning
        break;
    }

    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << v;
    QJsonObject o;
    o.insert(VARIANT_TYPE, v.typeName());
    o.insert(VARIANT_VALUE, QString(data.toBase64()));
    return o;
}

QJsonObject NoronJsonBinarySerializer::toJson(QVariantList list)
{
    QJsonArray array;
    foreach (QVariant v, list) {
        array.append(toJson(v));
    }

    QJsonObject o;
    o.insert(VARIANT_TYPE, CLASS_NAME(QVariantList));
    o.insert(VARIANT_VALUE, array);
    return o;
}

QJsonObject NoronJsonBinarySerializer::toJson(QStringList list)
{
    QJsonArray array;
    foreach (QVariant v, list) {
        array.append(toJson(v));
    }

    QJsonObject o;
    o.insert(VARIANT_TYPE, CLASS_NAME(QStringList));
    o.insert(VARIANT_VALUE, array);
    return o;
}

QJsonObject NoronJsonBinarySerializer::toJson(QVariantMap map)
{
    QJsonObject mapObject;
    foreach (QString key, map.keys()) {
        mapObject.insert(key, toJson(map[key]));
    }

    QJsonObject o;
    o.insert(VARIANT_TYPE, CLASS_NAME(QVariantMap));
    o.insert(VARIANT_VALUE, mapObject);
    return o;
}

QVariant NoronJsonBinarySerializer::fromJson(QJsonObject object)
{
    QString typeName = object[VARIANT_TYPE].toString();
    QVariant::Type type = QVariant::nameToType(typeName.toLatin1().data());

    if(type == QVariant::List)
        return fromJson(object[VARIANT_VALUE].toArray()).toList();

    if(type == QVariant::StringList)
        return fromJson(object[VARIANT_VALUE].toArray()).toStringList();

    if(type == QVariant::Map){
        QVariantMap map;
        QJsonObject mapObject = object[VARIANT_VALUE].toObject();
        foreach (QString key, mapObject.keys())
            map.insert(key, fromJson(mapObject[key].toObject()));
        return map;
    }

    QVariant v;
    QByteArray data = QByteArray::fromBase64(object[VARIANT_VALUE].toString().toLocal8Bit());
    QDataStream ds(&data,QIODevice::ReadOnly);
    ds >> v;
    return v;
}

QVariant NoronJsonBinarySerializer::fromJson(QJsonArray array)
{
    QVariantList list;
    foreach (QJsonValue value, array)
        list.append(fromJson(value.toObject()));
    return list;
}

QT_END_NAMESPACE
