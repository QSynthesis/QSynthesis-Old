#include <QDebug>
#include <QFile>

#include "QUtauStrings.h"
#include "VoiceBankTab.h"
#include "VoiceBankTabs/VoiceBankGroup.h"

VoiceBankTab::VoiceBankTab(CentralTabWidget *parent) : CentralTab(parent) {
    initTab();
}

VoiceBankTab::~VoiceBankTab() {
    exitCore();
    clearHistory();
}

void VoiceBankTab::addNotifier() {
    removeNotifier();
    notifier = qSystem->createNotifier(m_filename, MiniSystem::Directory);
    if (notifier) {
        connect(notifier, &MiniSystemNotifier::fileChanged, this, &VoiceBankTab::handleFileChanged);
    }
}

void VoiceBankTab::removeNotifier() {
    if (notifier) {
        qSystem->removeNotifier(notifier);
        notifier = nullptr;
    }
}

VoiceBankGroup *VoiceBankTab::ptrs() const {
    return m_ptrs;
}

void VoiceBankTab::setFilename(const QString &value) {
    CentralTab::setFilename(value);
    updateTabName();
}

void VoiceBankTab::updateMenuRoot() {
    tabActions->setNaturalStatus();
    updateMenuCore();
}

void VoiceBankTab::updateStatusRoot() {
}

void VoiceBankTab::updateMenuCore() {
    tabActions->saveFile->setEnabled(edited);

    tabActions->undo->setEnabled(!earliest());
    tabActions->redo->setEnabled(!latest());

    OtoTableTab *curTab = dataArea->currentTab();
    if (curTab) {
        bool empty = curTab->selectedRanges().isEmpty();
        bool isTop = curTab->isCurrentTop();
        bool isBottom = curTab->isCurrentBottom();
        bool isValid = curTab->isCurrentValid();
        bool isSingle = curTab->isSelectionSingle();

        tabActions->deselect->setEnabled(!empty);
        tabActions->reset->setEnabled(!empty);

        tabActions->moveUp->setEnabled(isSingle && !isTop);
        tabActions->moveTop->setEnabled(isSingle && !isTop);
        tabActions->moveDown->setEnabled(isSingle && !isBottom);
        tabActions->moveBottom->setEnabled(isSingle && !isBottom);
        tabActions->duplicate->setEnabled(isSingle);
        tabActions->remove->setEnabled(isSingle && !(isTop && isBottom && isValid));
    } else {
        tabActions->deselect->setEnabled(false);
        tabActions->reset->setEnabled(false);

        tabActions->moveUp->setEnabled(false);
        tabActions->moveTop->setEnabled(false);
        tabActions->moveDown->setEnabled(false);
        tabActions->moveBottom->setEnabled(false);
        tabActions->remove->setEnabled(false);
    }

    tabActions->generateFrq->setEnabled(false);
    tabActions->modifyAlias->setEnabled(false);
    tabActions->removeInvalid->setEnabled(false);
}

void VoiceBankTab::updateTabName() {
    QString title = voicebank.title();
    if (!title.isEmpty()) {
        setTabName(title);
    } else {
        setTabName(PathFindFileName(m_filename));
    }
}

void VoiceBankTab::handleSavedStateChanged() {
}

void VoiceBankTab::handleFileChanged(const QStringList &files) {
    QStringList sampleFiles;
    bool changed = false;
    for (auto it = files.begin(); it != files.end(); ++it) {
        if (it->endsWith(FILE_NAME_OTO_INI, Qt::CaseInsensitive) ||
            it->endsWith(FILE_NAME_PREFIX_MAP, Qt::CaseInsensitive) ||
            it->endsWith(FILE_NAME_CHAR_TEXT, Qt::CaseInsensitive) ||
            it->endsWith(FILE_NAME_VOICE_README, Qt::CaseInsensitive)) {
            changed = true;
        } else {
            sampleFiles.append(*it);
        }
    }
    if (dataArea->notifyTable(sampleFiles)) {
        changed = true;
    }
    if (changed) {
        savedHistoryIndex = -1;
        setEdited(true);
    }
}
