#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QAbstractButton>
#include <QDialog>

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

    void setCopyProfiles(CopyProfileListModel *copyProfiles);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_btnAddCopyProfile_clicked();
    void on_btnDeleteCopyProfile_clicked();
    void on_buttonBox_clicked(QAbstractButton *button);
    void copyProfileDataAccepted(int width, int height, bool scaleUp);
    void recalculateCopyProfileDeleteEnabled();

private:
    void saveChanges();

private:
    Ui::OptionsWindow *ui;
    AddCopyProfileWindow addCopyProfileWindow;

    CopyProfileListModel *_copyProfiles = nullptr;
    CopyProfileListModel _workingCopyProfiles; // Temporary storage for options
};

#endif // OPTIONSWINDOW_H
