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

#ifndef NEURONJSONBINARYSERIALIZER_H
#define NEURONJSONBINARYSERIALIZER_H

#include "global.h"
#include "abstractserializer.h"

#include <QtCore/QObject>

NEURON_BEGIN_NAMESPACE

class NEURON_EXPORT JsonBinarySerializer : public AbstractSerializer
{
    Q_OBJECT
    Q_PROPERTY(QString validateToken READ validateToken WRITE setValidateToken NOTIFY validateTokenChanged)

    QString m_validateToken;

public:
    explicit JsonBinarySerializer(QObject *parent = nullptr);

    QByteArray serialize(QVariant v, bool *ok = nullptr) override;
    QByteArray serialize(QVariantList list);
    QByteArray serialize(QVariantMap map);

    QVariant deserialize(QByteArray bytes, bool *ok = nullptr) override;

    QJsonObject toJson(QVariant v);
    QJsonObject toJson(QVariantList list);
    QJsonObject toJson(QStringList list);
    QJsonObject toJson(QVariantMap map);

    QVariant fromJson(QJsonObject object);
    QVariant fromJson(QJsonArray array);

    QVariantMap serializeQObject(QObject *obj);
    void deserializeQObject(QObject *obj, QVariantMap jsonObject);
    QString validateToken() const;

public slots:
    void setValidateToken(QString validateToken);

signals:
    void validateTokenChanged(QString validateToken);

private:
    QString createValidateToken(QVariantMap &map);
};

NEURON_END_NAMESPACE

#endif // NEURONJSONBINARYSERIALIZER_H
