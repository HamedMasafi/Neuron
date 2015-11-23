#ifndef RPCHUB_P_H
#define RPCHUB_P_H

#include "noronhub.h"

#define ID                  "_id"
#define CLASS_NAME          "_c"
#define METHOD_NAME         "_m"
#define MAP_TYPE            "_t"
#define MAP_RETURN_VALUE    "_return_value"
#define MAP_TYPE_REQUEST    "request"
#define MAP_TYPE_RESPONSE   "response"
#define MAP_TOKEN_ITEM      "_token"

QT_BEGIN_NAMESPACE

class NoronHubPrivate{
    NoronHub *q_ptr;
    Q_DECLARE_PUBLIC(NoronHub)

public:
    NoronHubPrivate(NoronHub *parent);

    qint16 port;               // port
    QString serverAddress;     // address of server
    QSet<QString> locks;       // locks to prevent loop invoke
    QVariantList buffer;       // buffer for transactions
    QTcpSocket *socket;        // tcp socket
    bool isTransaction;        // if is in transaction mode
    qlonglong requestId;       // last request id
    int reconnectTimerId;      // reconnect after disconnect

    void addToMap(QVariantMap *map, QVariant var, int index);
    void procMap(QVariantMap map);
    bool response(qlonglong id, QString senderName, QVariant returnValue);
    void addValidateToken(QVariantMap *map);
    bool checkValidateToken(QVariantMap *map);
    QString MD5(QString text);
    QString MD5(QByteArray text);
};

QT_END_NAMESPACE
#endif // RPCHUB_P_H

