#include <QEvent>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaMethod>
#include <QTcpSocket>
#include <QEventLoop>
#include <QThread>

#include "rpcserver.h"
#include "rpcpeer.h"
#include "rpchubbase.h"

RpcPeer::RpcPeer(QObject *parent) : QObject(parent), _hub(0)
{
    if(qobject_cast<RpcHub*>(parent)){
        setHub(qobject_cast<RpcHub*>(parent));
        hub()->addSharedObject(this);
    }
}


RpcPeer::~RpcPeer()
{

}
void RpcPeer::addCall(long id, RemoteCallBase *call)
{
    hub()->_calls[id] = call;
}

void RpcPeer::removeCall(long id)
{
    hub()->_calls.remove(id);
}


void RpcPeer::connectToServer(QString address, qint16 port)
{
    if(!hub())
        setHub(new RpcHub(this));
    hub()->connectToServer(address, port);
}

qlonglong RpcPeer::invokeOnPeer(QString methodName,
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
 * @brief RpcPeer::setHubdefine hub for this peer.
 *      If you don't create hub it will be created on first connect.
 * @param hub
 */
void RpcPeer::setHub(RpcHubBase *hub)
{
    if (_hub == hub)
        return;

    //TODO: check this. I this this is correct
    hub->addSharedObject(this);
    _hub = hub;
    emit hubChanged(hub);
}

/**
 * @brief RpcPeer::hub return this peer's hub
 * @return hub
 */
RpcHubBase *RpcPeer::hub() const
{
    return _hub;
}
