#include "KeyboardTab.h"
#include "application.h"

#include <QTabBar>

KeyboardTab::KeyboardTab(CentralTabWidget *parent) : CentralTab(parent) {
    initTab();
}

KeyboardTab::~KeyboardTab() {
    exitCore();
    clearHistory();
}

void KeyboardTab::addNotifier() {
    removeNotifier();
    notifier = qSystem->createNotifier(m_filename, MiniSystem::File, false);
    if (notifier) {
        connect(notifier, &MiniSystemNotifier::fileChanged, this, &KeyboardTab::handleFileChanged);
    }
}

void KeyboardTab::removeNotifier() {
    if (notifier) {
        qSystem->removeNotifier(notifier);
        notifier = nullptr;
    }
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
}

void KeyboardTab::setFixedname(const QString &value) {
    CentralTab::setFixedname(value);
    updateTabName();
}

void KeyboardTab::handleFileChanged(const QStringList &files) {
    externModified = true;
    savedHistoryIndex = -1;
    setEdited(true);

    removeNotifier();
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
