#include "bdfdraw.h"

BdfDraw::BdfDraw() {}



void BdfDraw::clearScene(QGraphicsScene *scene)
{
    // Get all items in the scene
    QList<QGraphicsItem*> items = scene->items();

    // Clear the scene
    //  scene->clear();

    // Delete all items
    for (QGraphicsItem* item : items)
    {
        delete item;
    }
    scene->clear();
}



QGraphicsRectItem* BdfDraw::drawBlackRectangle(QGraphicsScene *scene, int aX, int aY, int w, int h)
{
    QGraphicsRectItem *rectItem = scene->addRect(aX, aY, w, h, QPen(Qt::NoPen), QBrush(QColor(bgColor)));
    return rectItem;
}



QGraphicsRectItem* BdfDraw::drawOutlinedRectangle(QGraphicsScene *scene, int aY, int aX, int w, int h, QColor color)
{
    QPen pen(color); // Use your desired outline color
    pen.setWidth(1);     // Set outline width to 1px

    QGraphicsRectItem *rectItem = scene->addRect(aX, aY, w, h, pen, QBrush(Qt::NoBrush));
    return rectItem;
}

BdfTextItem* BdfDraw::drawRunningText(QGraphicsScene *scene, int x, int y, const BdfFont &font, QString content, bool invert, int &currentOffset)
{
    if (content != lastInfotext)
    {
        currentOffset = 0;
        lastInfotext = content;
    }

    QColor color = invert ? QColor(bgColor) : QColor(textColor);
    int textWidth = font.textWidth(content);

    // The scene takes ownership of the item, so a raw pointer is unavoidable here.
    BdfTextItem *selectedText = new BdfTextItem(font, content, color);
    selectedText->setPos(x - currentOffset + bdfMarginX, y + bdfMarginY);
    scene->addItem(selectedText);

    currentOffset++;
    if (currentOffset >= textWidth)
    {
        currentOffset = 0;
    }

    return selectedText;
}


BdfTextItem* BdfDraw::drawTextLeft(QGraphicsScene *scene, int x, int y,
                                      const BdfFont &font, QString content, bool invert)
{
    QColor color = invert ? QColor(bgColor) : QColor(textColor);

    // The scene takes ownership of the item, so a raw pointer is unavoidable here.
    BdfTextItem *selectedText = new BdfTextItem(font, content, color);
    selectedText->setPos(x + bdfMarginX, y + bdfMarginY);
    scene->addItem(selectedText);
    return selectedText;
}


BdfTextItem* BdfDraw::drawTextRight(QGraphicsScene *scene, int x, int y,
                                       const BdfFont &font, QString content, bool invert)
{
    QColor color = invert ? QColor(bgColor) : QColor(textColor);

    // The scene takes ownership of the item, so a raw pointer is unavoidable here.
    BdfTextItem *selectedText = new BdfTextItem(font, content, color);
    selectedText->setPos(x - font.textWidth(content) - bdfMarginX, y + bdfMarginY);
    scene->addItem(selectedText);

    return selectedText;
}

BdfTextItem* BdfDraw::drawTextMiddle(QGraphicsScene *scene, int x, int y, const BdfFont &font, QString content, bool invert)
{
    QColor color = invert ? QColor(bgColor) : QColor(textColor);

    // The scene takes ownership of the item, so a raw pointer is unavoidable here.
    BdfTextItem *selectedText = new BdfTextItem(font, content, color);


    selectedText->setPos(x - (font.textWidth(content)/2), y + bdfMarginY);
    scene->addItem(selectedText);

    return selectedText;
}


void BdfDraw::drawWrappingText(QGraphicsScene *scene, QString text, const BdfFont &font,
                                  QColor textColor, int aX, int aY, int w, int h)
{
    const QStringList lines = font.wrapText(text, w);
    const int lineHeight = font.lineHeight();

    for (int i = 0; i < lines.size(); ++i)
    {
        const int lineY = i * lineHeight;

        // Stop when the next line would not fit completely into the area.
        if (lineY + lineHeight > h)
        {
            break;
        }

        // The scene takes ownership of the item, so a raw pointer is unavoidable here.
        BdfTextItem *lineItem = new BdfTextItem(font, lines.at(i), textColor);
        lineItem->setPos(aX, aY + lineY);
        scene->addItem(lineItem);
    }
}

