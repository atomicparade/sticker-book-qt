#ifndef STICKER_H
#define STICKER_H

#include <QImage>
#include <QString>

class Sticker
{
    friend class StickerNameComparator;

public:
    Sticker() = default;
    Sticker(QString path);

    bool operator<(const Sticker &other) const;
    bool operator>(const Sticker &other) const;
    bool operator==(const Sticker &other) const;

    QString path() const;
    QString name() const;
    const QImage& image() const;
    bool isValid() const;

private:
    QString _path;
    QString _name;
    QImage _image;
};

class StickerNameComparator
{
public:
    bool operator()(const Sticker &sticker1, const Sticker &sticker2)
    {
        return sticker1.name().compare(sticker2.name(), Qt::CaseInsensitive) < 0;
    }
};

#endif // STICKER_H
