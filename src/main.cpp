#include "windows/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "Apply"));
    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "&Cancel"));
    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "&Close"));
    Q_UNUSED(QT_TRANSLATE_NOOP("QPlatformTheme", "&OK"));

    a.setOrganizationName(ORGANIZATION_NAME);
    a.setApplicationName(PRODUCT_NAME);
    a.setApplicationVersion(VERSION_STRING);
    MainWindow w;
    w.show();
    return a.exec();
}
