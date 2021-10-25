#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QActionGroup>
#include <QDateTime>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QGraphicsSceneEvent>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QObject>
#include <QSharedMemory>
#include <QTranslator>

#include "CentralTabWidget.h"
#include "QUtils.h"
#include "SequenceTextFile.h"

class WelcomeTab;
class TuningTab;
class VoiceBankTab;
class KeyboardTab;
class SettingTab;

class WelcomeActionList;
class TuningActionList;
class VoiceActionList;
class KeyboardActionList;
class SettingActionList;

#define qRoot MainWindow::instance()

class MainWindow : public QMainWindow {
    Q_OBJECT
    Q_SINGLETON(MainWindow)

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Construct
public:
    void initAndShow();
    void freeAndQuit();

private:
    void initWindow();
    void quitWindow();

    void initValues();

    // Exec
public:
    void fromCommandLine(const QStringList &args); // Load from command line
    void fromApplication();

    // Tabs
public:
    CentralTabWidget *tabs;

    WelcomeTab *addWelcomeTab();   // Open welcome tab
    KeyboardTab *addKeyboardTab(); // Open keyboard tab
    SettingTab *addSettingTab();   // Open setting tab

    TuningTab *addEmptyTab(const SectionNotes &oNotes = SectionNotes()); // Open empty ust project
    TuningTab *addTuningTab(const QString &filename); // Open project

    VoiceBankTab *addVoiceBankTab(const QString &filename = "",
                                  bool notify = true); // Open voice bank

    bool addMultipleTabs(const QStringList &filenames); // Open multiple projects or folders

    void removeTab(CentralTab *tab); // Close tab
    void removeTab(int index);

    inline CentralTab *currentTab() {
        return tabs->currentTab();
    }
    inline CentralTab *previousTab() {
        return tabs->previousTab();
    }
    inline CentralTab *tabAt(int index) {
        return tabs->tabAt(index);
    }

private:
    void initTabs();

    int findTuningTab(const QString &filename);
    int findVoiceBankTab(const QString &dirname, Qs::DirRelation *relation);
    int findSpecialTab(CentralTab::TabType type);

    WelcomeTab *createWelcomeTab();
    SettingTab *createSettingTab();
    KeyboardTab *createKeyboardTab();
    VoiceBankTab *createVoiceBankTab(const QString &filename);
    TuningTab *createTuningTab(const QString &filename = "");

private:
    int untitledCount; // Untitled projects count

    QString incUntitled();
    QString decUntitled(); // Never used

    void makeUntitled(TuningTab *tab, const QString &name = "");

private:
    bool handleTabCloseRequent(int index);
    void handleTabIndexChanged(int index);
    void handleTabNameChanged(int index, const QString &newName);
    void handleTabPressed(int index, Qt::MouseButton button);

    // Menu
private:
    QMenu *fileMenu, *editMenu, *viewMenu, *modifyMenu, *previewMenu, *toolMenu, *helpMenu;

    WelcomeActionList *welcomeActions;
    TuningActionList *tuningActions;
    VoiceActionList *voiceActions;
    KeyboardActionList *keyboardActions;
    SettingActionList *settingActions;

private:
    void initMenuBar();
    void initActionLists();
    void setCurrentActions(Qs::MainTabs type);

private:
    void handleNewFile();
    void handleImportFile();
    void handleOpenFile();
    void handleOpenFolder();
    void handleSaveFile();
    void handleSaveAsFile();
    void handleRestoreFile();
    void handleSwitchFile();
    void handleCloseFile();

    void handleUndo();
    void handleRedo();
    void handleSelectAll();
    void handleDeselect();

    void handleReset();

    void handlePlayPause();
    void handleReplay();
    void handleStop();

    void handleOpenSettings();
    void handleOpenKeyShortcuts();
    void handleOpenThemes();
    void handleOpenLanguages();

    void handleOpenWelcome();
    void handleInstructions();
    void handleCheckUpdate();
    void handleAboutApp();
    void handleAboutQt();

    // Tuning
    void handleAppendFile();
    void handleExportSelection();
    void handleExportTrack();

    void handleCopyNotes();
    void handleCutNotes();
    void handlePasteNotes();
    void handleRemoveNotes();

    void handleInsertLyrics();
    void handleFindReplace();
    void handleTranspose();
    void handleOctaveUp();
    void handleOctaveDown();
    void handleRemoveRest();
    void handleInsertRest();
    void handleP2P3Fade();
    void handleP1P4Fade();
    void handleResetEnvelope();
    void handleNoteProperty();

    void handleMoveToStart();
    void handleMoveToEnd();
    void handleRemoveCache();
    void handleExportAudio();

    void handleLyricConfig();
    void handlePrefixConfig();

    void handleOpenBuildInMenu();
    void handleOpenPluginMenu();
    void handleOpenAliasMenu();

    void handleSwitchTrack();
    void handleSwitchConfig();

    void handleSwitchNote();
    void handleSwitchPitch();
    void handleSwitchEnvelope();

    void handleSwitchInt();
    void handleSwitchMod();
    void handleSwitchVel();

    void handleOpenProjectSettings();
    void handleOpenCharsetSettings();

    void handleFullAdsorb();
    void handleHalfAdsorb();
    void handleQuarterAdsorb();
    void handleSixthAdsorb();
    void handleEighthAdsorb();
    void handleTwelfthAdsorb();
    void handleSixteenthAdsorb();
    void handleTwentyForthAdsorb();
    void handleThirtySecondAdsorb();
    void handleNoneAdsorb();

    void handleSwitchNoteVisibility();
    void handleSwitchPitchVisibility();
    void handleSwitchEnvelopeVisibility();
    void handleSwitchParamsVisibility();

    void handlePlayHeadDisplay();
    void handlePlayHeadCenter();

    void handleShowSpriteAdjust();

    // Voice Bank
    void handleExportCurrent();

    void handleMoveUpSample();
    void handleMoveDownSample();
    void handleMoveTopSample();
    void handleMoveBottomSample();
    void handleDuplicateSample();
    void handleRemoveSample();

    void handleGenerateFrq();
    void handleModifyAlias();
    void handleRemoveInvalidSamples();

    void handleSetOffset();
    void handleSetOverlap();
    void handleSetPreUttr();
    void handleSetConstant();
    void handleSetBlank();

    void handleOpenRecentFile();   // Temporary
    void handleMoreRecentFile();   // Temporary
    void handleMoreRecentFolder(); // Temporary
    void handleClearRecentMenu();  // Temporary

    void handleExecutePlugin(); // Temporary
    void handleOpenPluginDir(); // Temporary

public:
    void reloadMenu();
    void reloadShortcuts();
    void reloadConfig();

    // File
private:
    bool execOpen();
    bool execOpenFolder();
    bool execSave(CentralTab *tab);
    bool execSaveAs(TuningTab *tab);
    bool execImport();

    // States
private:
    // Methods called when tab changed
    void reloadTitle();

public:
    // Methods called when welcome tab changed
    void clearRecentMenu();
    void reloadRecentMenu();

    // Events
private:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
    void changeEvent(QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    // Modules
private:
    void initModules();
    void freeModules();

    void initConfig();
    void initShortcuts();
    void initSettingIni();

    void saveSettingIni();

    void reloadVoice();
    void reloadPlugins();
    void reloadThemes();
    void reloadLanguages();

    void initMemory();

signals:
    void awake();
    void sleep();
};

#endif // MAINWINDOW_H
