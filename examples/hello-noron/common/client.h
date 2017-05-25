#ifndef CLIENT
#define CLIENT

#include <NoronPeer>


class Client : public NoronPeer
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged USER true)


    N_PROPERTY_DECL(int, t, t, setT, tChanged)
    N_REMOTE_METHOD_DECL(void, setTime)

public:
    Client(QObject *parent);
    Client(NoronAbstractHub *hub, QObject *parent);

public slots:
#ifdef QT_QML_LIB
    int getRandomNumber(QJSValue callbackFunction);
#endif
#if __cplusplus >= 201103L
    int getRandomNumber(std::function<void(int)> callbackFunction);
#endif
    Q_INVOKABLE int getRandomNumber(const QObject *obj, char *callbackSlot);
    int getRandomNumber();
    int getRandomNumber(const QObject *obj, const QMetaMethod *callbackMethod);
    int getRandomNumberAsync();
    int getRandomNumberSlot();

signals:
    int getRandomNumberSignal(int returnValue);

};
#endif // CLIENT
