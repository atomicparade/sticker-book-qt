#include <QFileInfo>

#include "sticker.h"

Sticker::Sticker(QString path) : _path(path)
{
    const QFileInfo fileInfo(path);
    _name = fileInfo.fileName();
}

bool Sticker::operator<(const Sticker &other) const
{
    return _name.compare(other._name, Qt::CaseInsensitive) < 0;
}

bool Sticker::operator>(const Sticker &other) const
{
    return _name.compare(other._name, Qt::CaseInsensitive) > 0;
}

bool Sticker::operator==(const Sticker &other) const
{
    return _name.compare(other._name, Qt::CaseInsensitive) == 0;
}

QString Sticker::path() const
{
    return _path;
}

QString Sticker::name() const
{
    return _name;
}
