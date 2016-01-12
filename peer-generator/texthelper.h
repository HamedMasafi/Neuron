#ifndef TEXTHELPER_H
#define TEXTHELPER_H

#include <QObject>
#include <QHash>

class TextHelper : public QObject
{
    Q_OBJECT
    QHash<QString, QString> files;

public:
    explicit TextHelper(QObject *parent = 0);
    ~TextHelper();

    static TextHelper *instance();

    QString getFileContent(QString fileName);
    QString indent(QString text);

    bool hasOperatorEqual(QString type);
signals:

public slots:
};

#endif // TEXTHELPER_H
