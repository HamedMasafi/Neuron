#ifndef CLASSPARSER_H
#define CLASSPARSER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Class;
class Method;
class ClassParser : public QObject
{
    Q_OBJECT

    QString cppTemplate;
    QString hTemplate;

    void replaceBlock(QString *content, QString blockName, QString(*callbackfunc)(QString));

    QString replaceMethod(QString block);

public:
    explicit ClassParser(QObject *parent = 0);


    static Class *parse(QString templateCode);

private:
    static void procLine(Class *cls, QString line);
    static void procProperty(Class *cls, QString line);
    static void setMethodCode(Method *m, QString fileName);

signals:

public slots:
};

#endif // CLASSPARSER_H
