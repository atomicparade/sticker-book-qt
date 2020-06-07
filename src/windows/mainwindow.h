#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QStringList>

#include <views/stickergrid.h>

#include "models/copyprofilelistmodel.h"
#include "models/sticker.h"
#include "aboutwindow.h"
#include "optionswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_actionOptions_triggered();
    void on_btnReloadImages_clicked();
    void on_leSearch_textChanged(const QString &searchText);

    void on_directoriesUpdated();
    void on_stickerClicked(Sticker *sticker);

private:
    CopyProfile getSelectedCopyProfile();
    void loadStickers();
    void loadSettings();
    void saveSettings();
    void updateStickerGridLayout();

private:
    Ui::MainWindow *ui;
    AboutWindow aboutWindow;
    OptionsWindow optionsWindow;

    StickerGrid _stickerGrid;

    QSettings _settings;
    QStringList _directories;
    CopyProfileListModel _copyProfiles;
    QVector<Sticker> _stickers;
};
#endif // MAINWINDOW_H
