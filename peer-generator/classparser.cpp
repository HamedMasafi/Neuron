#include "classparser.h"

#include <QFile>
#include <QRegularExpression>

void ClassParser::replaceBlock(QString *content, QString blockName, QString (*callbackfunc)(QString))
{
    QRegularExpression regex(QString("#define BEGIN_%1(.*)#define END_%1")
                             .arg(blockName), QRegularExpression::DotMatchesEverythingOption);

    QRegularExpressionMatch match = regex.match(*content);

    QString s = callbackfunc(match.captured(1));

    content->replace(regex, s);
}

QString ClassParser::replaceMethod(QString block)
{

}

ClassParser::ClassParser(QObject *parent) : QObject(parent)
{
    QFile cppFile(":/template.cpp");
    QFile hFile(":/template.h");

    cppFile.open(QIODevice::ReadOnly);
    hFile.open(QIODevice::ReadOnly);

    cppTemplate = cppFile.readAll();
    hTemplate = hFile.readAll();
}

