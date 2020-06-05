#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

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
    void recalculateCopyProfileDeleteEnabled();

private:
    Ui::OptionsWindow *ui;
    AddCopyProfileWindow addCopyProfileWindow;

    CopyProfileListModel *_copyProfiles = nullptr;
};

#endif // OPTIONSWINDOW_H
