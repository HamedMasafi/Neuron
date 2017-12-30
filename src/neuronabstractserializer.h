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

#ifndef NEURONABSTRACTSERIALIZER_H
#define NEURONABSTRACTSERIALIZER_H

#include <QtCore/QObject>
#include "neuronglobal.h"

NEURON_BEGIN_NAMESPACE

class NeuronAbstractSerializer : public QObject
{
    Q_OBJECT
public:
    explicit NeuronAbstractSerializer(QObject *parent = 0);

    virtual QByteArray serialize(QVariant v) = 0;
    virtual QByteArray serialize(QVariantList list) = 0;
    virtual QByteArray serialize(QVariantMap map) = 0;

    virtual QVariant deserialize(QByteArray bytes) = 0;
signals:

public slots:
};

NEURON_END_NAMESPACE

#endif // NEURONABSTRACTSERIALIZER_H
