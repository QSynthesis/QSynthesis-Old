#include "../KeyboardTab.h"

void KeyboardTab::undo() {
    bool success = true;
    if (!earliest()) {
        KeyOperation *k = historyList.at(historyIndex - 1);
        int tabIndex = k->index().first;
        if (keyTabAt(tabIndex)->handleOperation(k)) {
            mainWidget->setCurrentIndex(tabIndex);
            success = true;
        }
        if (success) {
            historyIndex--;
            setEdited(savedHistoryIndex != historyIndex);
        }
    }
}

void KeyboardTab::redo() {
    bool success = true;
    if (!latest()) {
        KeyOperation *k = historyList.at(historyIndex);
        int tabIndex = k->index().first;
        if (qobject_cast<KeyTableTab *>(mainWidget->tabAt(tabIndex))->handleOperation(k, false)) {
            mainWidget->setCurrentIndex(tabIndex);
            success = true;
        }
        if (success) {
            historyIndex++;
            setEdited(savedHistoryIndex != historyIndex);
        }
    }
}

void KeyboardTab::selectAll() {
    currentKeyTab()->selectAll();
}

void KeyboardTab::deselect() {
    currentKeyTab()->selectNone();
}

void KeyboardTab::reset() {
    currentKeyTab()->resetSelectedShortcuts();
}

bool KeyboardTab::earliest() const {
    return historyIndex == 0;
}

bool KeyboardTab::latest() const {
    return historyIndex == historyList.size();
}

void KeyboardTab::addHistory(KeyOperation *k) {
    // Saved status doesn't exist
    if (savedHistoryIndex > historyIndex) {
        savedHistoryIndex = -1;
    }
    // Remove all operations after
    while (historyList.size() > historyIndex) {
        delete historyList.back();
        historyList.pop_back();
    }
    historyList.append(k);
    historyIndex++;

    handleSavedStateChanged();
    setEdited(savedHistoryIndex != historyIndex);
}

void KeyboardTab::clearHistory() {
    for (int i = historyList.size() - 1; i >= 0; --i) {
        delete historyList.at(i);
    }
    historyList.clear();
    historyIndex = 0;
    savedHistoryIndex = 0;
}
