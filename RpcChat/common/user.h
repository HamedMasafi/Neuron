#ifndef USER_H
#define USER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#if __cplusplus >= 201103L
#   include <functional>
#endif

#ifdef QT_QML_LIB
#   include <QJSValue>
#endif

#include <RpcPeer>
#include <QString>
#include <QPixmap>


QT_BEGIN_NAMESPACE

class User : public RpcPeer
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged USER true)
    Q_PROPERTY(QPixmap avator READ avator WRITE setAvator NOTIFY avatorChanged USER true)
    Q_PROPERTY(bool typing READ typing WRITE setTyping NOTIFY typingChanged USER true)
    
    QString m_username;
    QPixmap m_avator;
    bool m_typing;
    

public:
    Q_INVOKABLE User(QObject *parent = 0);
    QPixmap avator();
    bool typing();
    QString username();

public slots:
    void messageRecived(QString username, QString message);
    void messageRecived(QString username, QString message, const QObject *obj, const QMetaMethod *callbackMethod);
    #if __cplusplus >= 201103L
    void messageRecived(QString username, QString message, std::function<void(void)> callbackFunction);
    #endif
    #ifdef QT_QML_LIB
    void messageRecived(QString username, QString message, QJSValue callbackFunction);
    #endif
    void messageRecived(QString username, QString message, const QObject *obj, char *callbackSlot);
    void messageRecivedAsync(QString username, QString message);
    void messageRecivedSlot(QString username, QString message);
    void roomMessage(QString message, const QObject *obj, const QMetaMethod *callbackMethod);
    #ifdef QT_QML_LIB
    void roomMessage(QString message, QJSValue callbackFunction);
    #endif
    void roomMessage(QString message, const QObject *obj, char *callbackSlot);
    void roomMessage(QString message);
    #if __cplusplus >= 201103L
    void roomMessage(QString message, std::function<void(void)> callbackFunction);
    #endif
    void roomMessageAsync(QString message);
    void roomMessageSlot(QString message);
    void sendImage(QPixmap image);
    void sendImage(QPixmap image, const QObject *obj, const QMetaMethod *callbackMethod);
    #if __cplusplus >= 201103L
    void sendImage(QPixmap image, std::function<void(void)> callbackFunction);
    #endif
    #ifdef QT_QML_LIB
    void sendImage(QPixmap image, QJSValue callbackFunction);
    #endif
    void sendImage(QPixmap image, const QObject *obj, char *callbackSlot);
    void sendImageAsync(QPixmap image);
    void sendImageSlot(QPixmap image);
    void sendMessage(QString message);
    void sendMessage(QString message, const QObject *obj, char *callbackSlot);
    void sendMessage(QString message, const QObject *obj, const QMetaMethod *callbackMethod);
    #ifdef QT_QML_LIB
    void sendMessage(QString message, QJSValue callbackFunction);
    #endif
    #if __cplusplus >= 201103L
    void sendMessage(QString message, std::function<void(void)> callbackFunction);
    #endif
    void sendMessageAsync(QString message);
    void sendMessageSlot(QString message);
    void setAvator(QPixmap avator);
    void setTyping(bool typing);
    void setUsername(QString username);

signals:
    void avatorChanged(QPixmap avator);
    void messageRecivedSignal(QString username, QString message);
    void roomMessageSignal(QString message);
    void sendImageSignal(QPixmap image);
    void sendMessageSignal(QString message);
    void typingChanged(bool typing);
    void usernameChanged(QString username);

};

QT_END_NAMESPACE

#endif // USER_H
