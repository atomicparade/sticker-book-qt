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
    _directories.clear();

    const int numDirectories = _settings.beginReadArray("directories");

    for (int i = 0; i < numDirectories; ++i)
    {
        _settings.setArrayIndex(i);
        const QString directory = _settings.value("directory").toString().trimmed();

        if (!directory.isEmpty() && !_directories.contains(directory, Qt::CaseInsensitive))
        {
            _directories.append(directory);
        }
    }

    _settings.endArray();

    _copyProfiles.clear();
    _copyProfiles.addCopyProfile(CopyProfile(-1, -1, false)); // Add Actual Size copy profile

    const int numCopyProfiles = _settings.beginReadArray("copyProfiles");

    for (int i = 0; i < numCopyProfiles; ++i)
    {
        _settings.setArrayIndex(i);
        const QVariant maybeWidth = _settings.value("width");
        const QVariant maybeHeight = _settings.value("height");
        const QVariant maybeScaleUp = _settings.value("scaleUp");

        if (maybeWidth.isValid() && maybeHeight.isValid() && maybeScaleUp.isValid())
        {
            CopyProfile copyProfile(maybeWidth.toInt(), maybeHeight.toInt(), maybeScaleUp.toBool());

            if (copyProfile.name() != "Actual Size")
            {
                _copyProfiles.addCopyProfile(copyProfile);
            }
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
    int nextIndex = 0;
    for (int i = 0; i < _copyProfiles.rowCount(); ++i)
    {
        CopyProfile copyProfile = _copyProfiles.at(i);

        if (copyProfile.name() != "Actual Size")
        {
            _settings.setArrayIndex(nextIndex);
            _settings.setValue("width", copyProfile.width());
            _settings.setValue("height", copyProfile.height());
            _settings.setValue("scaleUp", copyProfile.scaleUp());
            ++nextIndex;
        }
    }
    _settings.endArray();
}
