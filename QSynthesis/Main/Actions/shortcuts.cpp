#include "mainwindow.h"

void MainWindow::handleOpenBuildInMenu() {
    qDebug() << "[Action]"
             << "Build-In tools";

    QMenu *buildInMenu = tuningActions->buildInMenu;

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        buildInMenu->exec(QCursor::pos());
    }
}

void MainWindow::handleOpenPluginMenu() {
    qDebug() << "[Action]"
             << "Plugin";

    QMenu *pluginMenu = tuningActions->pluginMenu;

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        pluginMenu->exec(QCursor::pos());
    }
}

void MainWindow::handleOpenAliasMenu() {
    qDebug() << "[Action]"
             << "Alias";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->modifyAlias();
    }
}

void MainWindow::handleSwitchTrack() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchTrackStatus(Qs::Panels::Overview);
    }
}

void MainWindow::handleSwitchConfig() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchTrackStatus(Qs::Panels::Configuration);
    }
}

void MainWindow::handleSwitchNote() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchEditorStatus(Qs::Panels::Note);
    }
}

void MainWindow::handleSwitchPitch() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchEditorStatus(Qs::Panels::Pitch);
    }
}

void MainWindow::handleSwitchEnvelope() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchEditorStatus(Qs::Panels::Envelope);
    }
}

void MainWindow::handleSwitchInt() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchParamsStatus(Qs::Panels::Intensity);
    }
}

void MainWindow::handleSwitchMod() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchParamsStatus(Qs::Panels::Modulation);
    }
}

void MainWindow::handleSwitchVel() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchParamsStatus(Qs::Panels::Velocity);
    }
}

void MainWindow::handleSetOffset() {
    qDebug() << "[Action]"
             << "Set Offset";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Folder) {
        VoiceBankTab *tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->setOffsetByCursor();
    }
}

void MainWindow::handleSetOverlap() {
    qDebug() << "[Action]"
             << "Set Voice Overlap";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Folder) {
        VoiceBankTab *tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->setOverlapByCursor();
    }
}

void MainWindow::handleSetPreUttr() {
    qDebug() << "[Action]"
             << "Set Pre-Utterance";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Folder) {
        VoiceBankTab *tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->setPreUttrByCursor();
    }
}

void MainWindow::handleSetConstant() {
    qDebug() << "[Action]"
             << "Set Constant";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Folder) {
        VoiceBankTab *tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->setConstantByCursor();
    }
}

void MainWindow::handleSetBlank() {
    qDebug() << "[Action]"
             << "Set Blank";

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Folder) {
        VoiceBankTab *tab1 = qobject_cast<VoiceBankTab *>(tab);
        tab1->setBlankByCursor();
    }
}
