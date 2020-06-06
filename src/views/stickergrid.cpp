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
        button->setFixedSize(kButtonWidth, kButtonHeight);
        button->setIconSize(QSize(kButtonWidth, kButtonHeight));
        button->setFlat(true);
        button->setIcon(QPixmap::fromImage(sticker.image()));
        button->setToolTip(sticker.name());

        _buttons.append(button);
        _layout->addWidget(button);
    }
}
