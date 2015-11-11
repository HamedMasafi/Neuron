#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include <QMetaMethod>
#include <QDir>
#include <QCommandLineParser>

#include "class.h"

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

    QRegularExpression classRegex("class\\s+(\\S+)\\s*\\{([^}]*)\\}", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator i = classRegex.globalMatch(fileContent);
    QString savePath = parser.value(targetOption);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        Class cls;
        cls.setName(match.captured(1));
        cls.parse(match.captured(2));
        cls.save(savePath);

        qStdOut() << "The class " << cls.name() << " created in two files:\n";
        qStdOut() << "\t -" << (savePath + "/" + cls.name().toLower() + ".h\n");
        qStdOut() << "\t -" << (savePath + "/" + cls.name().toLower() + ".cpp\n\n");
    }

    return EXIT_SUCCESS;
}

