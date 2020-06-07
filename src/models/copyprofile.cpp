#include <QObject>

#include "copyprofile.h"

CopyProfile::CopyProfile(int width, int height, bool scaleUp)
    : _width(width)
    , _height(height)
    , _scaleUp(scaleUp)
{
    if (_width <= 0 && height <= 0)
    {
        _name = QObject::tr("Actual Size");
        _width = -1;
        _height = -1;
        _isActualSize = true;
    }
    else
    {
        if (_width > 0 && height > 0)
        {
            _name = QObject::tr("Width ") + QString::number(_width) +
                    QObject::tr("px, height ") + QString::number(_height) + QObject::tr("px");
        }
        else if (_width > 0 && height <= 0)
        {
            _name = QObject::tr("Width ") + QString::number(_width) + QObject::tr("px");
            _height = -1;
        }
        else if (_width <= 0 && height > 0)
        {
            _name = QObject::tr("Height ") + QString::number(_height) + QObject::tr("px");
            _width = -1;
        }

        if (_scaleUp)
        {
            _name += QObject::tr(", scale up");
        }
        else
        {
            _name += QObject::tr(", don't scale up");
        }

        _isActualSize = false;
    }
}

bool CopyProfile::operator==(const CopyProfile &other) const
{
    return (_isActualSize && other._isActualSize) ||
            (
                _width == other._width &&
                _height == other._height &&
                _scaleUp == other._scaleUp
            );
}

int CopyProfile::width() const
{
    return _width;
}

int CopyProfile::height() const
{
    return _height;
}

bool CopyProfile::scaleUp() const
{
    return _scaleUp;
}

bool CopyProfile::isActualSize() const
{
    return _isActualSize;
}

QString CopyProfile::name() const
{
    return _name;
}
