#include "../KeyTableTab.h"
#include "Tabs/KeyboardTab.h"
#include "mainwindow.h"

#include <QAction>

void KeyTableTab::openContextMenu() {
    QStringList list{tr("Modify key bind"), tr("Remove key bind"), tr("Reset key bind")};
    TemporaryMenu *menu = new TemporaryMenu(list, this);
    int index = menu->start();
    menu->deleteLater();

    switch (index) {
    case 0:
        handleModifyKeyBind();
        break;
    case 1:
        handleRemoveKeyBind();
        break;
    case 2:
        handleResetKeyBind();
        break;
    default:
        break;
    }
}

void KeyTableTab::handleModifyKeyBind() {
    int row = table->currentRow();

    KeyModifyDialog *dlg = new KeyModifyDialog(this);

    int code = dlg->exec();

    int key = dlg->key();
    int modifiers = dlg->modifiers();

    dlg->deleteLater();

    if (code != 1) {
        return;
    }

    if (modifiers == 0 && AppAssistant::isSpecialKey(static_cast<Qt::Key>(key))) {
        return;
    }

    if (key == 0) {
        return;
    }

    QKeySequence shortcut(modifiers + key);
    saveShortcutCore(row, shortcut.toString());
}

void KeyTableTab::handleRemoveKeyBind() {
    saveShortcutCore(table->currentRow(), "");
}

void KeyTableTab::handleResetKeyBind() {
    int row = table->currentRow();
    saveShortcutCore(row, m_defaultShortcuts.at(row).toString());
}

void KeyTableTab::handleCellDoubleClicked(int row, int column) {
    handleModifyKeyBind();
}

void KeyTableTab::handleSelectionChanged() {
    callForChange();

    QList<QTableWidgetSelectionRange> ranges = table->selectedRanges();
    QList<int> rows;
    for (int i = 0; i < ranges.size(); ++i) {
        const QTableWidgetSelectionRange &range = ranges.at(i);
        for (int j = range.topRow(); j <= range.bottomRow(); ++j) {
            rows.append(j);
        }
    }
}
