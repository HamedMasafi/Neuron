#include "class.h"
#include "texthelper.h"
#include "method.h"
#include "property.h"
#include "defines.h"
#include "enum.h"

#include <QDebug>
#include <QFile>
#include <QRegularExpression>

#define METHOD_SLOT             0
#define METHOD_FRESH            1
#define METHOD_ASYNC            2
#define METHOD_BYSIGNAL         3
#define METHOD_BYMETAMETHOD     4
#define METHOD_BYFUNC           5
#define METHOD_BYJSVALUE        6
#define METHOD_SIGNAL           7

#define FILE_NAME(x) #x


Class::Class(QObject *parent) : QObject(parent), m_headerFileName(QString::null), m_sourceFileName(QString::null),
    afterClass(QString::null), beginOfClass(QString::null), m_nameSpace(QString::null)
{

}

QString Class::headerCode() const
{
    QString code = "";

    QString lastDecl = "";
    QString methodsBlock;
    QString includeBlock = headerIncludeBlockCode() + LB;
    QString privateBlock = "";

    foreach (Property *p, properties)
        privateBlock.append(p->declareLine() + LB);
    privateBlock.append(LB);

    foreach (QString v, variables)
        privateBlock.append(v + LB);

    /*foreach (QString t, usedTypes) {
        if(t.startsWith("Q"))
            includeBlock.append("#include <" + t + ">" LB);
        else if(!TextHelper::instance()->hasOperatorEqual(t) && t != "void" && !t.startsWith(""))
            includeBlock.append("#include \"" + t + "\"" LB);
    }*/

    foreach (Method *m, methods) {
        if(m->isExtern())
            continue;

        if(m->declType() != lastDecl){
            methodsBlock.append("\n" + m->declType() + ":" LB);
            lastDecl = m->declType();
        }
        methodsBlock.append(m->declare() + LB);
    }
    foreach (Method *m, constructors) {
        if(m->declType() != lastDecl){
            methodsBlock.append("\n" + m->declType() + ":" LB);
            lastDecl = m->declType();
        }
        methodsBlock.append(m->declare() + LB);
    }

    code.append("#ifndef " + m_name.toUpper() + "_H" LB);
    code.append("#define " + m_name.toUpper() + "_H" LB LB);

    code.append(includeBlock + LB);

    if(!m_nameSpace.isNull())
        code.append("namespace " + m_nameSpace + "{" LB LB LB);

    foreach (QString className, declaredClasses)
        code.append("class " + className + ";" LB);

    code.append("class " + m_name + " : public " + m_baseType + LB);
    code.append("{" LB);

    if(!beginOfClass.isNull())
        code.append(beginOfClass);

    if(enums.count()){
        code.append("public:" LB);
        foreach (Enum *e, enums)
            code.append(e->toString() + LB);
    }

    code.append(methodsBlock + LB);

    if(!privateBlock.isEmpty())
        code.append("private:" LB + privateBlock + LB LB);


    code.append("};" LB);

    if(!afterClass.isNull())
        code.append(LB + afterClass + LB);

    if(!m_nameSpace.isNull())
        code.append("}" LB LB LB);


    code.append(TextHelper::instance()->joinSet(afterNameSpace, LB));
    code.append(LB LB);

    code.append("#endif // " + m_name.toUpper() + "_H" LB);

    return TextHelper::instance()->indent(code);
}

QString Class::sourceCode() const
{
    QString code = "#include \"" + headerFileName() + "\"" LB;

    code.append("#include <QMetaObject>" LB);
    code.append("#include <QMetaMethod>" LB LB);

    code.append(sourceIncludeBlockCode() + LB);

    if(!m_nameSpace.isNull())
        code.append("namespace " + m_nameSpace + LB "{" LB LB LB);

    foreach (Method *m, methods){
        if(!m->isExtern())
            continue;
        code.append(m->implement() + LB LB);
    }

    foreach (Method *m, constructors)
        code.append(m->implement() + LB LB);

    foreach (Method *m, methods){
        if(m->isExtern())
            continue;
        code.append(m->implement() + LB LB);
    }

    if(!m_nameSpace.isNull())
        code.append("}" LB);

    return TextHelper::instance()->indent(code);
}

bool methodLessThan(const Method *v1, const Method *v2)
{
    if(v1->declType() == v2->declType())
        return v1->name() < v2->name();
    else
        return v1->declType() < v2->declType();
}

void Class::save(QString dir)
{
    QFile hFile(dir + "/" + headerFileName());
    QFile cppFile(dir + "/" + sourceFileName());

    hFile.open(QIODevice::WriteOnly);
    cppFile.open(QIODevice::WriteOnly);

    qSort(methods.begin(), methods.end(), methodLessThan);
    hFile.write(headerCode().toUtf8());
    cppFile.write(sourceCode().toUtf8());

    hFile.close();
    cppFile.close();
}

void Class::addProperty(QString type, QString name)
{
    addProperty(new Property(type, name, this));
}

void Class::addProperty(QString type, QString name, QString readMethod, QString writeMethod, QString notifySignal, QString fieldName)
{
    addProperty(new Property(type, name, readMethod, writeMethod, notifySignal, fieldName));
}

void Class::addProperty(Property *prop)
{
    properties.append(prop);

    variables.append(prop->type() + " m_" + prop->name() + ";");

    Method *readMethod = new Method(this);
    Method *writeMethod = new Method(this);
    Method *notifySignal = new Method(this);

    readMethod->setReturnType(prop->type());
    writeMethod->setReturnType("void");
    notifySignal->setReturnType("void");

    writeMethod->setSignature(prop->type() + " " + prop->name());
    notifySignal->setSignature(prop->type() + " " + prop->name());

    readMethod->setDeclType("public");
    writeMethod->setDeclType("public slots");
    notifySignal->setDeclType("signals");

    readMethod->setName(prop->readMethodName());
    writeMethod->setName(prop->writeMethodName());
    notifySignal->setName(prop->notifySignalName());

    QString writeFileName = TextHelper::instance()->hasOperatorEqual(prop->type()) ? "property_write" : "property_write_nocheck";
    readMethod->setCode(TextHelper::instance()->getFileContent("property_read").arg(prop->name()));
    writeMethod->setCode(TextHelper::instance()->getFileContent(writeFileName).arg(prop->name()).arg(prop->writeMethodName()));

    addMethod(readMethod);
    addMethod(writeMethod);
    addMethod(notifySignal);

    usedTypes.insert(prop->type());
}

void Class::addMethod(Method *m)
{
    QStringList types = m->getParametereTypes().split(",");
    foreach (QString t, types)
        if(!t.contains(QRegularExpression("[^a-zA-Z0-9_]")))
            usedTypes.insert(t.trimmed().replace("*", ""));
    usedTypes.insert(m->returnType().replace("*", ""));

    methods.append(m);
}

void Class::addConstructor(Method *m)
{
    constructors.append(m);
}

void Class::addVariable(QString declareLine)
{
    variables.append(declareLine);
}

void Class::addEnum(Enum *e)
{
    enums.append(e);
}

void Class::addInclude(QString fileName, bool putInHeader, bool isGlobal, QString wrapperMacro, bool isClass)
{
    QString line = "";

    if(isGlobal)
        line = QString("#include <%1>").arg(fileName);
    else
        line = QString("#include \"%1\"").arg(fileName);

    if(!wrapperMacro.isNull())
        line = QString("#%1%3%2%3#endif")
                .arg(wrapperMacro)
                .arg(line.replace("#", "#    "))
                .arg(LB);

    if(putInHeader){
        m_headerIncludeBlockCode.insert(line);
    }else{
        m_sourceIncludeBlockCode.insert(line);
        if(/*fileName.startsWith("Q") && */isClass)
            declaredClasses.append(fileName);
    }
}

void Class::addBeginOfClass(QString line)
{
    beginOfClass.append(line + LB);
}

void Class::addAfterClass(QString line)
{
    afterClass.append(line + LB);
}

void Class::addAfterNamespace(QString line)
{
    afterNameSpace.insert(line);
}

void Class::addPrivateVariable(QString type, QString name)
{
    variables.append(type + " " + name + ";");
}

QString Class::name() const
{
    return m_name;
}

QString Class::baseType() const
{
    return m_baseType;
}

QString Class::sourceFileName() const
{
    if(m_sourceFileName.isNull())
        return m_name.toLower() + ".cpp";

    return m_sourceFileName;
}

QString Class::headerFileName() const
{
    if(m_headerFileName.isNull())
        return m_name.toLower() + ".h";

    return m_headerFileName;
}

QString Class::headerIncludeBlockCode() const
{
    return TextHelper::instance()->joinSet(m_headerIncludeBlockCode, LB);
}

QString Class::sourceIncludeBlockCode() const
{
    return TextHelper::instance()->joinSet(m_sourceIncludeBlockCode, LB);
}

QString Class::nameSpace() const
{
    return m_nameSpace;
}

void Class::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Class::setBaseType(QString baseType)
{
    if (m_baseType == baseType)
        return;

    m_baseType = baseType;
    emit baseTypeChanged(baseType);
}

void Class::setSourceFileName(QString sourceFileName)
{
    if (m_sourceFileName == sourceFileName)
        return;

    m_sourceFileName = sourceFileName;
    emit sourceFileNameChanged(sourceFileName);
}

void Class::setHeaderFileName(QString headerFileName)
{
    if (m_headerFileName == headerFileName)
        return;

    m_headerFileName = headerFileName;
    emit headerFileNameChanged(headerFileName);
}

void Class::setNameSpace(QString nameSpace)
{
    if (m_nameSpace == nameSpace)
        return;

    m_nameSpace = nameSpace;
    emit nameSpaceChanged(nameSpace);
}


