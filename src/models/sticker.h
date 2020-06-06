#ifndef STICKER_H
#define STICKER_H

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

private:
    QString _path;
    QString _name;
};

#endif // STICKER_H
