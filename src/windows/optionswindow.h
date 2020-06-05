#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QDialog>

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

private slots:
    void on_btnAddCopyProfile_clicked();

private:
    Ui::OptionsWindow *ui;
    AddCopyProfileWindow addCopyProfileWindow;
};

#endif // OPTIONSWINDOW_H
