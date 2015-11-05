#include "server.h"
#include <QMetaObject>

Server::Server(QObject *parent) : RpcPeer(parent)
{

}


//-----------------------------------------
// Methods for login
//-----------------------------------------

bool Player::loginSlot()
{
	bool ret;
    emit loginSignal(&ret);
    return ret;
    //throw std::runtime_error("TODO: fill block 'Player::login' in subclass");
}

void Player::loginAsync()
{
	qlonglong id = invokeOnPeer("loginSlot", false);
    RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
    _calls[id] = call;
}

bool Player::login()
{
	if(_isTransaction){
        return loginAsync();
    }else{
		qlonglong id = invokeOnPeer("loginSlot", false);
		RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
		_calls[id] = call;
		call->eventLoop->exec();
		bool ret = call->returnData.value<bool>();
		_calls.remove(id);
		delete call;
		return ret;
	}
}

#if __cplusplus < 201103L
void Player::login(std::function<void(bool)> func)
{
    RemoteCall<bool> *call = new RemoteCall<bool>(func);
    qlonglong id = invokeOnPeer("loginSlot", false);
    _calls[id] = call;
}
#endif

void Player::login(QObject *obj, char *slotName)
{
    RemoteCall<bool> *call = new RemoteCall<bool>(obj, slotName);
    qlonglong id = invokeOnPeer("loginSlot", false);
    _calls[id] = call;
}

//-----------------------------------------
// Methods for getRandom
//-----------------------------------------

qlonglong Player::getRandomSlot()
{
	qlonglong ret;
    emit loginSignal(&ret);
    return ret;
    //throw std::runtime_error("TODO: fill block 'Player::getRandom' in subclass");
}

void Player::getRandomAsync()
{
	qlonglong id = invokeOnPeer("getRandomSlot", false);
    RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
    _calls[id] = call;
}

qlonglong Player::getRandom()
{
	if(_isTransaction){
        return getRandomAsync();
    }else{
		qlonglong id = invokeOnPeer("getRandomSlot", false);
		RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
		_calls[id] = call;
		call->eventLoop->exec();
		qlonglong ret = call->returnData.value<qlonglong>();
		_calls.remove(id);
		delete call;
		return ret;
	}
}

#if __cplusplus < 201103L
void Player::getRandom(std::function<void(qlonglong)> func)
{
    RemoteCall<qlonglong> *call = new RemoteCall<qlonglong>(func);
    qlonglong id = invokeOnPeer("getRandomSlot", false);
    _calls[id] = call;
}
#endif

void Player::getRandom(QObject *obj, char *slotName)
{
    RemoteCall<qlonglong> *call = new RemoteCall<qlonglong>(obj, slotName);
    qlonglong id = invokeOnPeer("getRandomSlot", false);
    _calls[id] = call;
}

//-----------------------------------------
// Methods for property username
//-----------------------------------------

QString Player::username() const
{
    return m_username;
}

void Player::setUsername(QString username)
{
    if (m_username == username)
        return;

    m_username = username;
    invokeOnPeer("setUsername", false, username);
    emit usernameChanged();
}


//-----------------------------------------
// Methods for property password
//-----------------------------------------

QString Player::password() const
{
    return m_password;
}

void Player::setPassword(QString password)
{
    if (m_password == password)
        return;

    m_password = password;
    invokeOnPeer("setPassword", false, password);
    emit passwordChanged();
}


//-----------------------------------------
// Methods for property email
//-----------------------------------------

QString Player::email() const
{
    return m_email;
}

void Player::setEmail(QString email)
{
    if (m_email == email)
        return;

    m_email = email;
    invokeOnPeer("setEmail", false, email);
    emit emailChanged();
}


//-----------------------------------------
// Methods for getCount
//-----------------------------------------

int WebStorage::getCountSlot()
{
	int ret;
    emit loginSignal(&ret);
    return ret;
    //throw std::runtime_error("TODO: fill block 'WebStorage::getCount' in subclass");
}

void WebStorage::getCountAsync()
{
	qlonglong id = invokeOnPeer("getCountSlot", false);
    RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
    _calls[id] = call;
}

int WebStorage::getCount()
{
	if(_isTransaction){
        return getCountAsync();
    }else{
		qlonglong id = invokeOnPeer("getCountSlot", false);
		RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
		_calls[id] = call;
		call->eventLoop->exec();
		int ret = call->returnData.value<int>();
		_calls.remove(id);
		delete call;
		return ret;
	}
}

#if __cplusplus < 201103L
void WebStorage::getCount(std::function<void(int)> func)
{
    RemoteCall<int> *call = new RemoteCall<int>(func);
    qlonglong id = invokeOnPeer("getCountSlot", false);
    _calls[id] = call;
}
#endif

void WebStorage::getCount(QObject *obj, char *slotName)
{
    RemoteCall<int> *call = new RemoteCall<int>(obj, slotName);
    qlonglong id = invokeOnPeer("getCountSlot", false);
    _calls[id] = call;
}

//-----------------------------------------
// Methods for loginToServer
//-----------------------------------------

void Server::loginToServerSlot()
{
    throw std::runtime_error("TODO: fill block 'Server::loginToServer' in subclass");
}

void Server::loginToServerAsync()
{
	qlonglong id = invokeOnPeer("loginToServerSlot", false);
    RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
    _calls[id] = call;
}

void Server::loginToServer()
{
	if(_isTransaction){
        loginToServerAsync();
    }else{
		qlonglong id = invokeOnPeer("loginToServerSlot", false);
		RemoteCallBase *call = new RemoteCallBase(RemoteCallBase::EventLoop);
		_calls[id] = call;
		call->eventLoop->exec();
		_calls.remove(id);
		delete call;
	}
}

#if __cplusplus < 201103L
void Server::loginToServer(std::function<void()> func)
{
	RemoteCallBase *call = new RemoteCallBase(func);
    qlonglong id = invokeOnPeer("loginToServerSlot", false);
    _calls[id] = call;
}
#endif

void Server::loginToServer(QObject *obj, char *slotName)
{
    RemoteCallBase *call = new RemoteCallBase(obj, slotName);
    qlonglong id = invokeOnPeer("loginToServerSlot", false);
    _calls[id] = call;
}
