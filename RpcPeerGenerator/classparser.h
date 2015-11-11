#ifndef CLASSPARSER_H
#define CLASSPARSER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class ClassParser : public QObject
{
    Q_OBJECT
public:
    explicit ClassParser(QObject *parent = 0);

signals:

public slots:
};

#endif // CLASSPARSER_H
