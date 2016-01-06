#include "property.h"

Property::Property(QString type, QString name, QObject *parent) : QObject(parent)
{
    QString writeMethod = name;
    writeMethod[0] = writeMethod[0].toUpper();

    setType(type);
    setName(name);
    setReadMethod(name);
    setWriteMethod(writeMethod);
    setNotifySignal(name + "Changed");
    setFieldName("m_" + name);
}

Property::Property(QString type, QString name, QString readMethod, QString writeMethod, QString notifySignal, QString fieldName, QObject *parent) : QObject(parent),
    m_type(type), m_name(name), m_readMethod(readMethod), m_writeMethod(writeMethod), m_notifySignal(notifySignal), m_fieldName(fieldName)
{

}

QString Property::declareLine() const
{
    return QString("Q_PROPERTY(%1 %2 READ %3 WRITE %4 NOTIFY %5 USER true)")
            .arg(type())
            .arg(name())
            .arg(readMethod())
            .arg(writeMethod())
            .arg(notifySignal());
}

QString Property::type() const
{
    return m_type;
}

QString Property::name() const
{
    return m_name;
}

QString Property::readMethod() const
{
    return m_readMethod;
}

QString Property::writeMethod() const
{
    return m_writeMethod;
}

QString Property::notifySignal() const
{
    return m_notifySignal;
}

QString Property::fieldName() const
{
    return m_fieldName;
}

void Property::setType(QString type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(type);
}

void Property::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Property::setReadMethod(QString readMethod)
{
    if (m_readMethod == readMethod)
        return;

    m_readMethod = readMethod;
    emit readMethodChanged(readMethod);
}

void Property::setWriteMethod(QString writeMethod)
{
    if (m_writeMethod == writeMethod)
        return;

    m_writeMethod = writeMethod;
    emit writeMethodChanged(writeMethod);
}

void Property::setNotifySignal(QString notifySignal)
{
    if (m_notifySignal == notifySignal)
        return;

    m_notifySignal = notifySignal;
    emit notifySignalChanged(notifySignal);
}

void Property::setFieldName(QString fieldName)
{
    if (m_fieldName == fieldName)
        return;

    m_fieldName = fieldName;
    emit fieldNameChanged(fieldName);
}
