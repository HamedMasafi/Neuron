#ifndef CLASSPARSER_H
#define CLASSPARSER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Class;
class Property;
class Method;
class ClassParser : public QObject
{
    Q_OBJECT

    QString cppTemplate;
    QString hTemplate;

public:
    explicit ClassParser(QObject *parent = 0);

    struct ClassData{
        QString name;
        QString baseType;
        QString content;
        Class *classObject = 0;
    };
    QList<ClassData*> classDataList;

    void addClass(QString baseType, QString className, QString templateCode);
    void parseAll();
    QList<Class *> classes();


    bool includeUsedType(Class *cls, QString propType);

    void addQmlRegisterMethods(Class *cls);

private:
    void procLine(Class *cls, QString line);
    void procPropertyPeer(Class *cls, QString line, QString baseType);
    void procPropertyData(Class *cls, QString line);

    void setMethodCode(Method *m, QString fileName);
    void addPropertyToClass(Class *cls, Property *prop);

    Class *parsePeer(QString baseType, QString className, QString templateCode);
    Class *parseData(QString className, QString templateCode);

    Class *parse(QString baseType, QString className, QString templateCode);

signals:

public slots:
};

#endif // CLASSPARSER_H
