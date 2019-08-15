#ifndef USER_H
#define USER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include <AbstractHub>
#include <Peer>
#include <QPixmap>
#include <QString>

class User : public Neuron::Peer
{
    Q_OBJECT
    N_PROPERTY_DECL(QString, username, username, setUsername, usernameChanged)
    N_PROPERTY_DECL(QPixmap, avator, avator, setAvator, avatorChanged)

    N_REMOTE_METHOD_DECL(messageRecived, QString, username, QString, message)
    N_REMOTE_METHOD_DECL(sendImage, QPixmap, image)
    N_REMOTE_METHOD_DECL(sendMessage, QString, message)

public:
//    Q_INVOKABLE User(QObject *parent = nullptr);
//    User(Neuron::AbstractHub *hub, QObject *parent = nullptr);

    N_CLASS_DECL(User)
};

#endif // USER_H
