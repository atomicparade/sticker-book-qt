#include <QPushButton>
#include <QShowEvent>

#include "addcopyprofilewindow.h"
#include "constants.h"
#include "ui_addcopyprofilewindow.h"

AddCopyProfileWindow::AddCopyProfileWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCopyProfileWindow)
{
    ui->setupUi(this);
    intValidator.setRange(COPY_PROFILE_MIN_VALUE, COPY_PROFILE_MAX_VALUE);
    ui->leWidth->setValidator(&intValidator);
    ui->leHeight->setValidator(&intValidator);
}

AddCopyProfileWindow::~AddCopyProfileWindow()
{
    delete ui;
}

void AddCopyProfileWindow::showEvent(QShowEvent *event)
{
    ui->leWidth->setText("");
    ui->leHeight->setText("");
    ui->cbScaleUp->setCheckState(Qt::Unchecked);
    ui->leWidth->setFocus();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    event->accept();
}
