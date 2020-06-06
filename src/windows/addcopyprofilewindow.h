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

signals:
    void copyProfileDataAccepted(int width, int height, bool scaleUp);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void eventMaxHeightOrMaxWidthChanged();

    void on_buttonBox_accepted();

private:
    Ui::AddCopyProfileWindow *ui;
    QIntValidator intValidator;
};

#endif // ADDCOPYPROFILEWINDOW_H
