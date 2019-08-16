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

typedef Neuron::Call<void> CallVoid;

class ServerInstance : public Neuron::SharedObject
{
    Q_OBJECT

    N_PROPERTY_DECL(QVariantList, users, users, setUsers, usersChanged)


public:
    Q_INVOKABLE ServerInstance(QObject *parent = nullptr);
    ServerInstance(Neuron::AbstractHub *hub, QObject *parent = nullptr);

    N_REMOTE_METHOD_DECL(QString, message)
    N_REMOTE_METHOD_DECL(imageSent, QString, username, QPixmap, image)
    N_REMOTE_METHOD_DECL(userJoined, QString, username)
    N_REMOTE_METHOD_DECL(userLeaved, QString, username)
    N_REMOTE_METHOD_DECL(broadcastMessage, QString, message)
};


#endif // SERVER_H
