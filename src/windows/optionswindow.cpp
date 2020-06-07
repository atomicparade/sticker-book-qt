#include <QFileDialog>
#include <QItemSelectionModel>
#include <QShowEvent>

#include "optionswindow.h"
#include "ui_optionswindow.h"

OptionsWindow::OptionsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);

    connect(&addCopyProfileWindow, &AddCopyProfileWindow::copyProfileDataAccepted,
            this, &OptionsWindow::on_copyProfileDataAccepted);

    ui->lvDirectories->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable editing
    ui->lvDirectories->setModel(&_workingDirectoriesModel);
    connect(ui->lvDirectories->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &OptionsWindow::on_directorySelectionChanged);

    ui->lvCopyProfiles->setModel(&_workingCopyProfiles);
    connect(ui->lvCopyProfiles->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &OptionsWindow::on_copyProfileSelectionChanged);
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}

void OptionsWindow::setDirectories(QStringList *directories)
{
    _directories = directories;
}

void OptionsWindow::setCopyProfiles(CopyProfileListModel *copyProfiles)
{
    _copyProfiles = copyProfiles;
}

void OptionsWindow::showEvent(QShowEvent *event)
{
    // Create copies of the current settings and work only on those copies
    // until the user clicks Apply or OK
    _workingDirectories = *_directories;
    _workingDirectoriesModel.setStringList(_workingDirectories);
    recalculateDirectoryRemoveEnabled();

    _workingCopyProfiles.clear();
    for (int i = 0; i < _copyProfiles->rowCount(); ++i)
    {
        _workingCopyProfiles.addCopyProfile(_copyProfiles->at(i));
    }
    recalculateCopyProfileDeleteEnabled();

    event->accept();
}

void OptionsWindow::on_btnAddDirectory_clicked()
{
    QString directory = QFileDialog::getExistingDirectory();

    directory = directory.trimmed();
    if (!directory.isEmpty() && !_workingDirectories.contains(directory)) {
        _workingDirectories.append(directory);
        _workingDirectories.sort(Qt::CaseInsensitive);
        _workingDirectoriesModel.setStringList(_workingDirectories);
    }
}

void OptionsWindow::on_btnRemoveDirectory_clicked()
{
    QModelIndexList selectedIndexes = ui->lvDirectories->selectionModel()->selectedIndexes();

    for (auto i = selectedIndexes.rbegin(); i != selectedIndexes.rend(); ++i)
    {
        _workingDirectories.removeAt((*i).row());
    }

    _workingDirectoriesModel.setStringList(_workingDirectories);

    recalculateDirectoryRemoveEnabled();
}

void OptionsWindow::on_btnAddCopyProfile_clicked()
{
    addCopyProfileWindow.exec();
}

void OptionsWindow::on_btnDeleteCopyProfile_clicked()
{
    QModelIndexList selectedIndexes = ui->lvCopyProfiles->selectionModel()->selectedIndexes();

    for (auto i = selectedIndexes.rbegin(); i != selectedIndexes.rend(); ++i)
    {
        if ((*i).data() != "Actual Size")
        {
            _workingCopyProfiles.removeRow((*i).row());
        }
    }

    recalculateCopyProfileDeleteEnabled();
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

void OptionsWindow::on_copyProfileDataAccepted(int width, int height, bool scaleUp)
{
    _workingCopyProfiles.addCopyProfile(CopyProfile(width, height, scaleUp));
}

void OptionsWindow::on_directorySelectionChanged()
{
    recalculateDirectoryRemoveEnabled();
}

void OptionsWindow::on_copyProfileSelectionChanged()
{
    recalculateCopyProfileDeleteEnabled();
}

void OptionsWindow::recalculateDirectoryRemoveEnabled()
{
    QModelIndexList selectedIndexes = ui->lvDirectories->selectionModel()->selectedIndexes();

    // Only enable the button if at least one directory is selected
    ui->btnRemoveDirectory->setEnabled(selectedIndexes.size() > 0);
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
    // Only update _directories if _workingDirectories is different from before
    bool updateDirectories = false;

    if (_directories->size() != _workingDirectories.size())
    {
        updateDirectories = true;
    }
    else
    {
        for (int i = 0; i < _workingDirectories.size(); ++i)
        {
            if (_workingDirectories.at(i) != _directories->at(i))
            {
                updateDirectories = true;
                break;
            }
        }
    }

    if (updateDirectories)
    {
        *_directories = _workingDirectories;
        emit directoriesUpdated();
    }

    _copyProfiles->clear();
    for (int i = 0; i < _workingCopyProfiles.rowCount(); ++i)
    {
        _copyProfiles->addCopyProfile(_workingCopyProfiles.at(i));
    }
}
