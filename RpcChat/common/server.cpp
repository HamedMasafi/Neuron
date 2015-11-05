#include "server.h"
#include <QMetaObject>
#include <QMetaMethod>

Server::Server(QObject *parent) : RpcPeer(parent)
{

}


//-----------------------------------------
// Methods for property users
//-----------------------------------------

QStringList Server::users() const
{
    return m_users;
}

void Server::setUsers(QStringList users)
{
    if (m_users == users)
        return;

    m_users = users;
    invokeOnPeer("setUsers", users);
    emit usersChanged();
}


//-----------------------------------------
// Methods for broadcastMessage
//-----------------------------------------

void Server::broadcastMessageSlot(QString message)
{
    emit broadcastMessageHandle(message);
}

void Server::broadcastMessageAsync(QString message)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
}

void Server::broadcastMessage(QString message)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);

    if(id){
		RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
		call->eventLoop->exec();
        removeCall(id);
		delete call;
    }
}

#if __cplusplus >= 201103L
void Server::broadcastMessage(QString message, std::function<void()> func)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(func);
        addCall(id, call);
    }
}
#endif

void Server::broadcastMessage(QString message, const QObject *obj, char *slotName)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), slotName);
        addCall(id, call);
    }
}

void Server::broadcastMessage(QString message, const QObject *obj, const QMetaMethod *method)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);

    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj),
                                                  const_cast<QMetaMethod *>(method));
        addCall(id, call);
    }
}

//-----------------------------------------
// Methods for userJoined
//-----------------------------------------

void Server::userJoinedSlot(QString username)
{
    emit userJoinedHandle(username);
}

void Server::userJoinedAsync(QString username)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
}

void Server::userJoined(QString username)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);

    if(id){
		RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
		call->eventLoop->exec();
        removeCall(id);
		delete call;
    }
}

#if __cplusplus >= 201103L
void Server::userJoined(QString username, std::function<void()> func)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(func);
        addCall(id, call);
    }
}
#endif

void Server::userJoined(QString username, const QObject *obj, char *slotName)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), slotName);
        addCall(id, call);
    }
}

void Server::userJoined(QString username, const QObject *obj, const QMetaMethod *method)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);

    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj),
                                                  const_cast<QMetaMethod *>(method));
        addCall(id, call);
    }
}

//-----------------------------------------
// Methods for userLeaved
//-----------------------------------------

void Server::userLeavedSlot(QString username)
{
    emit userLeavedHandle(username);
}

void Server::userLeavedAsync(QString username)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
}

void Server::userLeaved(QString username)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);

    if(id){
		RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
		call->eventLoop->exec();
        removeCall(id);
		delete call;
    }
}

#if __cplusplus >= 201103L
void Server::userLeaved(QString username, std::function<void()> func)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(func);
        addCall(id, call);
    }
}
#endif

void Server::userLeaved(QString username, const QObject *obj, char *slotName)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), slotName);
        addCall(id, call);
    }
}

void Server::userLeaved(QString username, const QObject *obj, const QMetaMethod *method)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);

    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj),
                                                  const_cast<QMetaMethod *>(method));
        addCall(id, call);
    }
}

//-----------------------------------------
// Methods for imageSent
//-----------------------------------------

void Server::imageSentSlot(QString username, QPixmap image)
{
    emit imageSentHandle(username,image);
}

void Server::imageSentAsync(QString username, QPixmap image)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
}

void Server::imageSent(QString username, QPixmap image)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);

    if(id){
		RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
		call->eventLoop->exec();
        removeCall(id);
		delete call;
    }
}

#if __cplusplus >= 201103L
void Server::imageSent(QString username, QPixmap image, std::function<void()> func)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(func);
        addCall(id, call);
    }
}
#endif

void Server::imageSent(QString username, QPixmap image, const QObject *obj, char *slotName)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), slotName);
        addCall(id, call);
    }
}

void Server::imageSent(QString username, QPixmap image, const QObject *obj, const QMetaMethod *method)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);

    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj),
                                                  const_cast<QMetaMethod *>(method));
        addCall(id, call);
    }
}
