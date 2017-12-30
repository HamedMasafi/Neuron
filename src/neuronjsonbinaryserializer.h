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

#ifndef NEURONJSONBINARYSERIALIZER_H
#define NEURONJSONBINARYSERIALIZER_H

#include "neuronglobal.h"
#include "neuronabstractserializer.h"

#include <QtCore/QObject>

NEURON_BEGIN_NAMESPACE

class NEURON_EXPORT NeuronJsonBinarySerializer : public NeuronAbstractSerializer
{
    Q_OBJECT
public:
    explicit NeuronJsonBinarySerializer(QObject *parent = 0);

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

NEURON_END_NAMESPACE

#endif // NEURONJSONBINARYSERIALIZER_H
