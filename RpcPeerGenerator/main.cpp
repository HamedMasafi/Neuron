#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include <QMetaMethod>
#include <QDir>
#include <QCommandLineParser>

using namespace std;

QHash<QString, QString> files;


QString implements;
QHash<QString, QString> methodDecls;
QHash<QString, QString> variables;
QStringList properties;
QString className;


QString getParametereNames(QString signature){
    QString s = signature;
    qDebug() << "before "<< s;
    s.replace(QRegularExpression("(,|^)\\s*\\S+\\s*\\*?"), "\\1");
    qDebug() << "after "<< s;
    return s;
}

QString getParametereTypes(QString signature){
    QString s = signature;
    s.replace(QRegularExpression("(\\*)?(\\S*)\\s*(,|$)"), "\\1");
    return s;
}

QString generate_cpp(){
    QString ret;

    ret = files["implement"];
    ret = ret
            .replace("%NAME%", className)
            .replace("%HEADER_FILE%", className.toLower());

    ret.append(implements);

    return ret;
}

QString generate_h(){
    QString ret;

    ret.append(QString(files["header"]).arg(className).arg(className.toUpper()));

    foreach (QString s, properties) {
        ret.append("    " + s + "\n");
    }

    ret.append("\n");

    QHashIterator<QString, QString> i(variables);
    while (i.hasNext()) {
        i.next();
        ret.append("    " + i.value() + " " + i.key() + ";\n");
    }


    foreach (QString key, methodDecls.keys()) {
        ret.append("\n" + key + ":\n");
        ret.append(methodDecls[key]);
    }

    ret.append("};\n");
    ret.append("#endif // " + className.toUpper() + "_H\n");
    return ret;
}

void writeToFile(QString content, QString filePath){
    QFile file(filePath);
    file.open(QIODevice::WriteOnly);
    file.write(content.toUtf8());
    file.close();
}

QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}

void procProperty(QString line){
    QRegularExpression regex("Q_PROPERTY\\((\\S+) (\\S+) READ (\\S+) WRITE (\\S+) NOTIFY (\\S+)\\)");
    QRegularExpressionMatch match = regex.match(line);

    if(!match.hasMatch())
        return;

    properties.append(line);

    QString type = match.captured(1);
    QString name = match.captured(2);
    QString read = match.captured(3);
    QString write = match.captured(4);
    QString notify = match.captured(5);

    variables.insert("m_" + name, type);

    QString buffer = files["implement_property"];

    buffer
            .replace("%NAME%", name)
            .replace("%WRITE_NAME%", write)
            .replace("%READ_NAME%", read)
            .replace("%NOTIFY_NAME%", notify)
            .replace("%CLASS_NAME%", className)
            .replace("%TYPE%", type);

    implements.append(buffer);
    methodDecls["public slots"].append(QString("    void %1(%2 %3);\n")
                                       .arg(write)
                                       .arg(type)
                                       .arg(name));
    methodDecls["public"].append(QString("    %1 %2() const;\n")
                                 .arg(type).arg(read));

    methodDecls["signals"].append(QString("    void %1();\n").arg(notify));
}

void procLine(QString line){
    QRegularExpression regex("(\\S+)\\s+(\\S+)\\((.*)\\);");
    QRegularExpressionMatch match = regex.match(line);

    if(!match.hasMatch())
        return;

    QString type = match.captured(1);
    QString name = match.captured(2);
    QString params = match.captured(3);

    QString sep = "";
    if(params.trimmed() != "")
        sep.append(", ");

    QString signNames = getParametereNames(params);
    QString signTypes = getParametereTypes(params);

    QString buffer;
    if(type == "void"){
        buffer = files["implement_func_void"];
        methodDecls["signals"].append(QString("    void %1Handle(%2);\n")
                                      .arg(name)
                                      .arg(params));
    }else{
        buffer = files["implement_func"];
        methodDecls["signals"].append(QString("    void %1Handle(%2%3%4);\n")
                                      .arg(name)
                                      .arg(params)
                                      .arg(sep)
                                      .arg(type + " *result"));
    }

    buffer
            .replace("%CLASS_NAME%", className)
            .replace("%NAME%", name)
            .replace("%TYPE%", type)
            .replace("%SEP%", sep)
            .replace("%SIGN%", params)
            .replace("%SIGN_NAME%", signNames)
            .replace("%SIGN_TYPE%", signTypes);

    implements.append(buffer);

    buffer = files["header_func"];
    buffer
            .replace("%NAME%", name)
            .replace("%TYPE%", type)
            .replace("%CLASS_NAME%", className)
            .replace("%SEP%", sep)
            .replace("%SIGN%", params)
            .replace("%SIGN_NAME%", signNames)
            .replace("%SIGN_TYPE%", signTypes);


    methodDecls["public slots"].append(buffer);
}

void readClass(QString name, QString content){
    className = name;
    methodDecls["public"].append("    Q_INVOKABLE " + className + "(QObject *parent = 0);\n");
    QStringList lines = content.split("\n");

    foreach (QString line, lines) {
        line = line.trimmed();

        if(line.startsWith("//"))
            continue;

        if(line.startsWith("Q_PROPERTY"))
            procProperty(line);
        else
            procLine(line);
    }

    writeToFile(generate_h(), className.toLower() + ".h");
    writeToFile(generate_cpp(), className.toLower() + ".cpp");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(a.applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("Template file", "Source file to process.");

    QCommandLineOption targetOption(QStringList() << "t" << "target", "Target dictionary.");
    parser.addOption(targetOption);

    QCommandLineOption createProjectOption(QStringList() << "p" << "project", "Create project.");
    parser.addOption(createProjectOption);

    parser.process(a);

    const QStringList args = parser.positionalArguments();

    if(args.isEmpty()){
        qStdOut() << parser.helpText() << endl;
        return EXIT_SUCCESS;
    }

    QString templateFileName = args.first();
    if(!QFile(templateFileName).exists()){
        qStdOut() << "The file " << templateFileName << " deos not exists." << endl;
        return EXIT_SUCCESS;
    }

    QFile f(templateFileName);
    f.open(QIODevice::ReadOnly);
    QString fileContent = f.readAll();

    QDir rDir(":/snippets");
    QStringList resfiles = rDir.entryList();
    foreach (QString file, resfiles) {
        QFile fres(":/snippets/" + file);
        fres.open(QIODevice::ReadOnly);
        files.insert(file, fres.readAll());
        qDebug() << file;
        fres.close();
    }

    QRegularExpression classRegex("class\\s+(\\S+)\\s*\\{([^}]*)\\}", QRegularExpression::DotMatchesEverythingOption);
//    QRegularExpressionMatch match = classRegex.match(fileContent);

//    if(!match.hasMatch())
//        return EXIT_SUCCESS;

//    readClass(
//                match.captured(1),
//                match.captured(2));
    QRegularExpressionMatchIterator i = classRegex.globalMatch(fileContent);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        qDebug() << "Reading class"<<match.captured(1);
        methodDecls.clear();
        variables.clear();
        properties.clear();
        implements = QString();

        readClass(
                    match.captured(1),
                    match.captured(2));
    }

    return EXIT_SUCCESS;
}

