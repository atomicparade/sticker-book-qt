#ifndef STICKERGRID_H
#define STICKERGRID_H

#include <QGridLayout>
#include <QMap>
#include <QPushButton>

#include "models/sticker.h"

class StickerGrid : public QObject
{
    Q_OBJECT
public:
    const int kButtonWidth = 64;
    const int kButtonHeight = 64;

    StickerGrid(QObject *parent = nullptr);

    void setScrollbarWidth(int width);
    void setLayout(QGridLayout *layout);
    void loadStickers(QVector<Sticker> *stickers);
    void hideStickers(QVector<Sticker> *stickersToHide);
    void updateLayout(int contentAreaWidth);

signals:
    void stickerClicked(Sticker *sticker);

private slots:
    void stickerButtonClicked();

private:
    int _scrollbarWidth;
    QGridLayout *_layout;
    QMap<Sticker *,QPushButton *> _buttons;
    QWidget _rightSpacer;
    QWidget _bottomSpacer;
};

#endif // STICKERGRID_H
