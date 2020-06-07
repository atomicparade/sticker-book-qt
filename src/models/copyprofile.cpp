#include "copyprofile.h"

CopyProfile::CopyProfile(int width, int height, bool scaleUp)
    : _width(width)
    , _height(height)
    , _scaleUp(scaleUp)
{
    if (_width <= 0 && height <= 0)
    {
        _name = "Actual Size";
        _width = -1;
        _height = -1;
        _isActualSize = true;
    }
    else
    {
        if (_width > 0 && height > 0)
        {
            _name = "Width " + QString::number(_width) + "px, height " + QString::number(_height) + "px";
        }
        else if (_width > 0 && height <= 0)
        {
            _name = "Width " + QString::number(_width) + "px";
            _height = -1;
        }
        else if (_width <= 0 && height > 0)
        {
            _name = "Height " + QString::number(_height) + "px";
            _width = -1;
        }

        if (_scaleUp)
        {
            _name += ", scale up";
        }
        else
        {
            _name += ", don't scale up";
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
