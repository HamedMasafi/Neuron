#include "neuronsimpletokenvalidator.h"

#include <QCryptographicHash>

#define MAP_TOKEN_ITEM      "_token"

NeuronSimpleTokenValidator::NeuronSimpleTokenValidator(QObject *parent)
    : NeuronAbstractDataEncoder(parent), _validateToken(QString())
{

}

QString NeuronSimpleTokenValidator::validateToken() const
{
    return _validateToken;
}

void NeuronSimpleTokenValidator::setValidateToken(const QString &validateToken)
{
    _validateToken = validateToken;
}

void NeuronSimpleTokenValidator::encrypt(QVariantMap &map)
{
    map.insert(MAP_TOKEN_ITEM, QVariant(""));
    map.insert(MAP_TOKEN_ITEM, createValidateToken(map));
}

bool NeuronSimpleTokenValidator::decrypt(QVariantMap &map)
{
    QString token = map.value(MAP_TOKEN_ITEM).toString();
    map.insert(MAP_TOKEN_ITEM, QVariant(""));

    QString validateToken = createValidateToken(map);

    return token == validateToken;
}


QString NeuronSimpleTokenValidator::createValidateToken(QVariantMap &map)
{
    QString s = "";
    QMapIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();

        QMetaType t(i.value().userType());

        bool ok;
        if (t.flags() & QMetaType::PointerToQObject)
            s.append(i.key() + ": " + i.value().typeName() + "*");
        else if (t.flags() & QMetaType::IsEnumeration)
            s.append(i.key() + ": " + i.value().toInt(&ok) + "*");
        else
            s.append(i.key() + ": " + i.value().toString() + "*");
    }

    QString data = s + _validateToken;
    return QString(QCryptographicHash::hash(data.toLocal8Bit(),
                                    QCryptographicHash::Md5).toHex());
}
