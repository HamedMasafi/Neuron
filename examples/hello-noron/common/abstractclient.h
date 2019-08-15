#ifndef CLIENT
#define CLIENT

#include <Peer>

class AbstractClient : public Neuron::Peer
{
    Q_OBJECT


    N_PROPERTY_DECL(int, t, t, setT, tChanged)
    N_PROPERTY_DECL(QString, username, username, setUsername, usernameChanged)

    N_REMOTE_METHOD_DECL(setTime)
    N_REMOTE_METHOD_DECL(int, getRandomNumber)

    N_CLASS_DECL(AbstractClient)
};
#endif // CLIENT
