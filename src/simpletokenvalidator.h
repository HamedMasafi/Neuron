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

#ifndef NEURONSIMPLETOKENVALIDATOR_H
#define NEURONSIMPLETOKENVALIDATOR_H

#include "abstractdataencoder.h"

NEURON_BEGIN_NAMESPACE

class NEURON_EXPORT SimpleTokenValidator : public AbstractDataEncoder
{
    Q_OBJECT

    QString _validateToken;
public:
    SimpleTokenValidator(QObject *parent = nullptr);
    SimpleTokenValidator(const QString &token, QObject *parent = nullptr);

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
