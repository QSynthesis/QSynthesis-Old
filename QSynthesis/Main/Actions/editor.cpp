#include "mainwindow.h"

void MainWindow::handleOpenProjectSettings() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->showProjectSettings();
    }
}

void MainWindow::handleOpenCharsetSettings() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->showCharsetSettings();
    }
}

void MainWindow::handleFullAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(1);
    }
}
void MainWindow::handleHalfAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(2);
    }
}
void MainWindow::handleQuarterAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(4);
    }
}
void MainWindow::handleSixthAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(6);
    }
}
void MainWindow::handleEighthAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(8);
    }
}
void MainWindow::handleTwelfthAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(12);
    }
}
void MainWindow::handleSixteenthAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(16);
    }
}
void MainWindow::handleTwentyForthAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(24);
    }
}
void MainWindow::handleThirtySecondAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(32);
    }
}
void MainWindow::handleNoneAdsorb() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->setLengthUnit(0);
    }
}

void MainWindow::handleSwitchNoteVisibility() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchNoteVisibility();
    }
}

void MainWindow::handleSwitchPitchVisibility() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchPitchVisibility();
    }
}

void MainWindow::handleSwitchEnvelopeVisibility() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchEnvelopeVisibility();
    }
}

void MainWindow::handleSwitchParamsVisibility() {
    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->switchParamsVisibility();
    }
}
