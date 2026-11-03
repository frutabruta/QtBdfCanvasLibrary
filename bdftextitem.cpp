#include "bdftextitem.h"

#include <QPainter>

BdfTextItem::BdfTextItem(const BdfFont &font, const QString &text, const QColor &color,
                         QGraphicsItem *parent)
    : QGraphicsItem(parent), m_font(font), m_text(text), m_color(color)
{
}

QRectF BdfTextItem::boundingRect() const
{
    return QRectF(0, 0, m_font.textWidth(m_text), m_font.lineHeight());
}

void BdfTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing, false);
    m_font.drawText(*painter, 0, m_font.ascent(), m_text, m_color);
}

void BdfTextItem::setColor(const QColor &color)
{
    m_color = color;
    update();
}

void BdfTextItem::setText(const QString &text)
{
    prepareGeometryChange();
    m_text = text;
    update();
}
