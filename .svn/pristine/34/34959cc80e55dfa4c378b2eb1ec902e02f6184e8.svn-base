#include "method.h"
#include "class.h"

#include <QDebug>
#include <QRegularExpression>

Method::Method(QObject *parent) : QObject(parent), parentClass((Class*)parent)
{

}

QString Method::declType() const
{
    return m_declType;
}

QString Method::name() const
{
    return m_name;
}

QString Method::returnType() const
{
    return m_returnType;
}

QString Method::signature() const
{
    return m_signature;
}

QString Method::wrapperMacro() const
{
    return m_wrapperMacro;
}

QString Method::seprator() const
{
    return m_seprator;
}

void Method::setDeclType(QString declType)
{
    if (m_declType == declType)
        return;

    m_declType = declType;
    emit declTypeChanged(declType);
}

void Method::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Method::setReturnType(QString returnType)
{
    if (m_returnType == returnType)
        return;

    m_returnType = returnType;
    emit returnTypeChanged(returnType);
}

void Method::setSignature(QString signature)
{
    if (m_signature == signature)
        return;

    m_signature = signature;
    emit signatureChanged(signature);
}

void Method::setWrapperMacro(QString wrapperMacro)
{
    if (m_wrapperMacro == wrapperMacro)
        return;

    m_wrapperMacro = wrapperMacro;
    emit wrapperMacroChanged(wrapperMacro);
}

void Method::setSeprator(QString seprator)
{
    if (m_seprator == seprator)
        return;

    m_seprator = seprator;
    emit sepratorChanged(seprator);
}

QString Method::getParametereNames(){
    QString s = signature();
    qDebug() << "before "<< s;
    s.replace(QRegularExpression("(,|^)\\s*\\S+\\s*\\*?"), "\\1");
    qDebug() << "after "<< s;
    return s;
}

QString Method::getParametereTypes(){
    QString s = signature();
    s.replace(QRegularExpression("(\\*)?(\\S*)\\s*(,|$)"), "\\1");
    return s;
}

QString Method::replaceParams(QString text)
{
    return text
            .replace("%CLASS_NAME%", parentClass->name())
            .replace("%NAME%", name())
            .replace("%TYPE%", returnType())
            .replace("%SEP%", seprator())
            .replace("%SIGN%", signature())
            .replace("%SIGN_NAME%", getParametereNames())
            .replace("%SIGN_TYPE%", getParametereTypes());
}

