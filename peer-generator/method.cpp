#include "method.h"
#include "class.h"

#include "defines.h"

#include <QDebug>
#include <QRegularExpression>
#include "texthelper.h"

Method::Method(QObject *parent) : QObject(parent), parentClass((Class*)parent),
    m_code(QString::null), m_isInvokable(false), m_inheristanceDeclare(QString::null), m_returnType(QString::null),
    m_isStatic(false), m_isExtern(false), m_isVirtual(false)
{
    parentClass = qobject_cast<Class*>(parent);
}

QString Method::declare()
{
    QString ret = QString("%6%5%4%1 %2(%3);")
            .arg(returnType())
            .arg(name())
            .arg(signature())
            .arg(isInvokable() ? "Q_INVOKABLE " : "")
            .arg(isStatic() ? "static " : "")
            .arg(isVirtual() ? "virtual " : "");

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
    if(declType() == "signals")
        return QString::null;

    QString ret = "";
    QString normalizedCode = code();
    if(!normalizedCode.endsWith(LB))
        normalizedCode.append(LB);

    if(isExtern())
        ret = QString("static %1 %2(%3)" LB "{" LB "%4}")
                .arg(returnType())
                .arg(name())
                .arg(signature().replace(QRegularExpression("\\s*=\\s*\\S*"), ""))
                .arg(normalizedCode);
    else
        ret = QString("%1 %5::%2(%3)%6" LB "{" LB "%4}")
                .arg(returnType())
                .arg(name())
                .arg(signature().replace(QRegularExpression("\\s*=\\s*\\S*"), ""))
                .arg(normalizedCode)
                .arg(parentClass->name())
                .arg(inheristanceDeclare().isNull() ? "" : " : " +inheristanceDeclare());


    if(!wrapperMacro().isNull()){
        if(wrapperMacro().contains("<") || wrapperMacro().contains(">") || wrapperMacro().contains("=") )
            ret.prepend("#if " + wrapperMacro() + LB);
        else
            ret.prepend("#ifdef " + wrapperMacro() + LB);
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

QString Method::inheristanceDeclare() const
{
    return m_inheristanceDeclare;
}

bool Method::isStatic() const
{
    return m_isStatic;
}

bool Method::isExtern() const
{
    return m_isExtern;
}

bool Method::isVirtual() const
{
    return m_isVirtual;
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

void Method::setInheristanceDeclare(QString inheristanceDeclare)
{
    if (m_inheristanceDeclare == inheristanceDeclare)
        return;

    m_inheristanceDeclare = inheristanceDeclare;
    emit inheristanceDeclareChanged(inheristanceDeclare);
}

void Method::setIsStatic(bool isStatic)
{
    if (m_isStatic == isStatic)
        return;

    m_isStatic = isStatic;
    emit isStaticChanged(isStatic);
}

void Method::setIsExtern(bool isExtern)
{
    if (m_isExtern == isExtern)
        return;

    m_isExtern = isExtern;
    emit isExternChanged(isExtern);
}

void Method::setIsVirtual(bool isVirtual)
{
    if (m_isVirtual == isVirtual)
        return;

    m_isVirtual = isVirtual;
    emit isVirtualChanged(isVirtual);
}

QString Method::getParametereNames(){
    QString ret = "";
    QRegularExpression r("(const\\s+)?(?<type>\\S+)\\s*(?<star>\\*?)\\s*(\\&?)(?<name>\\S+)(\\s*=\\s*\\S)?\\s*,");
    QRegularExpressionMatchIterator i = r.globalMatch(signature() + ",", 0, QRegularExpression::PartialPreferCompleteMatch);

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if(!ret.isEmpty())
            ret.append(", ");
        ret.append(match.captured("name"));
    }
    return ret;
}

QString Method::getParametereTypes(){
    QString ret = "";
    QRegularExpression r("(const\\s+)?(?<type>\\S+)\\s*(?<star>\\*?)\\s*(\\&?)(?<name>\\S+)(\\s*=\\s*\\S)?\\s*,");
    QRegularExpressionMatchIterator i = r.globalMatch(signature() + ",", 0, QRegularExpression::PartialPreferCompleteMatch);

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        if(!ret.isEmpty())
            ret.append(", ");
        ret.append(match.captured("type"));

        if(!match.captured("star").isNull())
            ret.append("*");
    }

    return ret;
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

