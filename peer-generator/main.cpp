#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include <QMetaMethod>
#include <QDir>
#include <QCommandLineParser>

#include "class.h"
#include "classparser.h"
#include "texthelper.h"

//TODO: code cleanup for this roject is needed
using namespace std;

QTextStream& qStdOut()
{
    static QTextStream ts( stdout );
    return ts;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("Rpc peer generator utility");
    a.setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription(a.applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("Template file", "Source file to process.");

    QCommandLineOption targetOption(QStringList() << "t" << "target", "Target dictionary.");
    targetOption.setDefaultValue(QDir::currentPath());
    parser.addOption(targetOption);

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
    f.close();

    TextHelper::instance()->normalizeCode(fileContent);

    QString firstLine;
    QString content;
    QHash<QString, QString> classesCode;
    ClassParser classParser;
    int len = fileContent.length();
    while(TextHelper::instance()->extractBlock("class", fileContent, firstLine, content)){
//        qDebug() << firstLine << content;
        if(len == fileContent.length())
            qFatal("Len equal");
        firstLine = firstLine
                .replace("class ", "")
                .replace("public ", "");
        QStringList parts = firstLine.split(":");
        if(parts.length() != 2){
            qFatal("Syntax error at: %s", qPrintable(firstLine));
            return EXIT_SUCCESS;
        }

        classesCode.insert(parts.at(0).trimmed(), content);

        classParser.addClass(parts.at(1).trimmed(),
                             parts.at(0).trimmed(),
                             content);
//        qInfo("%s", qPrintable(content));
    }


//    QRegularExpression classRegex("class\\s+(?<type>MAIN\\s+)?(?<name>\\S+)\\s*(:\\s*(?<base_type>\\S+))?\\s*\\{(?<content>[^}]*)\\}[^;]", QRegularExpression::DotMatchesEverythingOption);
//    QRegularExpressionMatchIterator i = classRegex.globalMatch(fileContent);
    QString savePath = parser.value(targetOption);

    QRegularExpression namespaceRegex("namespace\\s+(\\S+)", QRegularExpression::DotMatchesEverythingOption);
    QString namespaceStr = namespaceRegex.match(fileContent).captured(1);

    int peersCount = 0;
    int sharedObjectsCount = 0;

    classParser.parseAll();

//    if(peersCount == 0 && classes.count() != 0){
//        classes[0]->setBaseType("NoronPeer");
//        peersCount++;
//    }

    foreach (Class *cls, classParser.classes()) {
        cls->setNameSpace(namespaceStr);
        cls->save(savePath);

        qStdOut() << "The class " << cls->name() << " created in two files:\n";
        qStdOut() << "\t -" << (savePath + "/" + cls->headerFileName() + "\n");
        qStdOut() << "\t -" << (savePath + "/" + cls->sourceFileName() + "\n\n");
    }

    qStdOut() << "Job end. " << peersCount << " peer(s) and " << sharedObjectsCount << " shared object(s) are created.\n\n";

    return EXIT_SUCCESS;
}

