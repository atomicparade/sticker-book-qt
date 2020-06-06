#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "models/copyprofilelistmodel.h"
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
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionAbout_triggered();
    void on_actionExit_triggered();

    void on_actionOptions_triggered();

private:
    Ui::MainWindow *ui;
    AboutWindow aboutWindow;
    OptionsWindow optionsWindow;

    CopyProfileListModel _copyProfiles;
};
#endif // MAINWINDOW_H
