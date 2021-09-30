#ifndef KEYBOARDTAB_H
#define KEYBOARDTAB_H

#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>

#include "Actions/KeyboardActionList.h"
#include "CentralTab.h"
#include "Controls/SwitchButton.h"
#include "Document/ShortcutsFile.h"
#include "KeyboardTabs/Contents/KeyTableTab.h"
#include "KeyboardTabs/Operations/KeyOperation.h"
#include "MiniSystem/MiniSystemNotifier.h"
#include "TabWidget.h"

// Keyboard Mapping Tab Class
class KeyboardTab : public CentralTab {
    Q_OBJECT

public:
    explicit KeyboardTab(CentralTabWidget *parent = nullptr);
    ~KeyboardTab();

    KeyboardActionList *tabActions;

    ShortcutsFile keys;

private:
    MiniSystemNotifier *notifier;

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
    void handleFileChanged(const QStringList &files);

protected:
    void updateMenuRoot() override;
    void updateMenuCore() override;

    // Core
private:
    void loadCore();
    void saveCore();
    void exitCore();

    bool checkNoConflict();

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

    KeyTableTab *keyTabAt(int index) const;
    KeyTableTab *currentKeyTab() const;

    void handleSwitchRequested(bool &accepted);
    void handleSwitched();
    void handleResetCurrent();

    void handleTabIndexChanged(int index);

    // Edit
public:
    void undo() override;
    void redo() override;
    void selectAll() override;
    void deselect() override;

    void reset() override;

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

private:
    bool externModified;
};

#endif // KEYBOARDTAB_H
