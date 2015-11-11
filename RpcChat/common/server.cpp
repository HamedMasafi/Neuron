#include "server.h"

#include <QMetaObject>
#include <QMetaMethod>

QT_BEGIN_NAMESPACE

Server::Server(QObject *parent) : RpcPeer(parent)
{

}

#ifdef QT_QML_LIB
void Server::broadcastMessage(QString message, QJSValue callbackFunction)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

#ifdef __cplusplus >= 201103L
void Server::broadcastMessage(QString message, std::function<void(void)> callbackFunction)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

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

void Server::broadcastMessage(QString message, const QObject *obj, char *callbackSlot)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), callbackSlot);
        addCall(id, call);
    }
    
}

void Server::broadcastMessage(QString message, const QObject *obj, const QMetaMethod *callbackMethod)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);
    
    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod));
        addCall(id, call);
    }
    
}

void Server::broadcastMessageAsync(QString message)
{
    qlonglong id = invokeOnPeer("broadcastMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
    
}

void Server::broadcastMessageSlot(QString message)
{
    emit broadcastMessageSignal(message);
    
}

void Server::imageSent(QString username, QPixmap image, const QObject *obj, const QMetaMethod *callbackMethod)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);
    
    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod));
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

#ifdef QT_QML_LIB
void Server::imageSent(QString username, QPixmap image, QJSValue callbackFunction)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void Server::imageSent(QString username, QPixmap image, const QObject *obj, char *callbackSlot)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), callbackSlot);
        addCall(id, call);
    }
    
}

#ifdef __cplusplus >= 201103L
void Server::imageSent(QString username, QPixmap image, std::function<void(void)> callbackFunction)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void Server::imageSentAsync(QString username, QPixmap image)
{
    qlonglong id = invokeOnPeer("imageSentSlot", username,image);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
    
}

void Server::imageSentSlot(QString username, QPixmap image)
{
    emit imageSentSignal(username,image);
    
}

#ifdef __cplusplus >= 201103L
void Server::userJoined(QString username, std::function<void(void)> callbackFunction)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void Server::userJoined(QString username, const QObject *obj, char *callbackSlot)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), callbackSlot);
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

void Server::userJoined(QString username, const QObject *obj, const QMetaMethod *callbackMethod)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);
    
    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod));
        addCall(id, call);
    }
    
}

#ifdef QT_QML_LIB
void Server::userJoined(QString username, QJSValue callbackFunction)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void Server::userJoinedAsync(QString username)
{
    qlonglong id = invokeOnPeer("userJoinedSlot", username);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
    
}

void Server::userJoinedSlot(QString username)
{
    emit userJoinedSignal(username);
    
}

#ifdef QT_QML_LIB
void Server::userLeaved(QString username, QJSValue callbackFunction)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void Server::userLeaved(QString username, const QObject *obj, const QMetaMethod *callbackMethod)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);
    
    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod));
        addCall(id, call);
    }
    
}

#ifdef __cplusplus >= 201103L
void Server::userLeaved(QString username, std::function<void(void)> callbackFunction)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

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

void Server::userLeaved(QString username, const QObject *obj, char *callbackSlot)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), callbackSlot);
        addCall(id, call);
    }
    
}

void Server::userLeavedAsync(QString username)
{
    qlonglong id = invokeOnPeer("userLeavedSlot", username);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
    
}

void Server::userLeavedSlot(QString username)
{
    emit userLeavedSignal(username);
    
}

QStringList Server::users()
{
    return m_users;
    
}

void Server::setUsers(QStringList users)
{
    if (m_users == users)
        return;
    
    m_users = users;
    emit usersChanged(users);
    
}


QT_END_NAMESPACE
