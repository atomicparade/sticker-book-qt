#include "copyprofile.h"

CopyProfile::CopyProfile(int width, int height, bool scaleUp, QObject *parent)
    : QObject(parent)
    , _width(width)
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

int CopyProfile::width()
{
    return _width;
}

int CopyProfile::height()
{
    return _height;
}

bool CopyProfile::scaleUp()
{
    return _scaleUp;
}

QString CopyProfile::name()
{
    return _name;
}
