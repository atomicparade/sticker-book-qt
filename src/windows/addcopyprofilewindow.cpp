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

    connect(ui->leWidth, &QLineEdit::textChanged, this, &AddCopyProfileWindow::eventMaxHeightOrMaxWidthChanged);
    connect(ui->leHeight, &QLineEdit::textChanged, this, &AddCopyProfileWindow::eventMaxHeightOrMaxWidthChanged);
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

void AddCopyProfileWindow::eventMaxHeightOrMaxWidthChanged()
{
    // At least one of width or height must be > 0
    const int width = ui->leWidth->text().toInt();
    const int height = ui->leHeight->text().toInt();

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled((width > 0) || (height > 0));
}

void AddCopyProfileWindow::on_buttonBox_accepted()
{
    const int width = ui->leWidth->text().toInt();
    const int height = ui->leHeight->text().toInt();

    if (width <= 0 && height <= 0)
    {
        return;
    }

    const bool scaleUp = ui->cbScaleUp->checkState() == Qt::Checked;

    emit copyProfileDataAccepted(width, height, scaleUp);
}
