#ifndef CLASSPARSER_H
#define CLASSPARSER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class ClassParser : public QObject
{
    Q_OBJECT

    QString cppTemplate;
    QString hTemplate;

    void replaceBlock(QString *content, QString blockName, QString(*callbackfunc)(QString));

    QString replaceMethod(QString block);

public:
    explicit ClassParser(QObject *parent = 0);

signals:

public slots:
};

#endif // CLASSPARSER_H
