#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QAbstractButton>
#include <QDialog>
#include <QMap>
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
    explicit OptionsWindow(QLocale currentLocale, QWidget *parent = nullptr);
    ~OptionsWindow();

    void setDirectories(QStringList *directories);
    void setCopyProfiles(CopyProfileListModel *copyProfiles);
    void setCurrentLocale(QLocale locale);
    void retranslateUi();

signals:
    void directoriesUpdated();
    void localeUpdated(QLocale newLocale);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void on_btnAddDirectory_clicked();
    void on_btnRemoveDirectory_clicked();
    void on_btnAddCopyProfile_clicked();
    void on_btnDeleteCopyProfile_clicked();
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_copyProfileDataAccepted(int width, int height, bool scaleUp);
    void on_directorySelectionChanged();
    void on_copyProfileSelectionChanged();

private:
    void recalculateDirectoryRemoveEnabled();
    void recalculateCopyProfileDeleteEnabled();
    void saveChanges();

private:
    Ui::OptionsWindow *ui;
    AddCopyProfileWindow addCopyProfileWindow;

    QMap<QString, QLocale> _locales;
    QLocale _currentLocale;

    QStringList *_directories = nullptr;
    QStringList _workingDirectories;
    QStringListModel _workingDirectoriesModel;
    CopyProfileListModel *_copyProfiles = nullptr;
    CopyProfileListModel _workingCopyProfiles; // Temporary storage for options
};

#endif // OPTIONSWINDOW_H
