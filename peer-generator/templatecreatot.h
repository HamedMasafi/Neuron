#ifndef TEMPLATECREATOT_H
#define TEMPLATECREATOT_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include <QMap>

class TemplateCreator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)

    QMap<QString, QString (*)(QString)> blockMaps;
    QMap<QString, QString> globalVariables;

public:
    explicit TemplateCreator(QObject *parent = 0);


    void generate();
    void setVariable(QString &content, QString &variableName, QString &variableValue);
    void registerBlock(QString blockName,
                       QString (*method) (QString));

    QString content() const;

public slots:
    void setContent(QString content);

signals:
    void contentChanged(QString content);

private:
    QString findFirstBlockName(QString &content);
    void findBlock(QString &content, QString blockName, int &begin, int &lenght);
    QString m_content;
    QString processBlock(QString &content, QString blockName);
};

#endif // TEMPLATECREATOT_H
