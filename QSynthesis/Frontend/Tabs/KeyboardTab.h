#ifndef KEYBOARDTAB_H
#define KEYBOARDTAB_H

#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>

#include "CentralTab.h"
#include "File/ShortcutsFile.h"
#include "KeyboardTabs/KeyboardTabContent.h"

#include "KeyboardTabs/Operations/KeyOperation.h"

class KeyboardActionList;

// Keyboard Mapping Tab Class
class KeyboardTab : public CentralTab {
    Q_OBJECT

public:
    explicit KeyboardTab(TabWidget *parent = nullptr);
    ~KeyboardTab();

    KeyboardActionList *tabActions;

    ShortcutsFile cfg;
    ShortcutsData keys;

public:
    bool load() override;
    bool save() override;
    bool restore() override;

    void awake() override;
    void sleep() override;

    void enter() override;
    void leave() override;

    void setFilename(const QString &value) override;
    void setFixedname(const QString &value) override;

    void undo() override;
    void redo() override;

    bool earliest() const;
    bool latest() const;

    // Methods for Notes Area
    void addHistory(KeyOperation *k);
    void clearHistory();

protected:
    void updateMenuRoot() override;
    void updateMenuCore() override;

private:
    QVBoxLayout *mainLayout;
    KeyboardTabContent *mainWidget;

private:
    // Save History for undo and redo
    QVector<KeyOperation *> historyList;
    int historyIndex;

    int savedHistoryIndex;

public:
    void handleKeyModified(int row, QString key);
    void handleOperation(KeyOperation *k, bool undo);
};

#endif // KEYBOARDTAB_H
