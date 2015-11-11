#ifndef CLASS_H
#define CLASS_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QList>
#include <QSet>
#include <QStringList>

class Method;
class Class : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    QStringList properties;
    QStringList variables;
    QSet<QString> usedTypes;
    QList<Method*> methods;

public:
    explicit Class(QObject *parent = 0);

    void parse(QString templateCode);
    QString h();
    QString cpp();

    void save(QString dir);

    QString name() const;

public slots:
    void setName(QString name);

signals:
    void nameChanged(QString name);

private:
    void procLine(QString line);
    void procProperty(QString line);
    QString m_name;
    void setMethodCode(Method *m, QString fileName);
};

#endif // CLASS_H
