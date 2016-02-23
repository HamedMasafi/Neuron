#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include <QMetaMethod>
#include <QDir>
#include <QCommandLineParser>

#include "class.h"
#include "classparser.h"

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

    QRegularExpression classRegex("class\\s+(?<type>MAIN\\s+)?(?<name>\\S+)\\s*(:\\s*(?<base_type>\\S+))?\\s*\\{(?<content>[^}]*)\\}", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator i = classRegex.globalMatch(fileContent);
    QString savePath = parser.value(targetOption);

    int peersCount = 0;
    int sharedObjectsCount = 0;

    QHash<QString, QString> classesCode;
//    QList<Class*> classes;

    ClassParser classParser;
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();

        QString baseType = match.captured("base_type");
        if(baseType.isEmpty())
            baseType = "NoronSharedObject";


        if(baseType == "NoronPeer")
            peersCount++;

        classesCode.insert(match.captured("name"), match.captured("content"));

        classParser.addClass(baseType,
                             match.captured("name"),
                             match.captured("content"));

    }
    classParser.parseAll();

//    if(peersCount == 0 && classes.count() != 0){
//        classes[0]->setBaseType("NoronPeer");
//        peersCount++;
//    }

    foreach (Class *cls, classParser.classes()) {
        cls->save(savePath);

        qStdOut() << "The class " << cls->name() << " created in two files:\n";
        qStdOut() << "\t -" << (savePath + "/" + cls->headerFileName() + "\n");
        qStdOut() << "\t -" << (savePath + "/" + cls->sourceFileName() + "\n\n");
    }

    qStdOut() << "Job end. " << peersCount << " peer(s) and " << sharedObjectsCount << " shared object(s) are created.\n\n";

    return EXIT_SUCCESS;
}

