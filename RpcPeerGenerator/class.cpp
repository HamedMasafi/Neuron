#include "class.h"

#include "method.h"

#include <QRegularExpression>

Class::Class(QObject *parent) : QObject(parent)
{

}

void Class::parse(QString templateCode)
{
//    QStringList lines = templateCode.split("\n");

//    foreach (QString line, lines) {
//        line = line.trimmed();

//        if(line.startsWith("//"))
//            continue;

//        if(line.startsWith("Q_PROPERTY"))
//            procProperty(line);
//        else
//            procLine(line);
//    }
}

QString Class::name() const
{
    return m_name;
}

void Class::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Class::procLine(QString line)
{
    QList<Method*> methods;
    for(int i = 0; i < 5; i++)
        methods.append(new Method(this));
//    Method methodSlot = new Method(this);
//    Method methodAsync = new Method(this);
//    Method methodFresh = new Method(this);
//    Method methodFunc = new Method(this);
//    Method methodSignal = new Method(this);

    QRegularExpression regex("(\\S+)\\s+(\\S+)\\((.*)\\);");
    QRegularExpressionMatch match = regex.match(line);

    if(!match.hasMatch())
        return;

    QString returnType = match.captured(1);
    QString name = match.captured(2);
    QString params = match.captured(3);

    QString sep = "";
    if(params.trimmed() != "")
        sep.append(", ");

    foreach (Method *m, methods) {
        m->setName(name);
        m->setReturnType(returnType);
        m->setSeprator(sep);
        m->setSignature(params);
    }
}

