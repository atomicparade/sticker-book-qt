#include "copyprofile.h"

CopyProfile::CopyProfile(int width, int height, bool scaleUp)
    : _width(width)
    , _height(height)
    , _scaleUp(scaleUp)
{
    if (_width <= 0 && height <= 0)
    {
        _name = "Actual Size";
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
        }
        else if (_width <= 0 && height > 0)
        {
            _name = "Height " + QString::number(_height) + "px";
        }

        if (_scaleUp)
        {
            _name += ", scale up";
        }
        else
        {
            _name += ", don't scale up";
        }
    }
}

bool CopyProfile::operator==(const CopyProfile &other) const
{
    // Compare by name instead of width/height/scaleUp
    // This takes care of Actual Size
    return _name == other._name;
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

QString CopyProfile::name() const
{
    return _name;
}
