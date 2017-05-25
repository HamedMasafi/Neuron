#include "defines.h"

#include "enum.h"

Enum::Enum(QString name, QString content) : _name(name), _lines(content)
{
//    _name = name;
//    QStringList ls = content.split('\n');
//    foreach (QString l, ls)
//        _lines.append(l.replace("\r", "").trimmed());
}

QString Enum::toString()
{
    return QString("enum %1{" LB "%2};" LB "Q_ENUM(%1)")
            .arg(_name)
            .arg(_lines);
}
