#ifndef COPYPROFILE_H
#define COPYPROFILE_H

#include <QObject>

class CopyProfile : public QObject
{
    Q_OBJECT
public:
    explicit CopyProfile(int width, int height, bool scaleUp, QObject *parent = nullptr);
    int width();
    int height();
    bool scaleUp();
    QString name();

private:
    int _width;
    int _height;
    bool _scaleUp;
    QString _name;
};

#endif // COPYPROFILE_H
