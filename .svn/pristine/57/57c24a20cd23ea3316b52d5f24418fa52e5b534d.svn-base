#ifndef CLASS_H
#define CLASS_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Class : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit Class(QObject *parent = 0);

    void parse(QString templateCode);

    QString name() const;

public slots:
    void setName(QString name);

signals:
    void nameChanged(QString name);

private:
    void procLine(QString line);
    QString m_name;
};

#endif // CLASS_H
