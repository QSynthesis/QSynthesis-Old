#include "../../KeyboardTab.h"
#include "../KeyTableTab.h"

#include <QAction>

void KeyTableTab::saveOperation(KeyOperation *k) {
    k = static_cast<KeyOperation *>(k->simplify(k));
    if (k) {
        m_tab->addHistory(k);
    } else {
        qDebug() << "[Key Operation]"
                 << "Addition Refused";
    }
}

bool KeyTableTab::handleOperation(KeyOperation *k, bool undo) {
    selectNone();
    executeOperation(k, undo);
    return true;
}

void KeyTableTab::executeOperation(KeyOperation *k, bool undo) {
    // Undo: next prior
    if (k->next() && undo) {
        executeOperation(k->next(), undo);
    }

    // Execute
    int row = k->index().second;
    QString text = undo ? k->origin() : k->modified();

    setShortcutAtRow(row, text);
    selectRow(row);

    // Redo: prev prior
    if (k->next() && !undo) {
        executeOperation(k->next(), undo);
    }
}
