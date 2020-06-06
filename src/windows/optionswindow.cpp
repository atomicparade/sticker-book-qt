#include <QItemSelectionModel>
#include <QShowEvent>

#include "optionswindow.h"
#include "ui_optionswindow.h"

OptionsWindow::OptionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);

    connect(&addCopyProfileWindow, &AddCopyProfileWindow::copyProfileDataAccepted,
            this, &OptionsWindow::copyProfileDataAccepted);

    ui->lvCopyProfiles->setModel(&_workingCopyProfiles);
    connect(ui->lvCopyProfiles->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &OptionsWindow::recalculateCopyProfileDeleteEnabled);
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::showEvent(QShowEvent *event)
{
    ui->btnRemoveDirectory->setEnabled(false);

    _workingCopyProfiles.clear();

    for (int i = 0; i < _copyProfiles->rowCount(); ++i)
    {
        _workingCopyProfiles.addCopyProfile(_copyProfiles->at(i));
    }

    recalculateCopyProfileDeleteEnabled();

    event->accept();
}

void OptionsWindow::setCopyProfiles(CopyProfileListModel *copyProfiles)
{
    _copyProfiles = copyProfiles;
}

void OptionsWindow::on_btnAddCopyProfile_clicked()
{
    addCopyProfileWindow.exec();
}

void OptionsWindow::on_btnDeleteCopyProfile_clicked()
{
    QModelIndexList selectedIndexes = ui->lvCopyProfiles->selectionModel()->selectedIndexes();

    if (selectedIndexes.size() > 0)
    {
        QModelIndex selectedIndex = selectedIndexes.first();

        CopyProfile selectedCopyProfile = _workingCopyProfiles.at(selectedIndex.row());

        _workingCopyProfiles.removeCopyProfile(selectedCopyProfile);
    }
}

void OptionsWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->buttonRole(button))
    {
    case QDialogButtonBox::ApplyRole:
    case QDialogButtonBox::AcceptRole:
        saveChanges();
        break;
    default:
        break;
    }
}

void OptionsWindow::copyProfileDataAccepted(int width, int height, bool scaleUp)
{
    _workingCopyProfiles.addCopyProfile(CopyProfile(width, height, scaleUp));
}

void OptionsWindow::recalculateCopyProfileDeleteEnabled()
{
    bool enableButton = false;

    QModelIndexList selectedIndexes = ui->lvCopyProfiles->selectionModel()->selectedIndexes();

    // Only enable the button if at least one copy profile other than "Actual Size" is enabled
    if (selectedIndexes.size() > 0)
    {
        QModelIndex selectedIndex = selectedIndexes.first();

        if (selectedIndex.isValid() && selectedIndex.data().toString().compare("Actual Size") != 0)
        {
            enableButton = true;
        }
    }

    ui->btnDeleteCopyProfile->setEnabled(enableButton);
}

void OptionsWindow::saveChanges()
{
    _copyProfiles->clear();

    for (int i = 0; i < _workingCopyProfiles.rowCount(); i++)
    {
        _copyProfiles->addCopyProfile(_workingCopyProfiles.at(i));
    }
}

