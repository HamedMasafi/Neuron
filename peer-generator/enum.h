#ifndef ENUM_H
#define ENUM_H

#include <QtCore/qglobal.h>
#include <QStringList>

class Enum
{
    QString _name;
    QString _lines;

public:
    Enum(QString name, QString content);
    QString toString();
};

#endif // ENUM_H
