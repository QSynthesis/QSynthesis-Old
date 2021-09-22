#include "../KeyTableTab.h"
#include "Tabs/KeyboardTab.h"
#include "mainwindow.h"

#include <QAction>

void KeyTableTab::resetAllShortcuts() {
    QList<QPair<int, QString>> pairs;
    int i = 0;
    for (auto it = m_defaultShortcuts.begin(); it != m_defaultShortcuts.end(); ++it, ++i) {
        pairs.append(qMakePair(i, it->toString()));
    }
    saveShortcutsCore(pairs);
}

void KeyTableTab::resetSelectedShortcuts() {
    QList<QPair<int, QString>> pairs;

    const QList<QTableWidgetSelectionRange> &ranges = table->selectedRanges();
    for (int i = 0; i < ranges.size(); ++i) {
        const QTableWidgetSelectionRange &range = ranges.at(i);
        for (int j = range.topRow(); j <= range.bottomRow(); ++j) {
            pairs.append(qMakePair(j, m_defaultShortcuts.at(j).toString()));
        }
    }
    saveShortcutsCore(pairs);
}

void KeyTableTab::callForChange() {
    m_tab->change();
}

void KeyTableTab::saveShortcutCore(int index, const QString &text) {
    saveShortcutsCore({qMakePair(index, text)});
}

void KeyTableTab::saveShortcutsCore(const QList<QPair<int, QString>> &pairs) {
    KeyOperation *ko = nullptr;
    for (auto it = pairs.begin(); it != pairs.end(); ++it) {
        int index = it->first;
        QString text = it->second;

        QTableWidgetItem *item = table->item(index, 1);

        // New Operation
        KeyOperation *k = new KeyOperation();

        // Save Information
        k->setIndex(qMakePair(tabWidget()->indexOf(this), index));
        k->setOrigin(item->text());
        k->setModified(text);

        // Update Front-end
        setShortcutAtRow(index, text);

        if (!ko) {
            ko = k;
        } else {
            ko->setTail(k);
        }
    }

    int i = 0;
    for (KeyOperation *it = ko; it; it = it->next()) {
        i++;
    }
    saveOperation(ko);
}
