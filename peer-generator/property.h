#ifndef PROPERTY_H
#define PROPERTY_H

#include <QtCore/QObject>

class Method;
class Property : QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString readMethodName READ readMethodName WRITE setReadMethodName NOTIFY readMethodNameChanged)
    Q_PROPERTY(QString writeMethodName READ writeMethodName WRITE setWriteMethodName NOTIFY writeMethodNameChanged)
    Q_PROPERTY(QString notifySignalName READ notifySignalName WRITE setNotifySignalName NOTIFY notifySignalNameChanged)
    Q_PROPERTY(QString fieldName READ fieldName WRITE setFieldName NOTIFY fieldNameChanged)

//    Method *readMethod();
//    Method *writeMethod();
//    Method *notifySignal();

    QString m_type;
    QString m_name;
    QString m_readMethodName;
    QString m_writeMethodName;
    QString m_notifySignalName;
    QString m_fieldName;

public:
    Property(QString type, QString name, QObject *parent = 0);
    Property(QString type, QString name, QString readMethodName, QString writeMethodName, QString notifySignalName, QString fieldName, QObject *parent = 0);

    QString declareLine() const;

    QString type() const;
    QString name() const;
    QString readMethodName() const;
    QString writeMethodName() const;
    QString notifySignalName() const;
    QString fieldName() const;

public slots:
    void setType(QString type);
    void setName(QString name);
    void setReadMethodName(QString readMethodName);
    void setWriteMethodName(QString writeMethodName);
    void setNotifySignalName(QString notifySignalName);
    void setFieldName(QString fieldName);

signals:
    void typeChanged(QString type);
    void nameChanged(QString name);
    void readMethodNameChanged(QString readMethodName);
    void writeMethodNameChanged(QString writeMethodName);
    void notifySignalNameChanged(QString notifySignalName);
    void fieldNameChanged(QString fieldName);
};

#endif // PROPERTY_H
