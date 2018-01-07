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

#ifndef NEURONSIMPLETOKENVALIDATOR_H
#define NEURONSIMPLETOKENVALIDATOR_H

#include "neuronabstractdataencoder.h"

NEURON_BEGIN_NAMESPACE

class NeuronSimpleTokenValidator : public NeuronAbstractDataEncoder
{
    Q_OBJECT

    QString _validateToken;
public:
    NeuronSimpleTokenValidator(QObject *parent = Q_NULLPTR);

public:
    void encrypt(QVariantMap &map);
    bool decrypt(QVariantMap &map);

    QString validateToken() const;
    void setValidateToken(const QString &validateToken);

private:
    QString createValidateToken(QVariantMap &map);
};

NEURON_END_NAMESPACE

#endif // NEURONSIMPLETOKENVALIDATOR_H
