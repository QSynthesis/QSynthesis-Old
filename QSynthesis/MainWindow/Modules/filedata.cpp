#include "application.h"
#include "mainwindow.h"

void MainWindow::initConfig() {
    qConfig->setFilename(settingConifgPath());
    qConfig->load();
}

void MainWindow::initShortcuts() {
    qShortcuts->setFilename(keyboardConfigPath());
    qShortcuts->load();
}

void MainWindow::initSettingIni() {
    qSetting->setFilename(settingIniPath());
    qSetting->load();
}

void MainWindow::saveSettingIni() {
    if (!qSetting->save()) {
        QMessageBox::warning(qRoot, MainTitle,
                             tr("Unable to write %1!").arg(FILE_NAME_SETTING_INI));
        exitOnNoIOPermission();
    }
}
