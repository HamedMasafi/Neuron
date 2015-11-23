#ifndef RPCHUB_H
#define RPCHUB_H

#include <QtCore/QObject>
#include <QHash>
#include <QSet>

#include "noronglobal.h"
#include "noronhubbase.h"

QT_BEGIN_NAMESPACE

class QTcpSocket;
class NoronPeer;
class NoronSerializerBase;
class NoronHubPrivate;
class TOOJ_EXPORT NoronHub : public NoronHubBase
{
    Q_OBJECT
    NoronHubPrivate *d_ptr;
    Q_DECLARE_PRIVATE(NoronHub)

public:
    explicit NoronHub(QObject *parent = 0);
    explicit NoronHub(NoronSerializerBase *serializer, QObject *parent = 0);
    virtual ~NoronHub();

    Q_INVOKABLE void beginTransaction();
    Q_INVOKABLE bool isTransaction() const;
    Q_INVOKABLE void rollback();
    Q_INVOKABLE void commit();

    Q_INVOKABLE void connectToServer(QString address = QString::null, qint16 port = 0);
    Q_INVOKABLE void disconnectFromServer();
    Q_INVOKABLE bool setSocketDescriptor(qintptr socketDescriptor);

    bool sendBlocked() const;
    void timerEvent(QTimerEvent *);
    void sync();

signals:
    void disconnected();
    void sendBlockedChanged(bool);

public slots:
    void socket_connected();
    void socket_disconnected();
    void socket_onReadyRead();
    qlonglong invokeOnPeer(
            QString sender,
            QString methodName,
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


};

QT_END_NAMESPACE

#endif // RPCHUB_H
