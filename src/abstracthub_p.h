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

#ifndef NEURONABSTRACTHUB_P_H
#define NEURONABSTRACTHUB_P_H

#include <QtCore/QSet>

#include <QMutex>
#include <cstdint>

#include "abstracthub.h"
#include "abstractdataencoder.h"

#define ID                  "_id"
#define CLASS_NAME          "_c"
#define METHOD_NAME         "_m"
#define MAP_TYPE            "_t"
#define MAP_RETURN_VALUE    "_return_value"
#define MAP_TYPE_REQUEST    "request"
#define MAP_TYPE_RESPONSE   "response"
#define MAP_TOKEN_ITEM      "_token"

class QTcpSocket;
class QJSEngine;
class QQmlEngine;

NEURON_BEGIN_NAMESPACE

class AbstractHubPrivate{
    AbstractHub *q_ptr;
    Q_DECLARE_PUBLIC(AbstractHub)

public:
    AbstractHubPrivate(AbstractHub *parent);

    QSet<QString> locks;
    QVariantList buffer;
    QByteArray readBuffer;
    QHash<const QString, SharedObject*> sharedObjects;
    QMutex socketReadMutex;

    Peer* peer;
    AbstractSerializer* serializer;
    AbstractDataEncoder *encoder;
    qlonglong requestId;
    bool isTransaction;
    bool isMultiThread;
    qlonglong hubId;
    AbstractHub::Status status;

#ifdef QT_QML_LIB
    QJSEngine *jsEngine;
    QQmlEngine *qmlEngine;
#endif

    void addToMap(QVariantMap *map, QVariant var, int index);
    void procMap(QVariantList list);
    void procMap(QVariantMap map);
    bool response(const qlonglong &id, const QString &senderName, const QVariant &returnValue);
    QString MD5(const QString &text);
    QString MD5(QByteArray text);
    void sync();
};

NEURON_END_NAMESPACE

#endif // NEURONABSTRACTHUB_P_H
