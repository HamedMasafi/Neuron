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

#include <AbstractHub>
#include <SharedObject>
#include <QPixmap>
#include <QVariantList>
#include <QString>


NEURON_BEGIN_NAMESPACE

class Server : public SharedObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList users READ users WRITE setUsers NOTIFY usersChanged USER true)
    
    QVariantList m_users;
    

public:
    Q_INVOKABLE Server(QObject *parent = 0);
    Server(AbstractHub *hub, QObject *parent = 0);
    QVariantList users();

public slots:
    void broadcastMessage(QString message, const QObject *obj, char *callbackSlot);
    void broadcastMessage(QString message, const QObject *obj, const QMetaMethod *callbackMethod);
    #ifdef QT_QML_LIB
    void broadcastMessage(QString message, QJSValue callbackFunction);
    #endif
    #if __cplusplus >= 201103L
    void broadcastMessage(QString message, std::function<void(void)> callbackFunction);
    #endif
    void broadcastMessage(QString message);
    void broadcastMessageAsync(QString message);
    void broadcastMessageSlot(QString message);
    #ifdef QT_QML_LIB
    void imageSent(QString username, QPixmap image, QJSValue callbackFunction);
    #endif
    void imageSent(QString username, QPixmap image, const QObject *obj, char *callbackSlot);
    void imageSent(QString username, QPixmap image);
    void imageSent(QString username, QPixmap image, const QObject *obj, const QMetaMethod *callbackMethod);
    #if __cplusplus >= 201103L
    void imageSent(QString username, QPixmap image, std::function<void(void)> callbackFunction);
    #endif
    void imageSentAsync(QString username, QPixmap image);
    void imageSentSlot(QString username, QPixmap image);
    void setUsers(QVariantList users);
    #ifdef QT_QML_LIB
    void userJoined(QString username, QJSValue callbackFunction);
    #endif
    void userJoined(QString username, const QObject *obj, char *callbackSlot);
    void userJoined(QString username, const QObject *obj, const QMetaMethod *callbackMethod);
    void userJoined(QString username);
    #if __cplusplus >= 201103L
    void userJoined(QString username, std::function<void(void)> callbackFunction);
    #endif
    void userJoinedAsync(QString username);
    void userJoinedSlot(QString username);
    #if __cplusplus >= 201103L
    void userLeaved(QString username, std::function<void(void)> callbackFunction);
    #endif
    #ifdef QT_QML_LIB
    void userLeaved(QString username, QJSValue callbackFunction);
    #endif
    void userLeaved(QString username, const QObject *obj, const QMetaMethod *callbackMethod);
    void userLeaved(QString username, const QObject *obj, char *callbackSlot);
    void userLeaved(QString username);
    void userLeavedAsync(QString username);
    void userLeavedSlot(QString username);

signals:
    void broadcastMessageSignal(QString message);
    void imageSentSignal(QString username, QPixmap image);
    void userJoinedSignal(QString username);
    void userLeavedSignal(QString username);
    void usersChanged(QVariantList users);

};

NEURON_END_NAMESPACE

#endif // SERVER_H
