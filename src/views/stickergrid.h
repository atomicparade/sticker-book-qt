#ifndef STICKERGRID_H
#define STICKERGRID_H

#include <QGridLayout>
#include <QObject>
#include <QPushButton>

#include "models/sticker.h"

class StickerGrid : public QObject
{
    Q_OBJECT
public:
    const int kButtonWidth = 64;
    const int kButtonHeight = 64;

    explicit StickerGrid(QObject *parent = nullptr);

    void setLayout(QGridLayout *layout);
    void loadStickers(QVector<Sticker> *stickers);

private:
    QGridLayout *_layout;
    QVector<QPushButton *> _buttons;
};

#endif // STICKERGRID_H
