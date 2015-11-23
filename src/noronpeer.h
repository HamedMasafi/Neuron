#ifndef TOOJRCP_H
#define TOOJRCP_H

#include <QtCore/qglobal.h>

#include "noronhub.h"
#include "noronglobal.h"

QT_BEGIN_NAMESPACE

class QEventLoop;
class NoronHubBase;
class NoronServer;
class TOOJ_EXPORT NoronPeer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(NoronHubBase* hub READ hub WRITE setHub NOTIFY hubChanged)

    NoronHubBase *_hub;

public:
    explicit NoronPeer(QObject *parent = 0);
    ~NoronPeer();

    void connectToServer(QString address, qint16 port);

    NoronHubBase* hub() const;

protected:
    void addCall(long, NoronRemoteCallBase*);
    void removeCall(long);

signals:
    void hubChanged(NoronHubBase* hub);

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
    void setHub(NoronHubBase* hub);
};

QT_END_NAMESPACE

#endif // TOOJRCP_H
