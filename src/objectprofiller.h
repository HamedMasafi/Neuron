#ifndef OBJECTPROFILLER_H
#define OBJECTPROFILLER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class ObjectProfiller : public QObject
{
    Q_OBJECT
public:
    explicit ObjectProfiller(QObject *parent = 0);

signals:

public slots:
};

#endif // OBJECTPROFILLER_H