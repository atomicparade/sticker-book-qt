#include <QCloseEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    aboutWindow.close();
    event->accept();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutWindow.show();
    aboutWindow.raise();
    aboutWindow.activateWindow();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
