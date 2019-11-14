/**************************************************************************
**
** This file is part of .
** https://github.com/HamedMasafi/
**
**  is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
**  is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with .  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#include <QtCore/QBuffer>
#include <QtCore/QCryptographicHash>
#include <QtCore/QDataStream>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QMetaMethod>
#include <QtCore/QVariant>
#include <QtCore/QList>

#include "peer.h"
#include "jsonbinaryserializer.h"

#define VARIANT_TYPE "_type"
#define VARIANT_VALUE "_value"
#define CLASS_NAME(x) QString(#x)
#define MAP_TOKEN_ITEM      "_token"

NEURON_BEGIN_NAMESPACE

JsonBinarySerializer::JsonBinarySerializer(QObject *parent) : AbstractSerializer(parent)
{ }

QByteArray JsonBinarySerializer::serialize(QVariant v, bool *ok)
{
    Q_UNUSED(ok);

    QJsonValue val = toJson(v);
    QJsonDocument doc;

    doc.setObject(val.toObject());

    return doc.toJson(QJsonDocument::Compact) + "\n";
}

QByteArray JsonBinarySerializer::serialize(QVariantList list)
{
    QJsonValue val = toJson(list);
    QJsonDocument doc;

    doc.setObject(val.toObject());

    return doc.toJson(QJsonDocument::Compact) + "\n";
}

QByteArray JsonBinarySerializer::serialize(QVariantMap map)
{
    QJsonValue val = toJson(map);
    QJsonDocument doc;

    doc.setObject(val.toObject());

    return doc.toJson(QJsonDocument::Compact) + "\n";
}

QVariant JsonBinarySerializer::deserialize(QByteArray bytes, bool *ok)
{
    Q_UNUSED(ok);

    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    if(doc.isArray())
        return fromJson(QJsonDocument::fromJson(bytes).array());
    if(doc.isObject())
        return fromJson(QJsonDocument::fromJson(bytes).object());

    qWarning("Input string is not valid serialized json");
    qWarning(bytes);
    return QVariant();
}

QVariantMap JsonBinarySerializer::serializeQObject(QObject *obj)
{
    QVariantMap map;

    if (obj)
        for(int i = 0; i < obj->metaObject()->propertyCount(); i++){
            QMetaProperty property = obj->metaObject()->property(i);
            if(property.isReadable() && property.isWritable())
                map.insert(property.name(), property.read(obj).toString());
        }

    return map;
}

void JsonBinarySerializer::deserializeQObject(QObject *obj, QVariantMap map)
{
    for(int i = 0; i < obj->metaObject()->propertyCount(); i++){
        QMetaProperty property = obj->metaObject()->property(i);
        if(property.isReadable() && property.isWritable())
            property.write(obj, map[property.name()].toString());
    }
}

QString JsonBinarySerializer::validateToken() const
{
    return m_validateToken;
}

void JsonBinarySerializer::setValidateToken(QString validateToken)
{
    if (m_validateToken == validateToken)
        return;

    m_validateToken = validateToken;
    emit validateTokenChanged(m_validateToken);
}

QString JsonBinarySerializer::createValidateToken(QVariantMap &map)
{
    QString s = "";
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();

        QMetaType t(i.value().userType());

        if (t.flags() & QMetaType::PointerToQObject)
            s.append(i.key() + ": " + i.value().typeName() + "*");
        else if (t.flags() & QMetaType::IsEnumeration)
            s.append(i.key() + ": " + QString::number(i.value().toInt()) + "*");
        else
            s.append(i.key() + ": " + i.value().toString() + "*");
    }

    QString data = s + m_validateToken;
    return QString(QCryptographicHash::hash(data.toLocal8Bit(),
                                    QCryptographicHash::Md5).toHex());
}

QJsonObject JsonBinarySerializer::toJson(QVariant v)
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

    QJsonObject o;

    QString typeName = QString(v.typeName());
    if(typeName.endsWith("*")){
        //TODO: remove this line
        //issue #1: Can't build with Qt 5.5 and Qt 5.6
//        if(v.value<QObject*>()->metaObject()->inherits(&Peer::staticMetaObject))
        if(v.value<QObject*>()->inherits("Peer"))
            o.insert(VARIANT_TYPE, QString(v.value<Peer*>()->peerName())+ "*");
        else
            o.insert(VARIANT_TYPE, QString(v.value<QObject*>()->metaObject()->className()) + "*");
        o.insert(VARIANT_VALUE, toJson(serializeQObject(qvariant_cast<QObject*>(v))));
    }else{
        if(typeName.startsWith("QList<"))
            return toJson(v.value<QVariantList>());

        QByteArray data;
        QDataStream ds(&data, QIODevice::WriteOnly);
        ds << v;
        o.insert(VARIANT_TYPE, v.typeName());
        o.insert(VARIANT_VALUE, QString(data.toBase64()));
    }
    return o;
}

QJsonObject JsonBinarySerializer::toJson(QVariantList list)
{
    if(!list.count())
        qWarning("Count = 0");

    QJsonArray array;
    foreach (QVariant v, list) {
        array.append(toJson(v));
    }

    QJsonObject o;
    o.insert(VARIANT_TYPE, CLASS_NAME(QVariantList));
    o.insert(VARIANT_VALUE, array);
    return o;
}

QJsonObject JsonBinarySerializer::toJson(QStringList list)
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

QJsonObject JsonBinarySerializer::toJson(QVariantMap map)
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

QVariant JsonBinarySerializer::fromJson(QJsonObject object)
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

//    if(QMetaType::type(typeName.toLatin1().data())> 1024){
    if(typeName.endsWith("*")){
        QObject *obj;
        QVariantMap map;
        QJsonObject mapObject = object[VARIANT_VALUE].toObject().value(VARIANT_VALUE).toObject();

        foreach (QString key, mapObject.keys())
            map.insert(key, fromJson(mapObject[key].toObject()));
        int typeCode = QMetaType::type(typeName.toLatin1().data());

        if(typeCode == QMetaType::UnknownType){
            qWarning("Type %s is not registered!", qPrintable(typeName));
            return QVariant(QVariant::Invalid);
        }

        const QMetaObject *metaObject = QMetaType::metaObjectForType(typeCode);
        obj = metaObject->newInstance();
        K_REG_OBJECT(obj);

        if(!obj){
            qWarning("Object type %s can not deserialized", qPrintable(object[VARIANT_TYPE].toString()));
            return QVariant();
        }

        deserializeQObject(obj, map);


        QVariant ret = QVariant::fromValue(obj);
        ret.convert(typeCode);
        return ret;
    }

    QVariant v;
    QByteArray data = QByteArray::fromBase64(object[VARIANT_VALUE].toString().toLocal8Bit());
    QDataStream ds(&data,QIODevice::ReadOnly);
    ds >> v;
    return v;
}

QVariant JsonBinarySerializer::fromJson(QJsonArray array)
{
    QVariantList list;
    foreach (QJsonValue value, array)
        list.append(fromJson(value.toObject()));
    return list;
}

NEURON_END_NAMESPACE
