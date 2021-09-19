#ifndef KEYBOARDTAB_H
#define KEYBOARDTAB_H

#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>

#include "CentralTab.h"
#include "Controls/SwitchButton.h"
#include "File/ShortcutsFile.h"
#include "KeyboardTabs/Contents/KeyTableTab.h"
#include "KeyboardTabs/Operations/KeyOperation.h"

class KeyboardActionList;

// Keyboard Mapping Tab Class
class KeyboardTab : public CentralTab {
    Q_OBJECT

public:
    explicit KeyboardTab(CentralTabWidget *parent = nullptr);
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

private:
    void handleFileChanged();

protected:
    void updateMenuRoot() override;
    void updateMenuCore() override;

    // Core
private:
    void loadCore();
    void saveCore();

    // Init
private:
    void initTab();
    void initComponents();
    void initValues();

private:
    QHBoxLayout *switchLayout;
    QVBoxLayout *switchLineLayout;

    QVBoxLayout *mainLayout;
    TabWidget *mainWidget;

    KeyTableTab *commonKeyTab;
    KeyTableTab *projectKeyTab;
    KeyTableTab *voiceKeyTab;

    SwitchButton *sBtnCommon;
    SwitchButton *sBtnProject;
    SwitchButton *sBtnVoice;
    SwitchButtonGroup *sBtnGroup;
    SwitchButtonUnderline *sBtnUnderline;

    QPushButton *btnReset;

    void handleSwitched();
    void handleResetCurrent();

    // Edit
public:
    void undo() override;
    void redo() override;

    bool earliest() const;
    bool latest() const;

    // Methods for Notes Area
    void addHistory(KeyOperation *k);
    void clearHistory();

private:
    // Save History for undo and redo
    QVector<KeyOperation *> historyList;
    int historyIndex;

    int savedHistoryIndex;

public:
    void handleOperation(KeyOperation *k, bool undo);
};

#endif // KEYBOARDTAB_H
