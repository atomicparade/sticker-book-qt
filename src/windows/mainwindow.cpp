#include <algorithm>

#include <QClipboard>
#include <QCloseEvent>
#include <QColorDialog>
#include <QDir>
#include <QDirIterator>
#include <QPainter>
#include <QScrollBar>
#include <QTranslator>
#include <QWindow>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , optionsWindow(QLocale())
    , _currentLocale(QLocale())
    , _background(Qt::transparent)
    , _backgroundPixmap(16, 16)
    , _stickerGrid()
    , _settings(QCoreApplication::organizationName(), QCoreApplication::applicationName(), this)
    , _copyProfiles(this)
{
    _translator.load(QLocale(), "lang", "_", ":/translations", ".qm");
    qApp->installTranslator(&_translator);

    ui->setupUi(this);

    optionsWindow.setDirectories(&_directories);

    ui->cbCopyProfile->setModel(&_copyProfiles);
    optionsWindow.setCopyProfiles(&_copyProfiles);

    ui->lblBackground->setText("");

    _stickerGrid.setLayout(ui->stickerGridLayout);

    connect(&optionsWindow, &OptionsWindow::directoriesUpdated,
            this, &MainWindow::on_directoriesUpdated);
    connect(&optionsWindow, &OptionsWindow::localeUpdated,
            this, &MainWindow::on_localeUpdated);

    connect(&_stickerGrid, &StickerGrid::stickerClicked,
            this, &MainWindow::on_stickerClicked);

    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    updateStickerGridLayout();
}

void MainWindow::showEvent(QShowEvent *event)
{
    event->accept();
    loadStickers();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutWindow.exec();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionOptions_triggered()
{
    optionsWindow.exec();
}

void MainWindow::on_btnBackground_clicked()
{
    QColor color = QColorDialog::getColor(
                _background,
                this,
                "Select Background Color",
                QColorDialog::ShowAlphaChannel
    );

    if (color.isValid())
    {
        _background = color;
        updateBackgroundColor();
    }
}

void MainWindow::on_btnReloadImages_clicked()
{
    loadStickers();
}

void MainWindow::on_directoriesUpdated()
{
    loadStickers();
}

void MainWindow::on_localeUpdated(QLocale locale)
{
    updateLocale(locale);
}

void MainWindow::updateStickerGridLayout()
{
    int leftMargin;
    int topMargin;
    int rightMargin;
    int bottomMargin;

    const int scrollAreaWidth = ui->scrollArea->geometry().width();
    const int scrollbarWidth = qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
    ui->stickerGridLayout->getContentsMargins(&leftMargin, &topMargin, &rightMargin, &bottomMargin);

    const int contentAreaWidth = scrollAreaWidth - scrollbarWidth - leftMargin - rightMargin;

    _stickerGrid.updateLayout(contentAreaWidth);
}

void MainWindow::on_stickerClicked(Sticker *sticker)
{
    const CopyProfile copyProfile = getSelectedCopyProfile();

    QClipboard *clipboard = QGuiApplication::clipboard();

    QImage finalImage = sticker->image();

    const int height = finalImage.height();
    const int width = finalImage.width();
    const int maxHeight = copyProfile.height();
    const int maxWidth = copyProfile.width();
    const bool scaleUp = copyProfile.scaleUp();

    if (maxHeight > 0 && maxWidth > 0)
    {
        if (height > maxHeight || width > maxWidth)
        {
            const double widthRatio = static_cast<double>(width) / maxWidth;
            const double heightRatio = static_cast<double>(height) / maxHeight;

            if (widthRatio > heightRatio)
            {
                finalImage = finalImage.scaledToWidth(maxWidth, Qt::SmoothTransformation);
            }
            else
            {
                finalImage = finalImage.scaledToHeight(maxHeight, Qt::SmoothTransformation);
            }
        }
        else if ((height < maxHeight || width < maxWidth) && scaleUp)
        {
            const double widthRatio = static_cast<double>(width) / maxWidth;
            const double heightRatio = static_cast<double>(height) / maxHeight;

            if (widthRatio > heightRatio)
            {
                finalImage = finalImage.scaledToWidth(maxWidth, Qt::SmoothTransformation);
            }
            else
            {
                finalImage = finalImage.scaledToHeight(maxHeight, Qt::SmoothTransformation);
            }
        }
    }
    else if (maxHeight > 0)
    {
        if (
                 (height > maxHeight) ||
                 (height < maxHeight && scaleUp)
        ) {
            finalImage = finalImage.scaledToHeight(maxHeight, Qt::SmoothTransformation);
        }
    }
    else if (maxWidth > 0)
    {
        if (
                 (width > maxWidth) ||
                 (width < maxWidth && scaleUp)
        ) {
            finalImage = finalImage.scaledToWidth(maxWidth, Qt::SmoothTransformation);
        }
    }

    if (_background.alpha() > 0)
    {
        QImage image(finalImage.size(), QImage::Format_ARGB32);
        image.fill(_background);

        QPainter painter(&image);
        painter.drawImage(0, 0, finalImage);
        painter.end();

        finalImage = image;
    }

    clipboard->setImage(finalImage);
}

CopyProfile MainWindow::getSelectedCopyProfile()
{
    return _copyProfiles.at(ui->cbCopyProfile->currentIndex());
}

void MainWindow::loadStickers()
{
    _stickers.clear();

    QStringList extensions{
        "*.bmp",
        "*.gif",
        "*.jpg",
        "*.jpeg",
        "*.png"
    };

    for (QString directory : _directories)
    {
        QDirIterator it(directory,
                        extensions,
                        QDir::Files,
                        QDirIterator::Subdirectories | QDirIterator::FollowSymlinks
        );

        while (it.hasNext())
        {
            Sticker newSticker = Sticker(it.next());

            if (!_stickers.contains(newSticker))
            {
                _stickers.append(newSticker);
            }
        }
    }

    std::sort(_stickers.begin(), _stickers.end(), StickerNameComparator());

    _stickerGrid.loadStickers(&_stickers);
    updateStickerGridLayout();
}

void MainWindow::loadSettings()
{
    _directories.clear();

    const int numDirectories = _settings.beginReadArray("directories");

    for (int i = 0; i < numDirectories; ++i)
    {
        _settings.setArrayIndex(i);
        const QString directory = _settings.value("directory").toString().trimmed();

        if (!directory.isEmpty() && !_directories.contains(directory, Qt::CaseInsensitive))
        {
            _directories.append(directory);
        }
    }

    _settings.endArray();

    _copyProfiles.clear();
    _copyProfiles.addCopyProfile(CopyProfile(-1, -1, false)); // Add Actual Size copy profile

    const int numCopyProfiles = _settings.beginReadArray("copyProfiles");

    for (int i = 0; i < numCopyProfiles; ++i)
    {
        _settings.setArrayIndex(i);
        const QVariant maybeWidth = _settings.value("width");
        const QVariant maybeHeight = _settings.value("height");
        const QVariant maybeScaleUp = _settings.value("scaleUp");

        if (maybeWidth.isValid() && maybeHeight.isValid() && maybeScaleUp.isValid())
        {
            CopyProfile copyProfile(maybeWidth.toInt(), maybeHeight.toInt(), maybeScaleUp.toBool());

            if (!copyProfile.isActualSize())
            {
                _copyProfiles.addCopyProfile(copyProfile);
            }
        }
    }

    _settings.endArray();

    restoreGeometry(_settings.value("windowGeometry").toByteArray());

    {
        _settings.beginGroup("selectedCopyProfile");
        const QVariant maybeWidth = _settings.value("width");
        const QVariant maybeHeight = _settings.value("height");
        const QVariant maybeScaleUp = _settings.value("scaleUp");
        _settings.endGroup();

        if (maybeWidth.isValid() && maybeHeight.isValid() && maybeScaleUp.isValid())
        {
            CopyProfile savedSelectedCopyProfile = CopyProfile(maybeWidth.toInt(), maybeHeight.toInt(), maybeScaleUp.toBool());

            const int idx = _copyProfiles.indexOf(savedSelectedCopyProfile);

            if (idx >= 0)
            {
                ui->cbCopyProfile->setCurrentIndex(idx);
            }
        }
    }

    _currentLocale = _settings.value("locale", QLocale()).toLocale();
    optionsWindow.setCurrentLocale(_currentLocale);
    updateLocale(_currentLocale);

    _background = _settings.value("background", QColor::fromRgb(0, 0, 0, 0)).value<QColor>();
    updateBackgroundColor();
}

void MainWindow::saveSettings()
{
    _settings.beginWriteArray("directories");
    for (int i = 0; i < _directories.size(); ++i)
    {
        _settings.setArrayIndex(i);
        _settings.setValue("directory", _directories.at(i));
    }
    _settings.endArray();

    _settings.beginWriteArray("copyProfiles");
    int nextIndex = 0;
    for (int i = 0; i < _copyProfiles.rowCount(); ++i)
    {
        CopyProfile copyProfile = _copyProfiles.at(i);

        if (!copyProfile.isActualSize())
        {
            _settings.setArrayIndex(nextIndex);
            _settings.setValue("width", copyProfile.width());
            _settings.setValue("height", copyProfile.height());
            _settings.setValue("scaleUp", copyProfile.scaleUp());
            ++nextIndex;
        }
    }
    _settings.endArray();

    _settings.setValue("windowGeometry", saveGeometry());

    CopyProfile selectedCopyProfile = getSelectedCopyProfile();
    _settings.beginGroup("selectedCopyProfile");
    _settings.setValue("width", selectedCopyProfile.width());
    _settings.setValue("height", selectedCopyProfile.height());
    _settings.setValue("scaleUp", selectedCopyProfile.scaleUp());
    _settings.endGroup();

    _settings.setValue("locale", _currentLocale);

    _settings.setValue("background", _background);
}

void MainWindow::updateBackgroundColor()
{
    _backgroundPixmap.fill(Qt::white);
    _backgroundPixmap.fill(_background);
    ui->lblBackground->setPixmap(_backgroundPixmap);
}

void MainWindow::updateLocale(QLocale locale)
{
    const bool translationLoaded = _translator.load(locale, "lang", "_", ":/translations", ".qm");

    if (translationLoaded)
    {
        qApp->removeTranslator(&_translator);
        qApp->installTranslator(&_translator);
        ui->retranslateUi(this);
        optionsWindow.retranslateUi();
        aboutWindow.retranslateUi();
        _copyProfiles.retranslate();
    }

    _currentLocale = locale;
}

void MainWindow::on_leSearch_textChanged(const QString &searchText)
{
    const QString query = searchText.trimmed();

    QVector<Sticker> stickersToHide;

    for (const Sticker &sticker : _stickers)
    {
        if (!sticker.name().contains(query, Qt::CaseInsensitive))
        {
            stickersToHide.append(sticker);
        }
    }

    _stickerGrid.hideStickers(&stickersToHide);
    updateStickerGridLayout();
}
