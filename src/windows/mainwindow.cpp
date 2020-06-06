#include <QCloseEvent>
#include <QDir>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _settings(QCoreApplication::organizationName(), QCoreApplication::applicationName(), this)
    , _copyProfiles(this)
{
    ui->setupUi(this);

    optionsWindow.setDirectories(&_directories);

    ui->cbCopyProfile->setModel(&_copyProfiles);
    optionsWindow.setCopyProfiles(&_copyProfiles);

    _copyProfiles.addCopyProfile(CopyProfile(-1, -1, false));
    _copyProfiles.addCopyProfile(CopyProfile(100, -1, false));
    _copyProfiles.addCopyProfile(CopyProfile(-1, 100, false));
    _copyProfiles.addCopyProfile(CopyProfile(100, 100, false));
    _copyProfiles.addCopyProfile(CopyProfile(100, -1, true));
    _copyProfiles.addCopyProfile(CopyProfile(-1, 100, true));
    _copyProfiles.addCopyProfile(CopyProfile(100, 100, true));

    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    event->accept();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutWindow.exec();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionOptions_triggered()
{
    optionsWindow.exec();
}

void MainWindow::loadSettings()
{
    const int numDirectories = _settings.beginReadArray("directories");
    int numDirectoriesAdded = 0;

    for (int i = 0; i < numDirectories; ++i)
    {
        _settings.setArrayIndex(i);
        const QString directory = _settings.value("directory").toString().trimmed();

        if (!directory.isEmpty() && !_directories.contains(directory, Qt::CaseInsensitive))
        {
            _directories.append(directory);
            ++numDirectoriesAdded;
        }
    }

    _settings.endArray();
}

void MainWindow::saveSettings()
{
    _settings.beginWriteArray("directories");
    for (int i = 0; i < _directories.size(); ++i)
    {
        _settings.setArrayIndex(i);
        _settings.setValue("directory", _directories.at(i));
    }
    _settings.endArray();

    _settings.beginWriteArray("copyProfiles");
    for (int i = 0; i < _copyProfiles.rowCount(); ++i)
    {

    }
}
