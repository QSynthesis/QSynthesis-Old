#include "mainwindow.h"


void MainWindow::handleNewFile() {
    qDebug() << "[Action]"
             << "New";

    addEmptyTab();
}

void MainWindow::handleImportFile() {
    qDebug() << "[Action]"
             << "Import";

    execImport();
}

void MainWindow::handleOpenFile() {
    qDebug() << "[Action]"
             << "Open File";

    execOpen();
}

void MainWindow::handleOpenFolder() {
    qDebug() << "[Action]"
             << "Open Folder";

    execOpenFolder();
}

void MainWindow::handleSaveFile() {
    qDebug() << "[Action]"
             << "Save";

    CentralTab *tab = currentTab();
    execSave(tab);
}

void MainWindow::handleSaveAsFile() {
    qDebug() << "[Action]"
             << "Save As";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        execSaveAs(tab1);
    }
}

void MainWindow::handleRestoreFile() {
    qDebug() << "[Action]"
             << "Restore";

    CentralTab *tab = currentTab();
    if (tab->tabType() != Qs::Welcome) {
        tab->restore();
    }
}

void MainWindow::handleSwitchFile() {
    qDebug() << "[Action]"
             << "Switch";

    BaseTab *prevTab = previousTab();
    if (prevTab) {
        tabs->setCurrentWidget(prevTab);
    }
}

void MainWindow::handleCloseFile() {
    qDebug() << "[Action]"
             << "Close";

    handleTabCloseRequent(tabs->currentIndex());
}

void MainWindow::handleUndo() {
    qDebug() << "[Action]"
             << "Undo";

    CentralTab *tab = currentTab();
    if (tab->tabType() != Qs::Welcome) {
        tab->undo();
    }
}

void MainWindow::handleRedo() {
    qDebug() << "[Action]"
             << "Redo";

    CentralTab *tab = currentTab();
    if (tab->tabType() != Qs::Welcome) {
        tab->redo();
    }
}

void MainWindow::handleSelectAll() {
    qDebug() << "[Action]"
             << "Select All";

    CentralTab *tab = currentTab();
    if (tab->tabType() != Qs::Welcome) {
        tab->selectAll();
    }
}

void MainWindow::handleDeselect() {
    qDebug() << "[Action]"
             << "Deselect";

    CentralTab *tab = currentTab();
    if (tab->tabType() != Qs::Welcome) {
        tab->deselect();
    }
}

void MainWindow::handleReset() {
    qDebug() << "[Action]"
             << "Reset";

    CentralTab *tab = currentTab();
    if (tab->tabType() != Qs::Welcome) {
        tab->reset();
    }
}

void MainWindow::handlePlayPause() {
    qDebug() << "[Action]"
             << "Play";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->play();
    } else if (tab->tabType() == Qs::Folder) {
        VoiceBankTab *tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->play();
    }
}

void MainWindow::handleReplay() {
    qDebug() << "[Action]"
             << "Replay";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->replay();
    } else if (tab->tabType() == Qs::Folder) {
        VoiceBankTab *tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->replay();
    }
}

void MainWindow::handleStop() {
    qDebug() << "[Action]"
             << "Stop";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->stop();
    } else if (tab->tabType() == Qs::Folder) {
        VoiceBankTab *tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->stop();
    }
}

void MainWindow::handleOpenSettings() {
    addSettingTab();
}

void MainWindow::handleOpenKeyShortcuts() {
    addKeyboardTab();
}

void MainWindow::handleOpenThemes() {
    QStringList list = {"Light (Default)",    "Dark (Default)",    "My Custom Style 1",
                        "My Custom Style 2",  "My Custom Style 3", "My Custom Style 4",
                        "My Custom Style 5",  "My Custom Style 6", "My Custom Style 7",
                        "My Custom Style 8",  "My Custom Style 9", "My Custom Style 10",
                        "My Custom Style 11", "My Custom Style 12"};
    int index = tabs->useSelector(list, tr("Select color theme (Up/down keys to preview)"), 1,
                                  ColorTheme::previewTheme);
    qDebug() << "Final Index:" << index;
}

void MainWindow::handleOpenLanguages() {
}

void MainWindow::handleOpenWelcome() {
    addWelcomeTab();
}

void MainWindow::handleInstructions() {
}

void MainWindow::handleCheckUpdate() {
}

void MainWindow::handleAboutApp() {
}

void MainWindow::handleAboutQt() {
    QMessageBox::aboutQt(this);
}
