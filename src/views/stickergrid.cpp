#include <QLabel>
#include <QLayout>

#include "stickergrid.h"

void StickerGrid::setScrollbarWidth(int scrollbarWidth)
{
    _scrollbarWidth = scrollbarWidth;
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
        (*it)->deleteLater();
    }

    _buttons.clear();

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

void StickerGrid::updateLayout(int contentAreaWidth)
{
    const int buttonsPerRow = contentAreaWidth / (kButtonWidth + _layout->horizontalSpacing());

    int row = 0;
    int col = 0;

    for (QPushButton *button : _buttons)
    {
        _layout->addWidget(button, row, col);

        ++col;

        if (col >= buttonsPerRow)
        {
            ++row;
            col = 0;
        }
    }

    // Keep all buttons to the left and up
    _layout->addWidget(&_bottomSpacer, row + 1, 0);
    _layout->setRowStretch(row + 1, 1);

    _layout->addWidget(&_rightSpacer, buttonsPerRow, 0);
    _layout->setColumnStretch(buttonsPerRow, 1);
}
