#ifndef WEBSTORAGE_H
#define WEBSTORAGE_H

#if __cplusplus < 201103L
#   include <functional>
#endif
#include "rpcpeer.h"

class WebStorage : public RpcPeer{
   Q_OBJECT


public:
    WebStorage(QObject *parent = 0);

public slots:
	// getCount
    int getCountSlot();
    int getCount();
    void getCountAsync();
    void getCount(QObject *obj, char *slotName);
#if __cplusplus < 201103L
    void getCount(std::function<void(int)> func);
#endif
};
#endif // WEBSTORAGE_H
