#include "serverinstance.h"

#include <QMetaObject>
#include <QMetaMethod>

ServerInstance::ServerInstance(QObject *parent) : Neuron::SharedObject(parent)
{
}

ServerInstance::ServerInstance(Neuron::AbstractHub *hub, QObject *parent)
    : Neuron::SharedObject(hub, parent)
{
}

N_PROPERTY_IMPL(ServerInstance, QVariantList, users, users, setUsers, usersChanged)

N_REMOTE_METHOD_IMPL(ServerInstance, QString, message);
N_REMOTE_METHOD_IMPL(ServerInstance, imageSent, QString, username, QPixmap, image);
N_REMOTE_METHOD_IMPL(ServerInstance, userJoined, QString, username);
N_REMOTE_METHOD_IMPL(ServerInstance, userLeaved, QString, username);
N_REMOTE_METHOD_IMPL(ServerInstance, broadcastMessage, QString, message);
