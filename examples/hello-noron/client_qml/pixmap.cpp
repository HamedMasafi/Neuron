#include "pixmap.h"

#include <QPainter>
#include <QPixmap>

Pixmap::Pixmap(QQuickItem *parent) : QQuickPaintedItem(parent)
{

}

QPixmap Pixmap::pixmap() const
{
    return m_pixmap;
}

void Pixmap::paint(QPainter *painter)
{
    painter->drawPixmap(0, 0, m_pixmap);
}

QJSValue Pixmap::jsvalue() const
{
    return m_jsvalue;
}

QVariant Pixmap::pixmapVariant() const
{
    return m_pixmapVariant;
}

void Pixmap::load(QUrl fileUrl)
{
    m_pixmap.load(fileUrl.toLocalFile());
    m_pixmapVariant = QVariant(m_pixmap);
}

void Pixmap::setPixmap(QPixmap pixmap)
{
    //    if (m_pixmap == pixmap)
    //        return;

    m_pixmap = pixmap;
    emit pixmapChanged(pixmap);
}

void Pixmap::setJsvalue(QJSValue jsvalue)
{
//    if (m_jsvalue == jsvalue)
//        return;



    if(jsvalue.toVariant().type() == QVariant::Pixmap)
        m_pixmap = jsvalue.toVariant().value<QPixmap>();

    m_jsvalue = jsvalue;
    emit jsvalueChanged(jsvalue);
}

void Pixmap::setPixmapVariant(QVariant pixmapVariant)
{
//    if (m_pixmapVariant == pixmapVariant)
//        return;

    if(pixmapVariant.type() == QVariant::Pixmap)
        m_pixmap = pixmapVariant.value<QPixmap>();

    m_pixmapVariant = pixmapVariant;
    emit pixmapVariantChanged(pixmapVariant);
}

