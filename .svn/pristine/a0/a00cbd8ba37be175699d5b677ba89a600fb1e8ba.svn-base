#ifndef PLAYER_H
#define PLAYER_H

#if __cplusplus < 201103L
#   include <functional>
#endif
#include "rpcpeer.h"

class Player : public RpcPeer{
   Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)

    QString m_username;
    QString m_email;
    QString m_password;

public:
    Player(QObject *parent = 0);
    QString username() const;
    QString password() const;
    QString email() const;

public slots:
	// login
    bool loginSlot();
    bool login();
    void loginAsync();
    void login(QObject *obj, char *slotName);
#if __cplusplus < 201103L
    void login(std::function<void(bool)> func);
#endif
	// getRandom
    qlonglong getRandomSlot();
    qlonglong getRandom();
    void getRandomAsync();
    void getRandom(QObject *obj, char *slotName);
#if __cplusplus < 201103L
    void getRandom(std::function<void(qlonglong)> func);
#endif
    void setUsername(QString username);
    void setPassword(QString password);
    void setEmail(QString email);

signals:
    void usernameChanged();
    void passwordChanged();
    void emailChanged();
};
#endif // PLAYER_H
