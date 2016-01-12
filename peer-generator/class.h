#ifndef CLASS_H
#define CLASS_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QList>
#include <QSet>
#include <QStringList>

class Method;
class Property;
class Class : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString baseType READ baseType WRITE setBaseType NOTIFY baseTypeChanged)
    Q_PROPERTY(QString sourceFileName READ sourceFileName WRITE setSourceFileName NOTIFY sourceFileNameChanged)
    Q_PROPERTY(QString headerFileName READ headerFileName WRITE setHeaderFileName NOTIFY headerFileNameChanged)

    QStringList propertiesList;
    QStringList variables;
    QSet<QString> usedTypes;
    QList<Method*> methods;
    QList<Property*> properties;

public:
    explicit Class(QObject *parent = 0);

    void parse(QString templateCode);
    QString h();
    QString cpp();

    QString headerCode() const;

    void save(QString dir);

    void addProperty(QString type, QString name);
    void addProperty(QString type, QString name, QString readMethod, QString writeMethod, QString notifySignal, QString fieldName);
    void addProperty(Property *prop);
    void addMethod(Method *m);

    QString name() const;
    QString baseType() const;
    QString sourceFileName() const;
    QString headerFileName() const;

public slots:
    void setName(QString name);    
    void setBaseType(QString baseType);
    void setSourceFileName(QString sourceFileName);
    void setHeaderFileName(QString headerFileName);

signals:
    void nameChanged(QString name);    
    void baseTypeChanged(QString baseType);

    void sourceFileNameChanged(QString sourceFileName);

    void headerFileNameChanged(QString headerFileName);

private:
    void procLine(QString line);
    void procProperty(QString line);
    QString m_name;
    void setMethodCode(Method *m, QString fileName);
    QString m_baseType;
    QString m_sourceFileName;
    QString m_headerFileName;
};

#endif // CLASS_H
