#include "mainwindow.h"

void MainWindow::exitOnNoIOPermission() {
    QMessageBox::critical(nullptr, ErrorTitle, tr("No write file permission!"));
    exitPreparation();
    exit(1);
}

void MainWindow::exitOnVoiceDirMissing() {
    QMessageBox::critical(nullptr, ErrorTitle, tr("Voice directory not found."));
    exitPreparation();
    exit(2);
}

void MainWindow::exitOnPluginsDirMissing() {
    QMessageBox::critical(nullptr, ErrorTitle, tr("Plugin directory not found."));
    exitPreparation();
    exit(3);
}

void MainWindow::exitOnConfigDirMissing() {
    QMessageBox::critical(nullptr, ErrorTitle, tr("Config directory not found."));
    exitPreparation();
    exit(4);
}
