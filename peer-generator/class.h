#ifndef CLASS_H
#define CLASS_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QList>
#include <QSet>
#include <QStringList>

class Method;
class Property;
class Enum;
class Class : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString baseType READ baseType WRITE setBaseType NOTIFY baseTypeChanged)
    Q_PROPERTY(QString sourceFileName READ sourceFileName WRITE setSourceFileName NOTIFY sourceFileNameChanged)
    Q_PROPERTY(QString headerFileName READ headerFileName WRITE setHeaderFileName NOTIFY headerFileNameChanged)
    Q_PROPERTY(QString headerIncludeBlockCode READ headerIncludeBlockCode)
    Q_PROPERTY(QString sourceIncludeBlockCode READ sourceIncludeBlockCode)
    Q_PROPERTY(QString nameSpace READ nameSpace WRITE setNameSpace NOTIFY nameSpaceChanged)

    QStringList propertiesList;
    QStringList variables;
    QStringList declaredClasses;
    QSet<QString> usedTypes;
    QList<Method*> methods;
    QList<Method*> constructors;
    QList<Property*> properties;
    QList<Enum*> enums;

    QSet<QString> m_headerIncludeBlockCode;
    QSet<QString> m_sourceIncludeBlockCode;

    QSet<QString> afterNameSpace;
    QString afterClass;
    QString beginOfClass;
public:
    explicit Class(QObject *parent = 0);

    QString headerCode() const;
    QString sourceCode() const;

    void save(QString dir);

    void addProperty(QString type, QString name);
    void addProperty(QString type, QString name, QString readMethod, QString writeMethod, QString notifySignal, QString fieldName);
    void addProperty(Property *prop);
    void addMethod(Method *m);
    void addConstructor(Method *m);
    void addVariable(QString declareLine);
    void addEnum(Enum *e);

    void addInclude(QString fileName, bool putInHeader = true, bool isGlobal = true, QString wrapperMacro = QString::null, bool isClass = true);

    void addBeginOfClass(QString line);
    void addAfterClass(QString line);
    void addAfterNamespace(QString line);

    void addPrivateVariable(QString type, QString name);

    QString name() const;
    QString baseType() const;
    QString sourceFileName() const;
    QString headerFileName() const;
    QString headerIncludeBlockCode() const;
    bool wrapQtNamespace() const;
    QString sourceIncludeBlockCode() const;
    QString nameSpace() const;

public slots:
    void setName(QString name);    
    void setBaseType(QString baseType);
    void setSourceFileName(QString sourceFileName);
    void setHeaderFileName(QString headerFileName);
    void setNameSpace(QString nameSpace);

signals:
    void nameChanged(QString name);    
    void baseTypeChanged(QString baseType);
    void sourceFileNameChanged(QString sourceFileName);
    void headerFileNameChanged(QString headerFileName);
    void headerIncludeBlockCodeChanged(QString headerIncludeBlockCode);
    void sourceIncludeBlockCodeChanged(QString sourceIncludeBlockCode);
    void nameSpaceChanged(QString nameSpace);

private:
    void setMethodCode(Method *m, QString fileName);

    QString m_name;
    QString m_baseType;
    QString m_sourceFileName;
    QString m_headerFileName;
//    QString m_headerIncludeBlockCode;
//    QString m_sourceIncludeBlockCode;
    QString m_nameSpace;
};

#endif // CLASS_H
