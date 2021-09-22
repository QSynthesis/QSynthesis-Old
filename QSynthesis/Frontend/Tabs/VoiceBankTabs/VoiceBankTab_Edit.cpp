#include "../VoiceBankTab.h"
#include "Operations/NonOtoOperation.h"
#include "Operations/OtoOperation.h"

void VoiceBankTab::undo() {
    bool success = true;
    if (!earliest()) {
        VoiceOperation *v = historyList.at(historyIndex - 1);
        switch (v->type()) {
        case VoiceOperation::NonOto: {
            NonOtoOperation *no = static_cast<NonOtoOperation *>(v);
            success = infoArea->handleOperation(no);
            break;
        }
        case VoiceOperation::Oto: {
            OtoOperation *o = static_cast<OtoOperation *>(v);
            success = dataArea->handleOperation(o);
            break;
        }
        default:
            break;
        }
        if (success) {
            historyIndex--;
            setEdited(savedHistoryIndex != historyIndex);
        }
    }
}

void VoiceBankTab::redo() {
    bool success = true;
    if (!latest()) {
        VoiceOperation *v = historyList.at(historyIndex);
        switch (v->type()) {
        case VoiceOperation::NonOto: {
            NonOtoOperation *no = static_cast<NonOtoOperation *>(v);
            success = infoArea->handleOperation(no, false);
            break;
        }
        case VoiceOperation::Oto: {
            OtoOperation *o = static_cast<OtoOperation *>(v);
            success = dataArea->handleOperation(o, false);
            break;
        }
        default:
            break;
        }
        if (success) {
            historyIndex++;
            setEdited(savedHistoryIndex != historyIndex);
        }
    }
}

void VoiceBankTab::selectAll() {
    dataArea->currentTab()->selectAll();
}

void VoiceBankTab::deselect() {
    dataArea->currentTab()->selectNone();
}

bool VoiceBankTab::earliest() {
    return historyIndex == 0;
}

bool VoiceBankTab::latest() {
    return historyIndex == historyList.size();
}

void VoiceBankTab::addHistory(VoiceOperation *s) {
    // Saved status doesn't exist
    if (savedHistoryIndex > historyIndex) {
        savedHistoryIndex = -1;
    }
    // Remove all operations after
    while (historyList.size() > historyIndex) {
        delete historyList.back();
        historyList.pop_back();
    }
    historyList.append(s);
    historyIndex++;

    handleSavedStateChanged();
    setEdited(savedHistoryIndex != historyIndex);
}

void VoiceBankTab::clearHistory() {
    for (int i = historyList.size() - 1; i >= 0; --i) {
        delete historyList.at(i);
    }
    historyList.clear();
    historyIndex = 0;
    savedHistoryIndex = 0;
}
