#include "../VoiceBankTab.h"
#include "mainwindow.h"

void VoiceBankTab::handleCharTxtChanged() {
    savedHistoryIndex = -1;
    setEdited(true);
}

void VoiceBankTab::handlePrefixMapChanged() {
    savedHistoryIndex = -1;
    setEdited(true);
}

void VoiceBankTab::handleReadmeTxtChanged() {
    savedHistoryIndex = -1;
    setEdited(true);
}

void VoiceBankTab::handleOtoFileChanged(QString path) {
    savedHistoryIndex = -1;
    setEdited(true);
}

void VoiceBankTab::handleOtoDirChanged(QString path) {
    if (!qRoot->isActiveWindow() || otoTimer->isActive()) {
        otoBlock.push(path);
        return;
    }
    handleBlocks();
}

void VoiceBankTab::handleOtoDirChangedCore(QString path) {
    if (!isDirExist(path)) {
        dataArea->removeTable(path);
    } else {
        if (!dataArea->refreshTable(path)) {
            dataArea->addTable(path, voicebank.OtoLevels.value(path)->otoData());
        }
    }
}

void VoiceBankTab::onOtoTimer() {
    otoTimer->stop();
    handleBlocks();
}

void VoiceBankTab::handleBlocks() {
    if (otoBlock.isEmpty()) {
        return;
    }
    otoTimer->start(1000); // Handle change only once within 1 second

    QStringList paths = otoBlock.all();
    otoBlock.clear();

    for (QString &path : paths) {
        handleOtoDirChangedCore(path);
    }
}
