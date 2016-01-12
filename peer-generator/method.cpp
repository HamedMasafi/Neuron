#include "method.h"
#include "class.h"

#include <QDebug>
#include <QRegularExpression>
#include "texthelper.h"

Method::Method(QObject *parent) : QObject(parent), parentClass((Class*)parent),
    m_code(QString::null), m_isInvokable(false)
{
    parentClass = qobject_cast<Class*>(parent);
}

QString Method::declare()
{
    QString ret = QString("%4%1 %2(%3);")
            .arg(returnType())
            .arg(name())
            .arg(signature())
            .arg(isInvokable() ? "Q_INVOKABLE " : "");

    if(!wrapperMacro().isNull()){
        if(wrapperMacro().contains("<") || wrapperMacro().contains(">") || wrapperMacro().contains("=") )
            ret.prepend("#if " + wrapperMacro() + "\n");
        else
            ret.prepend("#ifdef " + wrapperMacro() + "\n");
        ret.append("\n#endif");
	}
    return ret;
}

QString Method::implement()
{
    if(code().isNull())
        return QString::null;

    QString ret = QString("%1 %5::%2(%3)\n{\n%4\n}")
            .arg(returnType())
            .arg(name())
            .arg(signature())
            .arg(TextHelper::instance()->indent(code()))
            .arg(parentClass->name());
    if(!wrapperMacro().isNull()){
        if(wrapperMacro().contains("<") || wrapperMacro().contains(">") || wrapperMacro().contains("=") )
            ret.prepend("#if " + wrapperMacro() + "\n");
        else
            ret.prepend("#ifdef " + wrapperMacro() + "\n");
        ret.append("\n#endif");
    }
    return ret;
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

QString Method::code() const
{
    return m_code;
}

bool Method::isInvokable() const
{
    return m_isInvokable;
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

void Method::setCode(QString code)
{
    if (m_code == code)
        return;

    m_code = code;
    emit codeChanged(code);
}

void Method::setIsInvokable(bool isInvokable)
{
    if (m_isInvokable == isInvokable)
        return;

    m_isInvokable = isInvokable;
    emit isInvokableChanged(isInvokable);
}

QString Method::getParametereNames(){
    QString s = signature();
    s.replace(QRegularExpression("(,|^)\\s*(const\\s+)?\\S+\\s*\\*?"), "\\1");
    return s;
}

QString Method::getParametereTypes(){
    QString s = signature();
    s.replace(QRegularExpression("(\\*)?(\\S*)\\s*(,|$)"), "\\1\\3");
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

