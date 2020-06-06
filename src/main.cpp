#include "windows/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName(ORGANIZATION_NAME);
    a.setApplicationName(PRODUCT_NAME);
    a.setApplicationVersion(VERSION_STRING);
    MainWindow w;
    w.show();
    return a.exec();
}
