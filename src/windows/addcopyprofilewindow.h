#ifndef ADDCOPYPROFILEWINDOW_H
#define ADDCOPYPROFILEWINDOW_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class AddCopyProfileWindow;
}

class AddCopyProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddCopyProfileWindow(QWidget *parent = nullptr);
    ~AddCopyProfileWindow();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void eventMaxHeightOrMaxWidthChanged();

private:
    Ui::AddCopyProfileWindow *ui;
    QIntValidator intValidator;
};

#endif // ADDCOPYPROFILEWINDOW_H
