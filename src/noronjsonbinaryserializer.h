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

#ifndef NORONJSONBINARYSERIALIZER_H
#define NORONJSONBINARYSERIALIZER_H

#include "noronglobal.h"
#include "noronabstractserializer.h"

#include <QtCore/QObject>

QT_BEGIN_NAMESPACE

class NORON_EXPORT NoronJsonBinarySerializer : public NoronAbstractSerializer
{
    Q_OBJECT
public:
    explicit NoronJsonBinarySerializer(QObject *parent = 0);

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

#endif // NORONJSONBINARYSERIALIZER_H
