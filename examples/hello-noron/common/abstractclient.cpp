#include "abstractclient.h"

#include <QMetaObject>
#include <QMetaMethod>

using namespace Neuron;

AbstractClient::AbstractClient(QObject *parent) : Peer(parent)
{
    setPeerName("AbstractClient");
}

AbstractClient::AbstractClient(AbstractHub *hub, QObject *parent) : Peer(parent)
{
    if(hub)
        setHub(hub);
    setPeerName("AbstractClient");
}

N_PROPERTY_IMPL(AbstractClient, int, t, t, setT, tChanged)
N_PROPERTY_IMPL(AbstractClient, QString, username, username, setUsername, usernameChanged)

N_REMOTE_METHOD_IMPL(AbstractClient, setTime)
N_REMOTE_METHOD_IMPL(AbstractClient, int, getRandomNumber)
