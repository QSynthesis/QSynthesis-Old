#include "QSActions.h"
#include "application.h"
#include "mainwindow.h"

void MainWindow::reloadMenu() {
    fileMenu->setTitle(tr("File(&F)"));
    editMenu->setTitle(tr("Edit(&E)"));
    modifyMenu->setTitle(tr("Modify(&M)"));
    previewMenu->setTitle(tr("Preview(&P)"));
    toolMenu->setTitle(tr("Tools(&T)"));
    helpMenu->setTitle(tr("Help(&H)"));

    welcomeActions->updateCommonStrings();

    welcomeActions->updateStrings();
    tuningActions->updateStrings();
    voiceActions->updateStrings();
    settingActions->updateStrings();
    keyboardActions->updateStrings();
}

void MainWindow::reloadShortcuts() {
    welcomeActions->setCommonShortcuts(qShortcuts->commonShortcuts);
    tuningActions->setShortcuts(qShortcuts->projectShortcuts);
    voiceActions->setShortcuts(qShortcuts->voiceShortcuts);
}

void MainWindow::reloadConfig() {
}
