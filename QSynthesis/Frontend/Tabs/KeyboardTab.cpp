#include "KeyboardTab.h"
#include "mainwindow.h"

KeyboardTab::KeyboardTab(CentralTabWidget *parent) : CentralTab(parent) {
    initTab();
}

KeyboardTab::~KeyboardTab() {
    clearHistory();
}

bool KeyboardTab::load() {
    bool valid = true;
    bool success = cfg.load(&valid);

    // Always success
    if (success && valid) {
    }

    keys = cfg.data();
    loadCore();
    return true;
}

bool KeyboardTab::save() {
    if (!checkNoConflict()) {
        return false;
    }

    saveCore();

    ShortcutsData orgKeys = cfg.data();
    cfg.setData(keys);

    bool result = cfg.save();
    if (!result) {
        cfg.setData(orgKeys);
        QMessageBox::about(this, ErrorTitle, tr("Unable to save file!"));
    } else {
        externModified = false;
        savedHistoryIndex = historyIndex; // Update saved history index
        setEdited(false);
    }

    return result;
}

bool KeyboardTab::restore() {
    clearHistory();
    if (externModified) {
        savedHistoryIndex = -1;
    }
    setEdited(savedHistoryIndex != historyIndex);
    loadCore();
    return true;
}

void KeyboardTab::awake() {
    CentralTab::awake();
}

void KeyboardTab::sleep() {
    CentralTab::sleep();
}

void KeyboardTab::enter() {
    CentralTab::enter();
}

void KeyboardTab::leave() {
    CentralTab::leave();
}

void KeyboardTab::setFilename(const QString &value) {
    CentralTab::setFilename(value);
    cfg.setFilename(m_filename);
}

void KeyboardTab::setFixedname(const QString &value) {
    CentralTab::setFixedname(value);
    updateTabName();
}

void KeyboardTab::handleFileChanged() {
    externModified = true;
    savedHistoryIndex = -1;
    setEdited(true);
}

void KeyboardTab::updateMenuRoot() {
    tabActions->setNaturalStatus();
    updateMenuCore();
}

void KeyboardTab::updateMenuCore() {
    tabActions->saveFile->setEnabled(edited);
    tabActions->restoreFile->setEnabled(edited);

    tabActions->undo->setEnabled(!earliest());
    tabActions->redo->setEnabled(!latest());

    bool empty = currentKeyTab()->selectedRanges().isEmpty();
    tabActions->deselect->setEnabled(!empty);
    tabActions->reset->setEnabled(!empty);
}
