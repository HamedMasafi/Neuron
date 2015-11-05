#ifndef SERVER_H
#define SERVER_H

#if __cplusplus < 201103L
#   include <functional>
#endif
#include "rpcpeer.h"

#include <QPixmap>

class Server : public RpcPeer{
   Q_OBJECT
    Q_PROPERTY(QStringList users READ users WRITE setUsers NOTIFY usersChanged)

    QStringList m_users;

signals:
    void usersChanged();
    void broadcastMessageHandle(QString message);
    void userJoinedHandle(QString username);
    void userLeavedHandle(QString username);
    void imageSentHandle(QString username, QPixmap image);

public:
    Q_INVOKABLE Server(QObject *parent = 0);
    QStringList users() const;

public slots:
    void setUsers(QStringList users);
	// broadcastMessage
    void broadcastMessageSlot(QString message);
    void broadcastMessage(QString message);
    void broadcastMessageAsync(QString message);
    void broadcastMessage(QString message, const QObject *obj, char *slotName);
    void broadcastMessage(QString message, const QObject *obj, const QMetaMethod *method);
#if __cplusplus >= 201103L
    void broadcastMessage(QString message, std::function<void(void)> func);
#endif
	// userJoined
    void userJoinedSlot(QString username);
    void userJoined(QString username);
    void userJoinedAsync(QString username);
    void userJoined(QString username, const QObject *obj, char *slotName);
    void userJoined(QString username, const QObject *obj, const QMetaMethod *method);
#if __cplusplus >= 201103L
    void userJoined(QString username, std::function<void(void)> func);
#endif
	// userLeaved
    void userLeavedSlot(QString username);
    void userLeaved(QString username);
    void userLeavedAsync(QString username);
    void userLeaved(QString username, const QObject *obj, char *slotName);
    void userLeaved(QString username, const QObject *obj, const QMetaMethod *method);
#if __cplusplus >= 201103L
    void userLeaved(QString username, std::function<void(void)> func);
#endif
	// imageSent
    void imageSentSlot(QString username, QPixmap image);
    void imageSent(QString username, QPixmap image);
    void imageSentAsync(QString username, QPixmap image);
    void imageSent(QString username, QPixmap image, const QObject *obj, char *slotName);
    void imageSent(QString username, QPixmap image, const QObject *obj, const QMetaMethod *method);
#if __cplusplus >= 201103L
    void imageSent(QString username, QPixmap image, std::function<void(void)> func);
#endif
};
#endif // SERVER_H
