#include "class.h"
#include "classparser.h"
#include "method.h"
#include "texthelper.h"
#include "defines.h"
#include "property.h"
#include "enum.h"

#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

#define METHOD_SLOT             0
#define METHOD_FRESH            1
#define METHOD_ASYNC            2
#define METHOD_BYSIGNAL         3
#define METHOD_BYMETAMETHOD     4
#define METHOD_BYFUNC           5
#define METHOD_BYJSVALUE        6
#define METHOD_SIGNAL           7

#define NORON_PEER "NoronPeer"

ClassParser::ClassParser(QObject *parent) : QObject(parent)
{
    QFile cppFile(":/template.cpp");
    QFile hFile(":/template.h");

    cppFile.open(QIODevice::ReadOnly);
    hFile.open(QIODevice::ReadOnly);

    cppTemplate = cppFile.readAll();
    hTemplate = hFile.readAll();
}

void ClassParser::addClass(QString baseType, QString className, QString templateCode)
{
    ClassData *data = new ClassData;
    data->baseType = baseType;
    data->content = templateCode;
    data->name = className;

    classDataList.append(data);
}

void ClassParser::parseAll()
{
    foreach (ClassData *data, classDataList)
        data->classObject = parse(data->baseType, data->name, data->content);
}

QList<Class *> ClassParser::classes()
{
    QList<Class *> ret;
    foreach (ClassData *data, classDataList)
        ret.append(data->classObject);

    return ret;
}


Class *ClassParser::parse(QString baseType, QString className, QString templateCode)
{
    //    if(baseType == "NoronData")
    //        return parseData(className, templateCode);
    //    else
    return parsePeer(baseType, className, templateCode);
}

void ClassParser::procLine(Class *cls, QString line)
{

    QList<Method*> methodsList;
    for(int i = 0; i < 8; i++)
        methodsList.append(new Method(cls));

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

    /*foreach (QString t, types)
        usedTypes.insert(t.trimmed());
*/
    methodsList[METHOD_BYJSVALUE]->setWrapperMacro("QT_QML_LIB");
    methodsList[METHOD_BYFUNC]->setWrapperMacro("__cplusplus >= 201103L");

    setMethodCode(methodsList[METHOD_ASYNC],        "method_async");
    setMethodCode(methodsList[METHOD_BYFUNC],       "method_byfunc");
    setMethodCode(methodsList[METHOD_BYJSVALUE],    "method_byjsvalue");
    setMethodCode(methodsList[METHOD_BYMETAMETHOD], "method_bymetamethod");
    setMethodCode(methodsList[METHOD_BYSIGNAL],     "method_bysignal");
    setMethodCode(methodsList[METHOD_FRESH],        "method_fresh");
    if(cls->baseType() != NORON_PEER){
        methodsList[METHOD_SLOT]->setSignature("NoronPeer *senderPeer" + sep + params);
        setMethodCode(methodsList[METHOD_SLOT],         "method_slot_shared");
    }else{
        setMethodCode(methodsList[METHOD_SLOT],         "method_slot");
    }

    methodsList[METHOD_ASYNC]->setName(name + "Async");
    methodsList[METHOD_SLOT]->setName(name + "Slot");

    methodsList[METHOD_SLOT]->setIsVirtual(true);
    methodsList[METHOD_BYSIGNAL]->setIsInvokable(true);

    methodsList[METHOD_BYSIGNAL]->setSignature(params + sep + "const QObject *obj, char *callbackSlot");
    methodsList[METHOD_BYMETAMETHOD]->setSignature(params + sep + "const QObject *obj, const QMetaMethod *callbackMethod");
    methodsList[METHOD_BYFUNC]->setSignature(params + sep + "std::function<void(" + returnType + ")> callbackFunction");
    methodsList[METHOD_BYJSVALUE]->setSignature(params + sep + "QJSValue callbackFunction");


    //    methodsList[METHOD_FRESH]->setIsInvokable(true);
    //    methodsList[METHOD_ASYNC]->setIsInvokable(true);
    //    methodsList[METHOD_BYJSVALUE]->setIsInvokable(true);

    methodsList[METHOD_SIGNAL]->setDeclType("signals");
    methodsList[METHOD_SIGNAL]->setName(name + "Signal");

    if(returnType == "void"){
        methodsList[METHOD_SIGNAL]->setSignature(params);
    }else{
        methodsList[METHOD_SIGNAL]->setSignature(params + sep + returnType + " *returnValue");
        if(returnType.endsWith("*")){
//            methodsList[METHOD_SIGNAL]->setSignature(params + sep + returnType + " returnValue");
            methodsList[METHOD_SLOT]->setCode(methodsList[METHOD_SLOT]->code().replace("&ret", "ret")
                                              .arg(" = new " + returnType.replace("*", "")));
        }else{
//            methodsList[METHOD_SIGNAL]->setSignature(params);
//            if(cls->baseType() != NORON_PEER)
//                methodsList[METHOD_SIGNAL]->setSignature("NoronPeer *senderPeer " + sep + params + ", " + returnType + " *returnValue");
//            else
        }
    }

    if(cls->baseType() != NORON_PEER){
        if(methodsList[METHOD_SIGNAL]->signature().isEmpty())
            methodsList[METHOD_SIGNAL]->setSignature("NoronPeer *senderPeer");
        else
            methodsList[METHOD_SIGNAL]->setSignature("NoronPeer *senderPeer, " + methodsList[METHOD_SIGNAL]->signature());
    }

    //usedTypes.insert(returnType);

    foreach (Method *m, methodsList){
        if(m != methodsList[METHOD_FRESH] && m != methodsList[METHOD_SLOT])
            m->setReturnType("void");
        cls->addMethod(m);
    }

    includeUsedType(cls, returnType);

    QStringList types = methodsList[0]->getParametereTypes().split(",");
    foreach(QString t, types)
        includeUsedType(cls, t.trimmed().replace("*", ""));
}

bool ClassParser::includeUsedType(Class *cls, QString propType)
{
    propType = propType.replace("*", "");
    if(propType.startsWith("Q")){
        QRegularExpression r("(\\w+)\\<(\\w+)\\>");
        QRegularExpressionMatch m = r.match(propType);

        if(m.hasMatch()){
            includeUsedType(cls, m.captured(1));
            includeUsedType(cls, m.captured(2));
        }else{
            cls->addInclude(propType);
        }
        return true;
    }

    if(propType.endsWith("List"))
        propType =  propType.left(propType.length() - 4);

    foreach (ClassData *data, classDataList){
        if(data->name == propType){
            cls->addInclude(data->name.toLower() + ".h", true, false);
            return true;
        }
    }

    return false;
}

void ClassParser::procPropertyPeer(Class *cls, QString line, QString baseType)
{

    line = line.trimmed();
    QRegularExpression regex("Q_PROPERTY\\((\\S+) (\\S+) READ (\\S+) WRITE (\\S+) NOTIFY (\\S+)\\)");
    QRegularExpressionMatch match = regex.match(line);
    Property *prop = 0;

    if(match.hasMatch()){
        QString type = match.captured(1);
        QString name = match.captured(2);
        QString read = match.captured(3);
        QString write = match.captured(4);
        QString notify = match.captured(5);

        prop = new Property(type, name, read, write, notify, "m_" + name);
    }

    QRegularExpression regexShort("Q_PROPERTY\\(\\s*(\\S+)\\s+(\\S+)\\s*\\)");
    QRegularExpressionMatch matchShort = regexShort.match(line);
    if(matchShort.hasMatch()){
        QString type = matchShort.captured(1);
        QString name = matchShort.captured(2);

        prop = new Property(type, name);
    }


    cls->addVariable(prop->type() + " m_" + prop->name() + ";");
    cls->addBeginOfClass(prop->declareLine());

    Method *readMethod = new Method(cls);
    Method *writeMethod = new Method(cls);
    Method *notifySignal = new Method(cls);


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


    QString writeFileName = "property_write";
    if(baseType == QT_STRINGIFY(QObject))
        writeFileName.append("_noinvoke");
    if(!TextHelper::instance()->hasOperatorEqual(prop->type()))
        writeFileName.append("_nocheck");

    //QString writeFileName = TextHelper::instance()->hasOperatorEqual(prop->type()) ? "property_write" : "property_write_nocheck";
    readMethod->setCode(TextHelper::instance()->getFileContent("property_read")
                        .arg(prop->name()));

    writeMethod->setCode(TextHelper::instance()->getFileContent(writeFileName)
                         .arg(prop->name())
                         .arg(prop->writeMethodName())
                         .arg(prop->name()));

    cls->addMethod(readMethod);
    cls->addMethod(writeMethod);
    cls->addMethod(notifySignal);

    if(prop->type().startsWith("Q"))
        cls->addInclude(prop->type());
    else {
        if(includeUsedType(cls, prop->type()))
            writeMethod->setCode(TextHelper::instance()->getFileContent(writeFileName)
                                 .arg(prop->name())
                                 .arg(prop->writeMethodName())
                                 .arg("QVariant::fromValue(" + prop->name() + ")"));
    }
}

void ClassParser::procPropertyData(Class *cls, QString line)
{

    line = line.trimmed();
    QRegularExpression regex("Q_PROPERTY\\((\\S+) (\\S+) READ (\\S+) WRITE (\\S+) NOTIFY (\\S+)\\)");
    QRegularExpressionMatch match = regex.match(line);

    QString type;
    QString name;
    QString read;
    QString write;
    QString notify;

    Property *prop = 0;
    if(match.hasMatch()){
        type = match.captured(1);
        name = match.captured(2);
        read = match.captured(3);
        write = match.captured(4);
        notify = match.captured(5);

        prop = new Property(type, name, read, write, notify, "m_" + name);
    }

    QRegularExpression regexShort("Q_PROPERTY\\(\\s*(\\S+)\\s+(\\S+)\\s*\\)");
    QRegularExpressionMatch matchShort = regexShort.match(line);
    if(matchShort.hasMatch()){
        type = matchShort.captured(1);
        name = matchShort.captured(2);

        prop = new Property(type, name, cls);
        prop->setNotifySignalName("");
    }

    Method *readMethod = new Method(cls);
    Method *writeMethod = new Method(cls);


    readMethod->setReturnType(type);
    writeMethod->setReturnType("void");

    writeMethod->setSignature(type + " " + name);

    readMethod->setDeclType("public");
    writeMethod->setDeclType("public slots");

    readMethod->setName(prop->readMethodName());
    writeMethod->setName(prop->writeMethodName());

    readMethod->setCode(QString("return this->value(QT_STRINGIFY(%1)).value<%2>();" LB).arg(name).arg(type));
    writeMethod->setCode(QString("this->insert(QT_STRINGIFY(%1), %1);" LB).arg(name));

    cls->addMethod(readMethod);
    cls->addMethod(writeMethod);

    includeUsedType(cls, prop->type());
    //    cls->addProperty(prop);
}

void ClassParser::setMethodCode(Method *m, QString fileName)
{
    if(m->returnType() == "void")
        fileName.append("_void");

    QString code = TextHelper::instance()->getFileContent(fileName);
    QString params = m->getParametereNames();

    if(!fileName.contains("_slot") && !params.trimmed().isEmpty())
        params = "QVariant::fromValue(" + params.replace(" ", "").replace(",", "), QVariant::fromValue(") + ")";

    if(code.isEmpty() || code.isNull()){
        m->setCode("//Error loading " + fileName);
    }else{
        code = code
                .replace("%1", m->name())
                .replace("%2", m->seprator())
                .replace("%3", params)
                .replace("%4", m->returnType());
        m->setCode(code);
    }
}

void ClassParser::addPropertyToClass(Class *cls, Property *prop)
{

}

void ClassParser::addQmlRegisterMethods(Class *cls)
{
    Method *createSingleton = new Method(cls);
    createSingleton->setIsExtern(true);
    createSingleton->setReturnType("QObject*");
    createSingleton->setSignature("QQmlEngine *, QJSEngine *");
    createSingleton->setName("create_singelton_object");
    createSingleton->setCode("return new " + cls->name() + "();");
    createSingleton->setWrapperMacro("QT_QML_LIB");
    cls->addMethod(createSingleton);

    Method *registerSingleton = new Method(cls);
//    QString classJsName = cls->name();
//    classJsName[0] = classJsName[0].toLower();
    registerSingleton->setName("registerQmlSingleton");
    registerSingleton->setReturnType("int");
    registerSingleton->setIsStatic(true);
    registerSingleton->setDeclType("public");
    registerSingleton->setSignature("const char *uri, int versionMajor, int versionMinor");
    registerSingleton->setCode(QString("return qmlRegisterSingletonType<%1>(uri, versionMajor, versionMinor, \"%1\", create_singelton_object);")
                               .arg(cls->name()));//.arg(classJsName));
    registerSingleton->setWrapperMacro("QT_QML_LIB");
    cls->addMethod(registerSingleton);

    Method *registerQml = new Method(cls);
    registerQml->setName("registerQml");
    registerQml->setReturnType("int");
    registerQml->setIsStatic(true);
    registerQml->setDeclType("public");
    registerQml->setSignature("const char *uri, int versionMajor, int versionMinor");
    registerQml->setCode(QString("return qmlRegisterType<%1>(uri, versionMajor, versionMinor, \"%1\");")
                         .arg(cls->name()));
    registerQml->setWrapperMacro("QT_QML_LIB");
    cls->addMethod(registerQml);

    //    cls->addInclude("QQmlEngine", false, true, "ifdef QT_QML_LIB");
    //    cls->addInclude("QJSEngine", false, true, "ifdef QT_QML_LIB");
    cls->addInclude("QtQml", false, true, "ifdef QT_QML_LIB", false);
}

Class *ClassParser::parsePeer(QString baseType, QString className, QString templateCode)
{
    Class *cls = new Class;
    cls->setName(className);

//    if(baseType == "QObject")
//        cls->setBaseType(QT_STRINGIFY(QObject));
//    else
        cls->setBaseType(baseType);

    cls->addBeginOfClass("Q_OBJECT");

    cls->addInclude("functional", true, true, "if __cplusplus >= 201103L");
    cls->addInclude("QJSValue", true, true, "ifdef QT_QML_LIB");
    cls->addInclude("NoronAbstractHub");

    QString firstLine;
    QString content;
    while(TextHelper::instance()->extractBlock("enum", templateCode, firstLine, content)){
        Enum *e = new Enum(firstLine.replace("enum ", ""), content);
        cls->addEnum(e);
    }

//    QRegularExpression enumRegex("enum\\s+(?<name>\\S+)\\s*\\{(?<content>[^}])*\\};"/*,
//                                 QRegularExpression::MultilineOption | QRegularExpression::DotMatchesEverythingOption*/);
//    QRegularExpressionMatchIterator matchs = enumRegex.globalMatch(templateCode);
//    while (matchs.hasNext()) {
//        QRegularExpressionMatch match = matchs.next();
//        templateCode = templateCode.replace(match.captured(), "");
////        cls->addBeginOfClass(match.captured() + "};" LB + "Q_ENUM(" + match.captured(1) + ")" LB);
//        qDebug() << "enum found" << match.captured();
//        Enum *e = new Enum(match.captured("name"), match.captured("content"));
//        cls->addEnum(e);
//    }

    QStringList lines = templateCode.split("\n");

    Method *constructor = new Method(cls);
    constructor->setName(cls->name());
    constructor->setIsInvokable(true);
    constructor->setSignature("QObject *parent = 0");
    constructor->setReturnType("");
    constructor->setDeclType("public");
    constructor->setInheristanceDeclare(cls->baseType() + "(parent)");
    cls->addMethod(constructor);

    Method *peerNameMethod = new Method(cls);
    peerNameMethod->setName("peerName");
    peerNameMethod->setReturnType(QT_STRINGIFY(const QString));
    peerNameMethod->setCode(QString("return QString(\"%1\");").arg(cls->name()));
    peerNameMethod->setDeclType("public");
    cls->addMethod(peerNameMethod);

    if(baseType == "QObject"){
        cls->addAfterClass(QString("typedef QList<%1*> %1List;").arg(className));
    }else{
        cls->addInclude(baseType);

        Method *constructor2 = new Method(cls);
        constructor2->setName(cls->name());
        constructor2->setSignature("NoronAbstractHub *hub, QObject *parent = 0");
        constructor2->setReturnType("");
        constructor2->setDeclType("public");

        if(baseType == NORON_PEER)
            constructor2->setCode("if(hub)" LB
                                  "setHub(hub);");
        else
            constructor2->setCode("if(hub){" LB
                                  "setHub(hub);" LB
                                  "hub->addSharedObject(this);" LB
                                  "}");

        constructor2->setInheristanceDeclare(cls->baseType() + "(parent)");
        cls->addMethod(constructor2);

    }
    addQmlRegisterMethods(cls);

    foreach (QString line, lines) {
        line = line.trimmed();

        if(line.startsWith("//"))
            continue;

        if(line.startsWith("Q_PROPERTY"))
            procPropertyPeer(cls, line, baseType);
        else
            procLine(cls, line);
    }

    return cls;
}

Class *ClassParser::parseData(QString className, QString templateCode)
{
    Class *cls = new Class;
    cls->setName(className);
    cls->setBaseType(QT_STRINGIFY(QVariantMap));

    cls->addBeginOfClass("Q_GADGET");
    cls->addAfterClass(QString("typedef QList<%1> %1List;").arg(className));

    cls->addAfterNamespace(QString("Q_DECLARE_METATYPE(%1)").arg(className));
    cls->addAfterNamespace(QString("Q_DECLARE_METATYPE(%1List)").arg(className));

    cls->addInclude("functional", true, true, "if __cplusplus >= 201103L");
    cls->addInclude("QJSValue", true, true, "ifdef QT_QML_LIB");
    cls->addInclude("NoronAbstractHub");
    cls->addInclude("QVariantMap");

    QStringList lines = templateCode.split("\n");

    Method *constructor = new Method(cls);
    constructor->setName(cls->name());
    constructor->setSignature("");
    constructor->setReturnType("");
    constructor->setDeclType("public");
    //    constructor->setInheristanceDeclare();

    cls->addMethod(constructor);

    addQmlRegisterMethods(cls);

    foreach (QString line, lines) {
        line = line.trimmed();

        if(line.startsWith("//"))
            continue;

        if(line.startsWith("Q_PROPERTY"))
            procPropertyData(cls, line);
        else
            procLine(cls, line);
    }

    return cls;
}

