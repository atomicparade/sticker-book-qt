#include <QCloseEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _copyProfiles(new CopyProfileListModel(this))
{
    ui->setupUi(this);

    optionsWindow.setCopyProfiles(_copyProfiles);

    _copyProfiles->addCopyProfile(CopyProfile(-1, -1, false));
    _copyProfiles->addCopyProfile(CopyProfile(100, -1, false));
    _copyProfiles->addCopyProfile(CopyProfile(-1, 100, false));
    _copyProfiles->addCopyProfile(CopyProfile(100, 100, false));
    _copyProfiles->addCopyProfile(CopyProfile(100, -1, true));
    _copyProfiles->addCopyProfile(CopyProfile(-1, 100, true));
    _copyProfiles->addCopyProfile(CopyProfile(100, 100, true));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
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
