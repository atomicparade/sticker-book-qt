#ifndef STICKERGRID_H
#define STICKERGRID_H

#include <QGridLayout>
#include <QPushButton>

#include "models/sticker.h"

class StickerGrid
{
public:
    const int kButtonWidth = 64;
    const int kButtonHeight = 64;

    StickerGrid() = default;

    void setScrollbarWidth(int width);
    void setLayout(QGridLayout *layout);
    void loadStickers(QVector<Sticker> *stickers);

    void updateLayout(int contentAreaWidth);

private:
    int _scrollbarWidth;
    QGridLayout *_layout;
    QVector<QPushButton *> _buttons;
    QWidget _rightSpacer;
    QWidget _bottomSpacer;
};

#endif // STICKERGRID_H
