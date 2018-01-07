/**************************************************************************
**
** This file is part of Neuron.
** https://github.com/HamedMasafi/Neuron
**
** Neuron is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Neuron is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Neuron.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#include "neuronsimpletokenvalidator.h"

#include <QCryptographicHash>

#define MAP_TOKEN_ITEM      "_token"

NEURON_BEGIN_NAMESPACE

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

NEURON_END_NAMESPACE
