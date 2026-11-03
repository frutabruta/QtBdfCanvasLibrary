#ifndef BDFDRAW_H
#define BDFDRAW_H


#include "Bdf/bdffont.h"
#include "Bdf/bdftextitem.h"

#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class BdfDraw
{
public:
    QString textColor="#ffffff";
    QString bgColor="#000000";

    BdfDraw();
    QGraphicsRectItem *drawBlackRectangle(QGraphicsScene *scene, int aX, int aY, int w, int h);
    QGraphicsRectItem *drawOutlinedRectangle(QGraphicsScene *scene, int aX, int aY, int w, int h, QColor color);
    BdfTextItem *drawRunningText(QGraphicsScene *scene, int x, int y, const BdfFont &font, QString content, bool invert, int &currentOffset);
    BdfTextItem *drawTextLeft(QGraphicsScene *scene, int x, int y, const BdfFont &font, QString content, bool invert=false);
    BdfTextItem *drawTextRight(QGraphicsScene *scene, int x, int y, const BdfFont &font, QString content, bool invert=false);
    BdfTextItem *drawTextMiddle(QGraphicsScene *scene, int x, int y, const BdfFont &font, QString content, bool invert=false);

    void drawWrappingText(QGraphicsScene *scene, QString text, const BdfFont &font, QColor textColor, int aX, int aY, int w, int h);

    const int bdfMarginX = 4;
    const int bdfMarginY = 4;

    QString lastInfotext="";
    void clearScene(QGraphicsScene *scene);
};

#endif // BDFDRAW_H
