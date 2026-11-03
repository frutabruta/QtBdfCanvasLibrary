#ifndef BDFTEXTITEM_H
#define BDFTEXTITEM_H

#include <QColor>
#include <QGraphicsItem>
#include <QString>

#include "bdffont.h"

class BdfTextItem : public QGraphicsItem
{
public:
    BdfTextItem(const BdfFont &font, const QString &text, const QColor &color,
                QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void setColor(const QColor &color);
    void setText(const QString &text);

private:
    const BdfFont &m_font;
    QString m_text;
    QColor m_color;
};

#endif // BDFTEXTITEM_H
