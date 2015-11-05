#ifndef SERVER_H
#define SERVER_H

#if __cplusplus < 201103L
#   include <functional>
#endif
#include "rpcpeer.h"

class Server : public RpcPeer{
   Q_OBJECT


public:
    Server(QObject *parent = 0);

public slots:
	// loginToServer
    void loginToServerSlot();
    void loginToServer();
    void loginToServerAsync();
    void loginToServer(QObject *obj, char *slotName);
#if __cplusplus < 201103L
    void loginToServer(std::function<void(void)> func);
#endif
};
#endif // SERVER_H
