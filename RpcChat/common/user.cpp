#include "user.h"
#include <QMetaObject>
#include <QMetaMethod>
#include <QPixmap>

User::User(QObject *parent) : RpcPeer(parent)
{

}


//-----------------------------------------
// Methods for property username
//-----------------------------------------

QString User::username() const
{
    return m_username;
}

void User::setUsername(QString username)
{
    if (m_username == username)
        return;

    m_username = username;
    invokeOnPeer("setUsername", username);
    emit usernameChanged();
}


//-----------------------------------------
// Methods for property avator
//-----------------------------------------

QPixmap User::avator() const
{
    return m_avator;
}

void User::setAvator(QPixmap avator)
{
//    if (m_avator == avator)
//        return;

    m_avator = avator;
    invokeOnPeer("setAvator", avator);
    emit avatorChanged();
}


//-----------------------------------------
// Methods for property typing
//-----------------------------------------

bool User::typing() const
{
    return m_typing;
}

void User::setTyping(bool typing)
{
    if (m_typing == typing)
        return;

    m_typing = typing;
    invokeOnPeer("setTyping", typing);
    emit typingChanged();
}


//-----------------------------------------
// Methods for sendMessage
//-----------------------------------------

void User::sendMessageSlot(QString message)
{
    emit sendMessageHandle(message);
}

void User::sendMessageAsync(QString message)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
}

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

#if __cplusplus >= 201103L
void User::sendMessage(QString message, std::function<void()> func)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(func);
        addCall(id, call);
    }
}
#endif

void User::sendMessage(QString message, const QObject *obj, char *slotName)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), slotName);
        addCall(id, call);
    }
}

void User::sendMessage(QString message, const QObject *obj, const QMetaMethod *method)
{
    qlonglong id = invokeOnPeer("sendMessageSlot", message);

    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj),
                                                  const_cast<QMetaMethod *>(method));
        addCall(id, call);
    }
}

//-----------------------------------------
// Methods for messageRecived
//-----------------------------------------

void User::messageRecivedSlot(QString username, QString message)
{
    emit messageRecivedHandle(username,message);
}

void User::messageRecivedAsync(QString username, QString message)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
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

#if __cplusplus >= 201103L
void User::messageRecived(QString username, QString message, std::function<void()> func)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(func);
        addCall(id, call);
    }
}
#endif

void User::messageRecived(QString username, QString message, const QObject *obj, char *slotName)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), slotName);
        addCall(id, call);
    }
}

void User::messageRecived(QString username, QString message, const QObject *obj, const QMetaMethod *method)
{
    qlonglong id = invokeOnPeer("messageRecivedSlot", username,message);

    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj),
                                                  const_cast<QMetaMethod *>(method));
        addCall(id, call);
    }
}

//-----------------------------------------
// Methods for roomMessage
//-----------------------------------------

void User::roomMessageSlot(QString message)
{
    emit roomMessageHandle(message);
}

void User::roomMessageAsync(QString message)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
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

#if __cplusplus >= 201103L
void User::roomMessage(QString message, std::function<void()> func)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(func);
        addCall(id, call);
    }
}
#endif

void User::roomMessage(QString message, const QObject *obj, char *slotName)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), slotName);
        addCall(id, call);
    }
}

void User::roomMessage(QString message, const QObject *obj, const QMetaMethod *method)
{
    qlonglong id = invokeOnPeer("roomMessageSlot", message);

    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj),
                                                  const_cast<QMetaMethod *>(method));
        addCall(id, call);
    }
}

//-----------------------------------------
// Methods for sendImage
//-----------------------------------------

void User::sendImageSlot(QPixmap image)
{
    emit sendImageHandle(image);
}

void User::sendImageAsync(QPixmap image)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
        addCall(id, call);
    }
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

#if __cplusplus >= 201103L
void User::sendImage(QPixmap image, std::function<void()> func)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(func);
        addCall(id, call);
    }
}
#endif

void User::sendImage(QPixmap image, const QObject *obj, char *slotName)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);

    if(id){
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj), slotName);
        addCall(id, call);
    }
}

void User::sendImage(QPixmap image, const QObject *obj, const QMetaMethod *method)
{
    qlonglong id = invokeOnPeer("sendImageSlot", image);

    if(id){
        QObject *target = const_cast<QObject *>(obj);
        RemoteCallBase *call = new RemoteCallBase(const_cast<QObject *>(obj),
                                                  const_cast<QMetaMethod *>(method));
        addCall(id, call);
    }
}
