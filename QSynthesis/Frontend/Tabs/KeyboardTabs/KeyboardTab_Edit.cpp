#include "../KeyboardTab.h"
#include "mainwindow.h"

void KeyboardTab::undo() {
    if (!earliest()) {
        KeyOperation *k = historyList[historyIndex - 1];
        handleOperation(k, true);
        historyIndex--;
    }
    setEdited(savedHistoryIndex != historyIndex);
    updateMenuCore();
}

void KeyboardTab::redo() {
    if (!latest()) {
        KeyOperation *k = historyList[historyIndex];
        handleOperation(k, false);
        historyIndex++;
    }
    setEdited(savedHistoryIndex != historyIndex);
    updateMenuCore();
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

    setEdited(savedHistoryIndex != historyIndex);
}

void KeyboardTab::clearHistory() {
    for (int i = historyList.size() - 1; i >= 0; --i) {
        delete historyList.at(i);
    }
    historyList.clear();
    historyIndex = 0;
    savedHistoryIndex = -1;
}
