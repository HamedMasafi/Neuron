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

public:
    Q_INVOKABLE AbstractClient(QObject *parent = nullptr);
    Q_INVOKABLE AbstractClient(Neuron::AbstractHub *hub, QObject *parent);
};
#endif // CLIENT
