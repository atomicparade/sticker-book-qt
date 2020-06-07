#include <QFileInfo>

#include "sticker.h"

Sticker::Sticker(QString path)
    : _path(path)
    , _name(QFileInfo(path).baseName().trimmed())
    , _image(_path)
{
}

bool Sticker::operator<(const Sticker &other) const
{
    return _path.compare(other._path, Qt::CaseInsensitive) < 0;
}

bool Sticker::operator>(const Sticker &other) const
{
    return _path.compare(other._path, Qt::CaseInsensitive) > 0;
}

bool Sticker::operator==(const Sticker &other) const
{
    return _path.compare(other._path, Qt::CaseInsensitive) == 0;
}

QString Sticker::path() const
{
    return _path;
}

QString Sticker::name() const
{
    return _name;
}

const QImage& Sticker::image() const
{
    return _image;
}

bool Sticker::isValid() const
{
    return !_image.isNull();
}
