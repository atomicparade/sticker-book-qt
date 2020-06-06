#ifndef COPYPROFILE_H
#define COPYPROFILE_H

#include <QString>

class CopyProfile
{
public:
    CopyProfile() = default;
    CopyProfile(int width, int height, bool scaleUp);
    bool operator==(const CopyProfile &other) const;
    int width() const;
    int height() const;
    bool scaleUp() const;
    QString name() const;

private:
    int _width;
    int _height;
    bool _scaleUp;
    QString _name;
};

#endif // COPYPROFILE_H
