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

#ifndef NEURONABSTRACTDATAENCODER_H
#define NEURONABSTRACTDATAENCODER_H

#include "global.h"
#include <QObject>
#include <QVariantMap>

NEURON_BEGIN_NAMESPACE

class AbstractDataEncoder : public QObject
{
    Q_OBJECT
public:
    AbstractDataEncoder(QObject *parent = Q_NULLPTR);

    virtual void encrypt(QVariantMap &map) = 0;
    virtual bool decrypt(QVariantMap &map) = 0;
};

NEURON_END_NAMESPACE

#endif // NEURONABSTRACTDATAENCODER_H
