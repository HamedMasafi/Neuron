#ifndef TOOJRCP_H
#define TOOJRCP_H

#include <QtCore/qglobal.h>

#include "rpchub.h"
#include "rpcglobal.h"

class QEventLoop;
class RpcHubBase;
class RpcServer;
class TOOJ_EXPORT RpcPeer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RpcHubBase* hub READ hub WRITE setHub NOTIFY hubChanged)

    RpcHubBase *_hub;

public:
    explicit RpcPeer(QObject *parent = 0);
    ~RpcPeer();

    void connectToServer(QString address, qint16 port);

    RpcHubBase* hub() const;

protected:
    void addCall(long, RemoteCallBase*);
    void removeCall(long);

signals:
    void hubChanged(RpcHubBase* hub);

public slots:

    qlonglong invokeOnPeer(QString methodName,
                      QVariant val0 = QVariant(),
                      QVariant val1 = QVariant(),
                      QVariant val2 = QVariant(),
                      QVariant val3 = QVariant(),
                      QVariant val4 = QVariant(),
                      QVariant val5 = QVariant(),
                      QVariant val6 = QVariant(),
                      QVariant val7 = QVariant(),
                      QVariant val8 = QVariant(),
                      QVariant val9 = QVariant());
    void setHub(RpcHubBase* hub);
};

#endif // TOOJRCP_H
