#include <QEvent>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaMethod>
#include <QTcpSocket>
#include <QEventLoop>
#include <QThread>

#include "noronserver.h"
#include "noronpeer.h"
#include "noronhubbase.h"

QT_BEGIN_NAMESPACE

NoronPeer::NoronPeer(QObject *parent) : QObject(parent), _hub(0)
{
    if(qobject_cast<NoronHub*>(parent)){
        setHub(qobject_cast<NoronHub*>(parent));
        hub()->addSharedObject(this);
    }
}


NoronPeer::~NoronPeer()
{

}
void NoronPeer::addCall(long id, NoronRemoteCallBase *call)
{
    hub()->_calls[id] = call;
}

void NoronPeer::removeCall(long id)
{
    hub()->_calls.remove(id);
}


void NoronPeer::connectToServer(QString address, qint16 port)
{
    if(!hub())
        setHub(new NoronHub(this));
    hub()->connectToServer(address, port);
}

qlonglong NoronPeer::invokeOnPeer(QString methodName,
                                QVariant val0,
                                QVariant val1,
                                QVariant val2,
                                QVariant val3,
                                QVariant val4,
                                QVariant val5,
                                QVariant val6,
                                QVariant val7,
                                QVariant val8,
                                QVariant val9)
{\
    return hub()->invokeOnPeer(
                metaObject()->className(),
                methodName,
                val0, val1, val2, val3, val4,
                val5, val6, val7, val8, val9);
}

/**
 * @brief NoronPeer::setHubdefine hub for this peer.
 *      If you don't create hub it will be created on first connect.
 * @param hub
 */
void NoronPeer::setHub(NoronHubBase *hub)
{
    if (_hub == hub)
        return;

    //TODO: check this.
    hub->addSharedObject(this);
    _hub = hub;
    emit hubChanged(hub);
}

/**
 * @brief NoronPeer::hub return this peer's hub
 * @return hub
 */
NoronHubBase *NoronPeer::hub() const
{
    return _hub;
}

QT_END_NAMESPACE
