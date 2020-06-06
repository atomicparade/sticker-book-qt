#ifndef STICKER_H
#define STICKER_H

#include <QImage>
#include <QString>

class Sticker
{
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

#endif // STICKER_H
