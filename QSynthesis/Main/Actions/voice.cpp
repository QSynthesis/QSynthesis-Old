#include "mainwindow.h"

void MainWindow::handleExportCurrent() {
    CentralTab *tab = currentTab();
    VoiceBankTab *tab1;
    if (tab->tabType() == Qs::Folder) {
        tab1 = qobject_cast<VoiceBankTab *>(tab);
    } else {
        return;
    }

    QString path = QFileDialog::getSaveFileName(this, tr("Export current settings"),
                                                FILE_NAME_OTO_INI, exportOtoIniFilterString);
    if (!path.isEmpty()) {
        tab1->exportCurrentSettings(path);
    }
}

void MainWindow::handleMoveUpSample() {
}

void MainWindow::handleMoveDownSample() {
}

void MainWindow::handleMoveTopSample() {
}

void MainWindow::handleMoveBottomSample() {
}

void MainWindow::handleDuplicateSample() {
}

void MainWindow::handleRemoveSample() {
}

void MainWindow::handleGenerateFrq() {
}

void MainWindow::handleModifyAlias() {
}

void MainWindow::handleRemoveInvalidSamples() {
}
