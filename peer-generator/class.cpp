#include "class.h"
#include "texthelper.h"
#include "method.h"
#include "property.h"

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

#ifdef Q_OS_WIN
#   define LB "\r\n"
#endif
#ifdef Q_OS_LINUX
#   define LB "\n"
#endif
#ifdef Q_OS_MACOSX
#   define LB "\r"
#endif

Class::Class(QObject *parent) : QObject(parent)
{

}

void Class::parse(QString templateCode)
{
    QStringList lines = templateCode.split("\n");

    foreach (QString line, lines) {
        line = line.trimmed();

        if(line.startsWith("//"))
            continue;

        if(line.startsWith("Q_PROPERTY"))
            procProperty(line);
        else
            procLine(line);
    }
}

QString Class::h()
{
    QString lastDecl = "public";
    QString ret;
    QString includeBlock;
    QString privateBlock;

    foreach (QString p, propertiesList)
        privateBlock.append(p + "\n");
    privateBlock.append("\n");
    foreach (QString v, variables)
        privateBlock.append(v + "\n");

    foreach (QString t, usedTypes) {
        if(t.startsWith("Q"))
            includeBlock.append("#include <" + t + ">\n");
    }

    foreach (Method *m, methods) {
        if(m->declType() != lastDecl){
            ret.append("\n" + m->declType() + ":\n");
            lastDecl = m->declType();
        }
        ret.append(TextHelper::instance()->indent(m->declare()) + "\n");
    }

    ret = QString(TextHelper::instance()->getFileContent("template.h"))
            .arg(name())
            .arg(ret)
            .arg(name().toUpper())
            .arg(includeBlock)
            .arg(TextHelper::instance()->indent(privateBlock))
            .arg(baseType());

    return ret;
}

QString Class::cpp()
{
    QString ret;

    foreach (Method *m, methods) {
        if(!m->implement().isNull())
            ret.append(m->implement() + "\n\n");
    }

    ret = QString(TextHelper::instance()->getFileContent("template.cpp"))
            .arg(name())
            .arg(ret)
            .arg(name().toLower())
            .arg("")
            .arg(baseType());

    return ret;
}

QString Class::headerCode() const
{
    QString code = "";

    QString lastDecl = "public";
    QString ret;
    QString includeBlock;
    QString privateBlock;

    foreach (QString p, propertiesList)
        privateBlock.append(p + LB);
    privateBlock.append(LB);

    foreach (QString v, variables)
        privateBlock.append(v + LB);

    foreach (QString t, usedTypes) {
        if(t.startsWith("Q"))
            includeBlock.append("#include <" + t + ">" LB);
    }

    foreach (Method *m, methods) {
        if(m->declType() != lastDecl){
            ret.append("\n" + m->declType() + ":" LB);
            lastDecl = m->declType();
        }
        ret.append(TextHelper::instance()->indent(m->declare()) + LB);
    }

    code = QString("#ifndef %1" LB
                   "#define %1" LB
                   "" LB
                   "class %2 : public NoronHub" LB
                   "{" LB
                   "%4" LB
                   LB
                   "%3"  LB
                   "};" LB
                   "#endif // %1" LB)

            .arg(m_name.toUpper())
            .arg(name())
            .arg(ret)
            .arg(privateBlock);

    return code;
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
    cppFile.write(cpp().toUtf8());

    hFile.close();
    cppFile.close();
}

void Class::addProperty(QString type, QString name)
{
    properties.append(new Property(type, name, this));
}

void Class::addProperty(QString type, QString name, QString readMethod, QString writeMethod, QString notifySignal, QString fieldName)
{
    properties.append(new Property(type, name, readMethod, writeMethod, notifySignal, fieldName));
}

void Class::addProperty(Property *prop)
{
    properties.append(prop);
}

void Class::addMethod(Method *m)
{
    methods.append(m);
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
        return m_name.toLower() = ".cpp";

    return m_sourceFileName;
}

QString Class::headerFileName() const
{
    if(m_headerFileName.isNull())
        return m_name.toLower() = ".h";

    return m_headerFileName;
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

void Class::procLine(QString line)
{
    QList<Method*> methodsList;
    for(int i = 0; i < 8; i++)
        methodsList.append(new Method(this));

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

    foreach (Method *m, methodsList) {
        m->setName(name);
        m->setReturnType(returnType);
        m->setSeprator(sep);
        m->setSignature(params);
        m->setDeclType("public slots");
    }

    QStringList types = methodsList[0]->getParametereTypes().split(",");
    foreach (QString t, types)
        usedTypes.insert(t.trimmed());

    methodsList[METHOD_BYJSVALUE]->setWrapperMacro("QT_QML_LIB");
    methodsList[METHOD_BYFUNC]->setWrapperMacro("__cplusplus >= 201103L");

    setMethodCode(methodsList[METHOD_ASYNC],        "method_async");
    setMethodCode(methodsList[METHOD_BYFUNC],       "method_byfunc");
    setMethodCode(methodsList[METHOD_BYJSVALUE],    "method_byjsvalue");
    setMethodCode(methodsList[METHOD_BYMETAMETHOD], "method_bymetamethod");
    setMethodCode(methodsList[METHOD_BYSIGNAL],     "method_bysignal");
    setMethodCode(methodsList[METHOD_FRESH],        "method_fresh");
    setMethodCode(methodsList[METHOD_SLOT],         "method_slot");

    methodsList[METHOD_ASYNC]->setName(name + "Async");
    methodsList[METHOD_SLOT]->setName(name + "Slot");

    methodsList[METHOD_BYSIGNAL]->setSignature(params + sep + "const QObject *obj, char *callbackSlot");
    methodsList[METHOD_BYMETAMETHOD]->setSignature(params + sep + "const QObject *obj, const QMetaMethod *callbackMethod");
    methodsList[METHOD_BYFUNC]->setSignature(params + sep + "std::function<void(" + returnType + ")> callbackFunction");
    methodsList[METHOD_BYJSVALUE]->setSignature(params + sep + "QJSValue callbackFunction");

//    methodsList[METHOD_FRESH]->setIsInvokable(true);
//    methodsList[METHOD_ASYNC]->setIsInvokable(true);
//    methodsList[METHOD_BYJSVALUE]->setIsInvokable(true);

    methodsList[METHOD_SIGNAL]->setDeclType("signals");
    methodsList[METHOD_SIGNAL]->setName(name + "Signal");

    if(returnType != "void"){
        methodsList[METHOD_SIGNAL]->setSignature(params + sep + ", " + returnType + " returnValue");
    }

    usedTypes.insert(returnType);

    foreach (Method *m, methodsList)
        this->methods.append(m);
}

void Class::procProperty(QString line)
{
    line = line.trimmed();
    QRegularExpression regex("Q_PROPERTY\\((\\S+) (\\S+) READ (\\S+) WRITE (\\S+) NOTIFY (\\S+)\\)");
    QRegularExpressionMatch match = regex.match(line);

    line = line.replace(")", " USER true)");

    if(!match.hasMatch())
        return;

    propertiesList.append(line);

    QString type = match.captured(1);
    QString name = match.captured(2);
    QString read = match.captured(3);
    QString write = match.captured(4);
    QString notify = match.captured(5);

    variables.append(type + " m_" + name + ";");

    Method *readMethod = new Method(this);
    Method *writeMethod = new Method(this);
    Method *notifySignal = new Method(this);


    readMethod->setReturnType(type);
    writeMethod->setReturnType("void");
    notifySignal->setReturnType("void");

    writeMethod->setSignature(type + " " + name);
    notifySignal->setSignature(type + " " + name);

    readMethod->setDeclType("public");
    writeMethod->setDeclType("public slots");
    notifySignal->setDeclType("signals");

    readMethod->setName(read);
    writeMethod->setName(write);
    notifySignal->setName(notify);


    QString writeFileName = TextHelper::instance()->hasOperatorEqual(type) ? "property_write" : "property_write_nocheck";
    readMethod->setCode(TextHelper::instance()->getFileContent("property_read").arg(name));
    writeMethod->setCode(TextHelper::instance()->getFileContent(writeFileName).arg(name).arg(write));

    methods.append(readMethod);
    methods.append(writeMethod);
    methods.append(notifySignal);

    usedTypes.insert(type);
}

void Class::setMethodCode(Method *m, QString fileName)
{
    if(m->returnType() == "void")
        fileName.append("_void");

    QString code = TextHelper::instance()->getFileContent(fileName);


    if(code.isEmpty() || code.isNull()){
        m->setCode("//Error loading " + fileName);
    }else{
        code = code
                .replace("%1", m->name())
                .replace("%2", m->seprator())
                .replace("%3", m->getParametereNames())
                .replace("%4", m->returnType());
        m->setCode(code);
    }
}

