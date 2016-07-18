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

    QString joinSet(QSet<QString> set, QString seprator) const;

    void normalizeCode(QString &code);
    bool extractBlock(const QString &blockName, QString &code, QString &firstLine, QString &content);
signals:

public slots:
};

#endif // TEXTHELPER_H
