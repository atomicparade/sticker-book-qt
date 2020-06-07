#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QAbstractButton>
#include <QDialog>
#include <QStringListModel>

#include "models/copyprofilelistmodel.h"
#include "addcopyprofilewindow.h"

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();

    void setDirectories(QStringList *directories);
    void setCopyProfiles(CopyProfileListModel *copyProfiles);

signals:
    void directoriesUpdated();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_btnAddDirectory_clicked();
    void on_btnRemoveDirectory_clicked();
    void on_btnAddCopyProfile_clicked();
    void on_btnDeleteCopyProfile_clicked();
    void on_buttonBox_clicked(QAbstractButton *button);
    void copyProfileDataAccepted(int width, int height, bool scaleUp);
    void recalculateDirectoryRemoveEnabled();
    void recalculateCopyProfileDeleteEnabled();

private:
    void saveChanges();

private:
    Ui::OptionsWindow *ui;
    AddCopyProfileWindow addCopyProfileWindow;

    QStringList *_directories = nullptr;
    QStringList _workingDirectories;
    QStringListModel _workingDirectoriesModel;
    CopyProfileListModel *_copyProfiles = nullptr;
    CopyProfileListModel _workingCopyProfiles; // Temporary storage for options
};

#endif // OPTIONSWINDOW_H
