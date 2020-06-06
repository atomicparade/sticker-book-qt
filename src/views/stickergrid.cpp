#include "stickergrid.h"

StickerGrid::StickerGrid(QObject *parent)
    : QObject(parent)
{
}

void StickerGrid::setLayout(QGridLayout *layout)
{
    _layout = layout;
}

void StickerGrid::loadStickers(QVector<Sticker> *stickers)
{
    for (auto it = _buttons.begin(); it != _buttons.end(); ++it)
    {
        _layout->removeWidget(*it);
        it = _buttons.erase(it);
    }

    for (const Sticker &sticker : *stickers)
    {
        QPushButton *button = new QPushButton();
        button->setFlat(true);
        button->setIcon(QPixmap::fromImage(sticker.image()));

        _buttons.append(button);
        _layout->addWidget(button);
    }
}
