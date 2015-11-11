#include "user.h"

#include <QMetaObject>
#include <QMetaMethod>

QT_BEGIN_NAMESPACE

User::User(QObject *parent) : RpcPeer(parent)
{

}

QPixmap User::avator()
{
    return m_avator;
    
}

void User::messageRecived(QString username, QString message)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);
    
    if(id){
    	RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
    	addCall(id, call);
    	call->eventLoop->exec();
    	removeCall(id);
    	delete call;
    }
}

#ifdef QT_QML_LIB
void User::messageRecived(QString username, QString message, QJSValue callbackFunction)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void User::messageRecived(QString username, QString message, const QObject *obj, const QMetaMethod *callbackMethod)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);
    
    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod));
        addCall(id, call);
    }
    
}

#ifdef __cplusplus >= 201103L
void User::messageRecived(QString username, QString message, std::function<void(void)> callbackFunction)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void User::messageRecived(QString username, QString message, const QObject *obj, char *callbackSlot)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), callbackSlot);
        addCall(id, call);
    }
    
}

void User::messageRecivedAsync(QString username, QString message)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
    
}

void User::messageRecivedSlot(QString username, QString message)
{
    emit messageRecivedSignal(username,message);
    
}

#ifdef QT_QML_LIB
void User::roomMessage(QString message, QJSValue callbackFunction)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void User::roomMessage(QString message, const QObject *obj, char *callbackSlot)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), callbackSlot);
        addCall(id, call);
    }
    
}

void User::roomMessage(QString message)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);
    
    if(id){
    	RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
    	addCall(id, call);
    	call->eventLoop->exec();
    	removeCall(id);
    	delete call;
    }
}

#ifdef __cplusplus >= 201103L
void User::roomMessage(QString message, std::function<void(void)> callbackFunction)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void User::roomMessage(QString message, const QObject *obj, const QMetaMethod *callbackMethod)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);
    
    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod));
        addCall(id, call);
    }
    
}

void User::roomMessageAsync(QString message)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
    
}

void User::roomMessageSlot(QString message)
{
    emit roomMessageSignal(message);
    
}

void User::sendImage(QPixmap image)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);
    
    if(id){
    	RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
    	addCall(id, call);
    	call->eventLoop->exec();
    	removeCall(id);
    	delete call;
    }
}

void User::sendImage(QPixmap image, const QObject *obj, const QMetaMethod *callbackMethod)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);
    
    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod));
        addCall(id, call);
    }
    
}

#ifdef __cplusplus >= 201103L
void User::sendImage(QPixmap image, std::function<void(void)> callbackFunction)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void User::sendImage(QPixmap image, const QObject *obj, char *callbackSlot)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), callbackSlot);
        addCall(id, call);
    }
    
}

#ifdef QT_QML_LIB
void User::sendImage(QPixmap image, QJSValue callbackFunction)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void User::sendImageAsync(QPixmap image)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
    
}

void User::sendImageSlot(QPixmap image)
{
    emit sendImageSignal(image);
    
}

void User::sendMessage(QString message, const QObject *obj, const QMetaMethod *callbackMethod)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);
    
    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), const_cast<QMetaMethod *>(callbackMethod));
        addCall(id, call);
    }
    
}

#ifdef QT_QML_LIB
void User::sendMessage(QString message, QJSValue callbackFunction)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void User::sendMessage(QString message)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);
    
    if(id){
    	RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
    	addCall(id, call);
    	call->eventLoop->exec();
    	removeCall(id);
    	delete call;
    }
}

void User::sendMessage(QString message, const QObject *obj, char *callbackSlot)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), callbackSlot);
        addCall(id, call);
    }
    
}

#ifdef __cplusplus >= 201103L
void User::sendMessage(QString message, std::function<void(void)> callbackFunction)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(callbackFunction);
        addCall(id, call);
    }
    
}
#endif

void User::sendMessageAsync(QString message)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);
    
    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
    
}

void User::sendMessageSlot(QString message)
{
    emit sendMessageSignal(message);
    
}

bool User::typing()
{
    return m_typing;
    
}

QString User::username()
{
    return m_username;
    
}

void User::setAvator(QPixmap avator)
{
    m_avator = avator;
    emit avatorChanged(avator);
    
}

void User::setTyping(bool typing)
{
    if (m_typing == typing)
        return;
    
    m_typing = typing;
    emit typingChanged(typing);
    
}

void User::setUsername(QString username)
{
    if (m_username == username)
        return;
    
    m_username = username;
    emit usernameChanged(username);
    
}


QT_END_NAMESPACE
