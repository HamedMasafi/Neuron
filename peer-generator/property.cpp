#include "property.h"

Property::Property(QString type, QString name, QObject *parent) : QObject(parent)
{
    QString writeMethodName = name;
    writeMethodName[0] = writeMethodName[0].toUpper();

    setType(type);
    setName(name);
    setReadMethodName(name);
    setWriteMethodName("set" + writeMethodName);
    setNotifySignalName(name + "Changed");
    setFieldName("m_" + name);
}

Property::Property(QString type, QString name, QString readMethodName, QString writeMethodName, QString notifySignal, QString fieldName, QObject *parent) : QObject(parent),
    m_type(type), m_name(name), m_readMethodName(readMethodName), m_writeMethodName(writeMethodName), m_notifySignalName(notifySignal), m_fieldName(fieldName)
{

}

QString Property::declareLine() const
{
    if(notifySignalName().isEmpty() || notifySignalName().isNull())
        return QString("Q_PROPERTY(%1 %2 READ %3 WRITE %4 USER true)")
                .arg(type())
                .arg(name())
                .arg(readMethodName())
                .arg(writeMethodName());
    else
        return QString("Q_PROPERTY(%1 %2 READ %3 WRITE %4 NOTIFY %5 USER true)")
                .arg(type())
                .arg(name())
                .arg(readMethodName())
                .arg(writeMethodName())
                .arg(notifySignalName());
}

QString Property::type() const
{
    return m_type;
}

QString Property::name() const
{
    return m_name;
}

QString Property::readMethodName() const
{
    return m_readMethodName;
}

QString Property::writeMethodName() const
{
    return m_writeMethodName;
}

QString Property::notifySignalName() const
{
    return m_notifySignalName;
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

void Property::setReadMethodName(QString readMethodName)
{
    if (m_readMethodName == readMethodName)
        return;

    m_readMethodName = readMethodName;
    emit readMethodNameChanged(readMethodName);
}

void Property::setWriteMethodName(QString writeMethodName)
{
    if (m_writeMethodName == writeMethodName)
        return;

    m_writeMethodName = writeMethodName;
    emit writeMethodNameChanged(writeMethodName);
}

void Property::setNotifySignalName(QString notifySignalName)
{
    if (m_notifySignalName == notifySignalName)
        return;

    m_notifySignalName = notifySignalName;
    emit notifySignalNameChanged(notifySignalName);
}

void Property::setFieldName(QString fieldName)
{
    if (m_fieldName == fieldName)
        return;

    m_fieldName = fieldName;
    emit fieldNameChanged(fieldName);
}
