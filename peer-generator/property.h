#ifndef PROPERTY_H
#define PROPERTY_H

#include <QtCore/QObject>

class Property : QObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString readMethod READ readMethod WRITE setReadMethod NOTIFY readMethodChanged)
    Q_PROPERTY(QString writeMethod READ writeMethod WRITE setWriteMethod NOTIFY writeMethodChanged)
    Q_PROPERTY(QString notifySignal READ notifySignal WRITE setNotifySignal NOTIFY notifySignalChanged)
    Q_PROPERTY(QString fieldName READ fieldName WRITE setFieldName NOTIFY fieldNameChanged)

    QString m_type;
    QString m_name;
    QString m_readMethod;
    QString m_writeMethod;
    QString m_notifySignal;
    QString m_fieldName;

public:
    Property(QString type, QString name, QObject *parent);
    Property(QString type, QString name, QString readMethod, QString writeMethod, QString notifySignal, QString fieldName, QObject *parent = 0);

    QString declareLine() const;

    QString type() const;
    QString name() const;
    QString readMethod() const;
    QString writeMethod() const;
    QString notifySignal() const;
    QString fieldName() const;

public slots:
    void setType(QString type);
    void setName(QString name);
    void setReadMethod(QString readMethod);
    void setWriteMethod(QString writeMethod);
    void setNotifySignal(QString notifySignal);
    void setFieldName(QString fieldName);

signals:
    void typeChanged(QString type);
    void nameChanged(QString name);
    void readMethodChanged(QString readMethod);
    void writeMethodChanged(QString writeMethod);
    void notifySignalChanged(QString notifySignal);
    void fieldNameChanged(QString fieldName);
};

#endif // PROPERTY_H
