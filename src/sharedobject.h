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

#ifndef NEURONSHAREDOBJECT_H
#define NEURONSHAREDOBJECT_H

#include <QtCore/QMutex>
#include <QtCore/QSet>

#define NEURON_SHARED_OBJECT
#include "syntax/syntax_sharedobject.h"
#include "abstracthub.h"
#include "peer.h"
#undef NEURON_SHARED_OBJECT

NEURON_BEGIN_NAMESPACE

//TODO: generate private class for me :-)
class NEURON_EXPORT SharedObject : public Peer
{
    Q_OBJECT

    AbstractHub *_activeHub;
    AbstractHub *_deactiveHub;
    bool _autoDelete;
    QMutex hubsLock;

public:
    SharedObject(QObject *parent = 0);
    SharedObject(AbstractHub *hub, QObject *parent = 0);

    void attachHub(AbstractHub *hub);
    void detachHub(AbstractHub *hub);
    bool setActiveHub(AbstractHub *hub);
    bool setAllHubsActiveExcept(AbstractHub *hub);

    QSet<AbstractHub*> hubs;

//    void setHub(AbstractHub* hub) /*Q_DECL_OVERRIDE*/;

    //BC
//    virtual const QString peerName() /*Q_DECL_OVERRIDE*/;
    virtual void hubAdded(AbstractHub *hub);
    virtual void hubRemoved(AbstractHub *hub);

    bool autoDelete() const;
    void setAutoDelete(bool autoDelete);

//private:
    QMap<QThread*, Peer*> senderPeers;
    void registerSender(QThread *t, Peer *peer);
    void unregisterSender(QThread *t);
    Peer *senderPeer() const;

private slots:
    void hub_statusChanged(AbstractHub::Status status);

protected:
    qlonglong invokeOnPeer(
            QString methodName,
            QVariant val0 = QVariant(),
            QVariant val1 = QVariant(),
            QVariant val2 = QVariant(),
            QVariant val3 = QVariant(),
            QVariant val4 = QVariant(),
            QVariant val5 = QVariant(),
            QVariant val6 = QVariant(),
            QVariant val7 = QVariant(),
            QVariant val8 = QVariant(),
            QVariant val9 = QVariant());

    void sync(AbstractHub *hub);
signals:
#ifdef NEURON_CLIENT
    void attached();
    void detached();
#endif

    friend class AbstractHub;
};

NEURON_END_NAMESPACE

#endif // NEURONSHAREDOBJECT_H
