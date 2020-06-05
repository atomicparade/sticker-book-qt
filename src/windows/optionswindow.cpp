#include "optionswindow.h"
#include "ui_optionswindow.h"

OptionsWindow::OptionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::setCopyProfileListModel(CopyProfileListModel *copyProfileListModel)
{
    ui->lvCopyProfiles->setModel(copyProfileListModel);
}

void OptionsWindow::on_btnAddCopyProfile_clicked()
{
    addCopyProfileWindow.exec();
}
