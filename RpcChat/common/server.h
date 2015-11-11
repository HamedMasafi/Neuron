#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#if __cplusplus >= 201103L
#   include <functional>
#endif

#ifdef QT_QML_LIB
#   include <QJSValue>
#endif

#include <RpcPeer>
#include <QStringList>
#include <QString>
#include <QPixmap>


QT_BEGIN_NAMESPACE

class Server : public RpcPeer
{
    Q_OBJECT
    Q_PROPERTY(QStringList users READ users WRITE setUsers NOTIFY usersChanged USER true)
    
    QStringList m_users;
    

public:
    Q_INVOKABLE Server(QObject *parent = 0);
    #ifdef QT_QML_LIB
    Q_INVOKABLE void broadcastMessage(QString message, QJSValue callbackFunction);
    #endif
    #if __cplusplus >= 201103L
    void broadcastMessage(QString message, std::function<void(void)> callbackFunction);
    #endif
    Q_INVOKABLE void broadcastMessage(QString message);
    void broadcastMessage(QString message, const QObject *obj, char *callbackSlot);
    void broadcastMessage(QString message, const QObject *obj, const QMetaMethod *callbackMethod);
    Q_INVOKABLE void broadcastMessageAsync(QString message);
    void broadcastMessageSlot(QString message);
    void imageSent(QString username, QPixmap image, const QObject *obj, const QMetaMethod *callbackMethod);
    Q_INVOKABLE void imageSent(QString username, QPixmap image);
    #ifdef QT_QML_LIB
    Q_INVOKABLE void imageSent(QString username, QPixmap image, QJSValue callbackFunction);
    #endif
    void imageSent(QString username, QPixmap image, const QObject *obj, char *callbackSlot);
    #if __cplusplus >= 201103L
    void imageSent(QString username, QPixmap image, std::function<void(void)> callbackFunction);
    #endif
    Q_INVOKABLE void imageSentAsync(QString username, QPixmap image);
    void imageSentSlot(QString username, QPixmap image);
    #if __cplusplus >= 201103L
    void userJoined(QString username, std::function<void(void)> callbackFunction);
    #endif
    void userJoined(QString username, const QObject *obj, char *callbackSlot);
    Q_INVOKABLE void userJoined(QString username);
    void userJoined(QString username, const QObject *obj, const QMetaMethod *callbackMethod);
    #ifdef QT_QML_LIB
    Q_INVOKABLE void userJoined(QString username, QJSValue callbackFunction);
    #endif
    Q_INVOKABLE void userJoinedAsync(QString username);
    void userJoinedSlot(QString username);
    #ifdef QT_QML_LIB
    Q_INVOKABLE void userLeaved(QString username, QJSValue callbackFunction);
    #endif
    void userLeaved(QString username, const QObject *obj, const QMetaMethod *callbackMethod);
    #if __cplusplus >= 201103L
    void userLeaved(QString username, std::function<void(void)> callbackFunction);
    #endif
    Q_INVOKABLE void userLeaved(QString username);
    void userLeaved(QString username, const QObject *obj, char *callbackSlot);
    Q_INVOKABLE void userLeavedAsync(QString username);
    void userLeavedSlot(QString username);
    QStringList users();

public slots:
    void setUsers(QStringList users);

signals:
    void broadcastMessageSignal(QString message);
    void imageSentSignal(QString username, QPixmap image);
    void userJoinedSignal(QString username);
    void userLeavedSignal(QString username);
    void usersChanged(QStringList users);

};

QT_END_NAMESPACE

#endif // SERVER_H
