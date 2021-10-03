#include "KeyboardTab.h"

KeyboardTab::KeyboardTab(CentralTabWidget *parent) : CentralTab(parent) {
    initTab();
}

KeyboardTab::~KeyboardTab() {
    exitCore();
    clearHistory();
}

bool KeyboardTab::load() {
    bool valid = true;
    bool success = keys.load(&valid);

    // Always success
    if (success && valid) {
    }

    loadCore();
    return true;
}

bool KeyboardTab::save() {
    if (!checkNoConflict()) {
        return false;
    }

    ShortcutsFile orgKeys;
    orgKeys.commonShortcuts = keys.commonShortcuts;
    orgKeys.projectShortcuts = keys.projectShortcuts;
    orgKeys.voiceShortcuts = keys.voiceShortcuts;

    saveCore();

    notifier ? notifier->blockSignals(true) : true;
    bool result = keys.save();
    notifier ? notifier->blockSignals(true) : true;

    if (!result) {
        keys.commonShortcuts = orgKeys.commonShortcuts;
        keys.projectShortcuts = orgKeys.projectShortcuts;
        keys.voiceShortcuts = orgKeys.voiceShortcuts;

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
    keys.setFilename(m_filename);

    if (notifier) {
        qSystem->removeNotifier(notifier);
    }
    notifier = qSystem->createNotifier(m_filename, MiniSystem::File, false);
    if (notifier) {
        connect(notifier, &MiniSystemNotifier::fileChanged, this, &KeyboardTab::handleFileChanged);
    }
}

void KeyboardTab::setFixedname(const QString &value) {
    CentralTab::setFixedname(value);
    updateTabName();
}

void KeyboardTab::handleFileChanged(const QStringList &files) {
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
