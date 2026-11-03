#include "bdffont.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>

bool BdfFont::load(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream in(&file);
    Glyph current;
    int encoding = -1;
    bool inBitmap = false;

    m_glyphs.clear();
    m_ascent = 0;
    m_descent = 0;

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (inBitmap)
        {
            if (line == "ENDCHAR")
            {
                inBitmap = false;
                if (encoding >= 0)
                {
                    m_glyphs.insert(encoding, current);
                }
            }
            else
            {
                current.bitmap.append(QByteArray::fromHex(line.toLatin1()));
            }
            continue;
        }

        if (line == "BITMAP")
        {
            inBitmap = true;
            continue;
        }

        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.size() < 2)
        {
            continue;
        }

        if (parts[0] == "FONT_ASCENT")
        {
            m_ascent = parts[1].toInt();
        }
        else if (parts[0] == "FONT_DESCENT")
        {
            m_descent = parts[1].toInt();
        }
        else if (parts[0] == "STARTCHAR")
        {
            current = Glyph();
            encoding = -1;
        }
        else if (parts[0] == "ENCODING")
        {
            encoding = parts[1].toInt();
        }
        else if (parts[0] == "DWIDTH")
        {
            current.advance = parts[1].toInt();
        }
        else if (parts[0] == "BBX" && parts.size() >= 5)
        {
            current.width = parts[1].toInt();
            current.height = parts[2].toInt();
            current.xOff = parts[3].toInt();
            current.yOff = parts[4].toInt();
        }
    }

    return !m_glyphs.isEmpty();
}

int BdfFont::ascent() const
{
    return m_ascent;
}

int BdfFont::descent() const
{
    return m_descent;
}

int BdfFont::lineHeight() const
{
    return m_ascent + m_descent;
}

int BdfFont::textWidth(const QString &text) const
{
    int width = 0;
    for (int i = 0; i < text.size(); ++i)
    {
        QHash<int, Glyph>::const_iterator it = m_glyphs.constFind(text.at(i).unicode());
        if (it != m_glyphs.constEnd())
        {
            width += it.value().advance;
        }
    }
    return width;
}

QStringList BdfFont::wrapText(const QString &text, int maxWidth) const
{
    QStringList lines;
    const QStringList paragraphs = text.split('\n');

    for (int p = 0; p < paragraphs.size(); ++p)
    {
        const QStringList words = paragraphs.at(p).split(' ', Qt::SkipEmptyParts);
        QString line;

        for (int w = 0; w < words.size(); ++w)
        {
            QString word = words.at(w);
            QString candidate = line.isEmpty() ? word : line + " " + word;

            if (textWidth(candidate) <= maxWidth)
            {
                line = candidate;
                continue;
            }

            if (!line.isEmpty())
            {
                lines << line;
                line.clear();
            }

            // A single word wider than the area is broken by characters.
            while (word.size() > 1 && textWidth(word) > maxWidth)
            {
                int cut = 1;
                while (cut < word.size() && textWidth(word.left(cut + 1)) <= maxWidth)
                {
                    ++cut;
                }
                lines << word.left(cut);
                word = word.mid(cut);
            }
            line = word;
        }

        lines << line;
    }

    return lines;
}

void BdfFont::drawText(QPainter &painter, int x, int baselineY,
                       const QString &text, const QColor &color) const
{
    int penX = x;

    for (int i = 0; i < text.size(); ++i)
    {
        QHash<int, Glyph>::const_iterator it = m_glyphs.constFind(text.at(i).unicode());
        if (it == m_glyphs.constEnd())
        {
            continue;
        }

        const Glyph &glyph = it.value();
        const int bytesPerRow = (glyph.width + 7) / 8;
        const int top = baselineY - (glyph.yOff + glyph.height);

        for (int row = 0; row < glyph.height; ++row)
        {
            for (int col = 0; col < glyph.width; ++col)
            {
                const int index = row * bytesPerRow + col / 8;
                if (index >= glyph.bitmap.size())
                {
                    continue;
                }
                const quint8 byte = static_cast<quint8>(glyph.bitmap.at(index));
                if (byte & (0x80 >> (col % 8)))
                {
                    painter.fillRect(penX + glyph.xOff + col, top + row, 1, 1, color);
                }
            }
        }

        penX += glyph.advance;
    }
}
