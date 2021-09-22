#include "../KeyTableTab.h"
#include "Tabs/KeyboardTab.h"
#include "mainwindow.h"

#include <QAction>

void KeyTableTab::openContextMenu() {
    QAction *modifyAction = new QAction(tr("Modify key bind"), m_menu);
    QAction *removeAction = new QAction(tr("Remove key bind"), m_menu);
    QAction *resetAction = new QAction(tr("Reset key bind"), m_menu);

    connect(modifyAction, &QAction::triggered, this, &KeyTableTab::handleModifyKeyBind);
    connect(removeAction, &QAction::triggered, this, &KeyTableTab::handleRemoveKeyBind);
    connect(resetAction, &QAction::triggered, this, &KeyTableTab::handleResetKeyBind);

    m_menu->addAction(modifyAction);
    m_menu->addAction(removeAction);
    m_menu->addAction(resetAction);

    m_menu->exec(QCursor::pos());
    m_menu->clear();
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

    if (key == 0) {
        return;
    }

    QKeySequence shortcut(key + modifiers);
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
