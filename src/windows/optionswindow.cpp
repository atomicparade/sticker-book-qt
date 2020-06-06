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
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::showEvent(QShowEvent *event)
{
    ui->btnRemoveDirectory->setEnabled(false);

    recalculateCopyProfileDeleteEnabled();

    event->accept();
}

void OptionsWindow::setCopyProfiles(CopyProfileListModel *copyProfiles)
{
    _copyProfiles = copyProfiles;
    ui->lvCopyProfiles->setModel(copyProfiles);

    connect(ui->lvCopyProfiles->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &OptionsWindow::recalculateCopyProfileDeleteEnabled);
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

        CopyProfile selectedCopyProfile = _copyProfiles->at(selectedIndex.row());

        _copyProfiles->removeCopyProfile(selectedCopyProfile);
    }
}

void OptionsWindow::copyProfileDataAccepted(int width, int height, bool scaleUp)
{
    _copyProfiles->addCopyProfile(CopyProfile(width, height, scaleUp));
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
