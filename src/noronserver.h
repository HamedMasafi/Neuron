#ifndef PRCSERVER_H
#define PRCSERVER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QSet>
#include <QTcpServer>

#include "norontcpsocketserver_p.h"
#include "noronhubbase.h"
#include "noronglobal.h"

QT_BEGIN_NAMESPACE

class NoronPeer;
class NoronServerPrivate;
class TOOJ_EXPORT NoronServer : public NoronHubBase
{
    Q_OBJECT

    NoronServerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(NoronServer)

    Q_PROPERTY(int typeId READ typeId WRITE setTypeId NOTIFY typeIdChanged)
    Q_PROPERTY(bool isMultiThread READ isMultiThread WRITE setIsMultiThread NOTIFY isMultiThreadChanged)

public:
    explicit NoronServer(qint16 port, QObject *parent = 0);

    QSet<NoronPeer*> peers();

    int typeId() const;
    bool isMultiThread() const;
    template <typename T> void registerType(){
        setTypeId(qRegisterMetaType<T>());
    }

    void beginTransaction();
    void rollback();
    void commit();

public slots:
    void setTypeId(int typeId);
    void setIsMultiThread(bool isMultiThread);

signals:
    void peerConnected(NoronPeer *peer);
    void peerDisconnected(NoronPeer *peer);
    void typeIdChanged(int typeId);
    void isMultiThreadChanged(bool isMultiThread);

private slots:
    void hub_disconnected();
    void server_newIncomingConnection(qintptr socketDescriptor);
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

#endif // PRCSERVER_H
