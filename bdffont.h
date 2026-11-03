#ifndef BDFFONT_H
#define BDFFONT_H

#include <QByteArray>
#include <QColor>
#include <QHash>
#include <QPainter>
#include <QString>
#include <QStringList>

class BdfFont
{
public:
    bool load(const QString &path);

    int ascent() const;
    int descent() const;
    int lineHeight() const;
    int textWidth(const QString &text) const;
    QStringList wrapText(const QString &text, int maxWidth) const;

    void drawText(QPainter &painter, int x, int baselineY,
                  const QString &text, const QColor &color) const;

private:
    struct Glyph
    {
        int width = 0;
        int height = 0;
        int xOff = 0;
        int yOff = 0;
        int advance = 0;
        QByteArray bitmap; // rows, each (width + 7) / 8 bytes, MSB first
    };

    QHash<int, Glyph> m_glyphs;
    int m_ascent = 0;
    int m_descent = 0;
};

#endif // BDFFONT_H
