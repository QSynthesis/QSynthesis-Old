#ifndef KEYTABLETAB_H
#define KEYTABLETAB_H

#include <QAction>
#include <QHeaderView>
#include <QMenu>
#include <QTableWidget>
#include <QVBoxLayout>

#include "../Operations/KeyOperation.h"
#include "KeyModifyDialog.h"
#include "Tabs/BaseTab.h"

class KeyboardTab;

class KeyTableTab : public BaseTab {
    Q_OBJECT
public:
    explicit KeyTableTab(KeyboardTab *tab, TabWidget *parent = nullptr);
    virtual ~KeyTableTab();

    void addShortcutData(QAction *action);
    void removeAllData();

public:
    void saveOperation(KeyOperation *k);
    bool handleOperation(KeyOperation *k, bool undo = true);

private:
    void executeOperation(KeyOperation *k, bool undo);

public:
    QList<QKeySequence> defaultShortcuts() const;
    void setDefaultShortcuts(const QList<QKeySequence> &defaultShortcuts);

    QList<QKeySequence> currentShortcuts() const;

    void resetAllShortcuts();
    void resetSelectedShortcuts();

public:
    void callForChange();

private:
    KeyboardTab *m_tab;

    QVBoxLayout *mainLayout;
    QTableWidget *table;

    QList<QKeySequence> m_defaultShortcuts;

public:
    void selectAll();
    void selectNone();
    void selectRow(int row);

    QList<QTableWidgetSelectionRange> selectedRanges() const;

    QString nameAtRow(int row) const;
    QString shortcutAtRow(int row) const;
    Qs::VariableSource sourceAtRow(int row) const;

    void setNameAtRow(int row, const QString &name);
    void setShortcutAtRow(int row, const QString &text);

private:
    void openContextMenu();
    void handleModifyKeyBind();
    void handleRemoveKeyBind();
    void handleResetKeyBind();

    void handleCellDoubleClicked(int row, int column);
    void handleSelectionChanged();

    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void saveShortcutCore(int index, const QString &text);
    void saveShortcutsCore(const QList<QPair<int, QString>> &pairs);
};

#endif // KEYTABLETAB_H
