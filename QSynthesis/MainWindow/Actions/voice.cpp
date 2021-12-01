#include "Tabs/Voice/VoiceBankTab.h"
#include "mainwindow.h"

void MainWindow::handleExportCurrent() {
    CentralTab *tab = currentTab();
    VoiceBankTab *tab1;
    if (tab->tabType() == Qs::Folder) {
        tab1 = qobject_cast<VoiceBankTab *>(tab);
    } else {
        return;
    }

    QString path = QFileDialog::getSaveFileName(nullptr, tr("Export current settings"),
                                                Utau::FILE_NAME_OTO_INI, exportOtoIniFilterString);
    if (!path.isEmpty()) {
        tab1->exportCurrentSettings(path);
    }
}

void MainWindow::handleMoveUpSample() {
    CentralTab *tab = currentTab();
    VoiceBankTab *tab1;
    if (tab->tabType() == Qs::Folder) {
        tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->moveUp();
    }
}

void MainWindow::handleMoveDownSample() {
    CentralTab *tab = currentTab();
    VoiceBankTab *tab1;
    if (tab->tabType() == Qs::Folder) {
        tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->moveDown();
    }
}

void MainWindow::handleMoveTopSample() {
    CentralTab *tab = currentTab();
    VoiceBankTab *tab1;
    if (tab->tabType() == Qs::Folder) {
        tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->moveTop();
    }
}

void MainWindow::handleMoveBottomSample() {
    CentralTab *tab = currentTab();
    VoiceBankTab *tab1;
    if (tab->tabType() == Qs::Folder) {
        tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->moveBottom();
    }
}

void MainWindow::handleDuplicateSample() {
    CentralTab *tab = currentTab();
    VoiceBankTab *tab1;
    if (tab->tabType() == Qs::Folder) {
        tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->duplicate();
    }
}

void MainWindow::handleRemoveSample() {
    CentralTab *tab = currentTab();
    VoiceBankTab *tab1;
    if (tab->tabType() == Qs::Folder) {
        tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->remove();
    }
}

void MainWindow::handleGenerateFrq() {
}

void MainWindow::handleModifyAlias() {
}

void MainWindow::handleRemoveInvalidSamples() {
}
