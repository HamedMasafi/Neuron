#ifndef PIXMAP_H
#define PIXMAP_H

#include <QtCore/qglobal.h>
#include <QQuickPaintedItem>
#include <QPixmap>
#include <QJSValue>

class Pixmap : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap NOTIFY pixmapChanged)
    Q_PROPERTY(QJSValue jsvalue READ jsvalue WRITE setJsvalue NOTIFY jsvalueChanged)
    Q_PROPERTY(QVariant pixmapVariant READ pixmapVariant WRITE setPixmapVariant NOTIFY pixmapVariantChanged)

    QPixmap m_pixmap;
    QJSValue m_jsvalue;
    QVariant m_pixmapVariant;

public:
    Pixmap(QQuickItem *parent = 0);

    void paint(QPainter *painter);

    QPixmap pixmap() const;
    QJSValue jsvalue() const;
    QVariant pixmapVariant() const;

signals:
    void pixmapChanged(QPixmap pixmap);

    void jsvalueChanged(QJSValue jsvalue);

    void pixmapVariantChanged(QVariant pixmapVariant);

public slots:
    void setPixmap(QPixmap pixmap);
    void setJsvalue(QJSValue jsvalue);
    void setPixmapVariant(QVariant pixmapVariant);
};

#endif // PIXMAP_H
