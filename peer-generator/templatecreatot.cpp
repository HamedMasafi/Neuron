#include "templatecreatot.h"

#include <QRegularExpression>

TemplateCreator::TemplateCreator(QObject *parent) : QObject(parent)
{

}

void TemplateCreator::generate()
{
    QString globalBlock;

    while(!(globalBlock = findFirstBlockName(m_content)).isNull()){

    }
}

void TemplateCreator::setVariable(QString &content, QString &variableName, QString &variableValue)
{
    QRegularExpression r(QString("<%1\/>").arg(variableName));
    content.replace(r, variableValue);
}

void TemplateCreator::registerBlock(QString blockName, QString (*method)(QString))
{
    blockMaps.insert(blockName, method);
}

QString TemplateCreator::content() const
{
    return m_content;
}

void TemplateCreator::setContent(QString content)
{
    if (m_content == content)
        return;

    m_content = content;
    emit contentChanged(content);
}

QString TemplateCreator::findFirstBlockName(QString &content)
{
    QRegularExpression r("<(\\w+)>");
    QRegularExpressionMatch m = r.match(content);

    if(m.hasMatch())
        return m.captured(1);
    else
        return QString::null;
}

void TemplateCreator::findBlock(QString &content, QString blockName, int &begin, int &lenght)
{
    QRegularExpression r(QString("<%1>(.*)<\/%1>").arg(blockName));
    QRegularExpressionMatch m = r.match(content);

    if(m.hasMatch()){
        begin = m.capturedStart();
        lenght = m.capturedLength();
    }else{
        begin = lenght = 0;
    }
}

QString TemplateCreator::processBlock(QString &content, QString blockName)
{
    int begin, lenght;
    findBlock(content, blockName, begin, lenght);

    QString block;

    while(!(block = findFirstBlockName(m_content)).isNull()){
        findBlock(content, blockName, begin, lenght);

        QString blockContent = content.remove(begin, lenght);

        if(blockMaps.contains(block)){
            blockMaps[block](blockContent);
        }

    }
}

