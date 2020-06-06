#include <QFileInfo>

#include "sticker.h"

Sticker::Sticker(QString path) : _path(path)
{
    const QFileInfo fileInfo(path);
    _name = fileInfo.fileName();
}

QString Sticker::path() const
{
    return _path;
}

QString Sticker::name() const
{
    return _name;
}
