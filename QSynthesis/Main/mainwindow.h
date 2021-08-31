#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Customs/TopComboBox.h"
#include "Directory/PluginsCollect.h"
#include "Directory/VoiceCollect.h"
#include "Document/QSFileData.h"
#include "File/NormalFileCollect.h"
#include "File/SettingIniFile.h"
#include "Import/QMidiFile.h"
#include "Plugin/PluginHandler.h"
#include "QSActions.h"
#include "QSTabs.h"
#include "QUtauUtils.h"
#include "QUtils.h"
#include "Tabs/CentralTabs/CentralTabWidget.h"
#include "VoiceBank/QOtoReference.h"

#include <QAction>
#include <QActionGroup>
#include <QDateTime>
#include <QDebug>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QMimeData>
#include <QObject>
#include <QSharedMemory>
#include <QTranslator>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Construct
public:
    void initAndShow();
    void beforeDelete();

private:
    void initValues();
    void initWindow();

    // Import
public:
    // Parse MIDI file
    bool parseMidiFile(const QString &filename, SectionNotes &oNotes);
    // Parse Synthesizer V project
    bool parseSynthVFile(const QString &filename, bool svp, SectionNotes &oNotes);
    // Parse Vocaloid project
    bool parseVocaloidFile(const QString &filename, bool vsqx, SectionNotes &oNotes);

    // Tabs
public:
    CentralTabWidget *tabs;

    WelcomeTab *addWelcomeTab();   // Open welcome tab
    KeyboardTab *addKeyboardTab(); // Open keyboard tab
    SettingTab *addSettingTab();   // Open setting tab

    TuningTab *addEmptyTab(const SectionNotes &oNotes = SectionNotes()); // Open empty ust project
    bool addMultipleTabs(const QStringList &filenames); // Open multiple projects or folders

    TuningTab *addTuningTab(const QString &filename,
                            bool noCloseIfInvalid = true); // Open project
    VoiceBankTab *addVoiceBankTab(const QString &filename = "",
                                  bool notify = true); // Open voice bank

    void removeTab(CentralTab *tab); // Close tab
    void removeTab(int index);

    inline CentralTab *currentTab() {
        BaseTab *w = tabs->currentWidget();
        return qobject_cast<CentralTab *>(w);
    }
    inline CentralTab *tabAt(int index) {
        BaseTab *w = tabs->tabAt(index);
        return qobject_cast<CentralTab *>(w);
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

    void handleOpenRecentFile();  // Temporary
    void handleClearRecentMenu(); // Temporary

    void handleExecutePlugin(); // Temporary
    void handleOpenPluginDir(); // Temporary

public:
    void reloadMenu();
    void reloadShortcuts();

    // Exec
public:
    void fromCommandLine(int argc, char **argv); // Load from command line
    void fromApplication();

private:
    bool execOpen();
    bool execOpenFolder();
    bool execSave(CentralTab *tab);
    bool execSaveAs(TuningTab *tab);
    bool execImport();

    // Refresh
public:
    // Methods called when file system changed
    void reloadConfig();
    void reloadVoice();
    void reloadPlugins();

    // Methods called when tab changed
    void reloadTitle();

    // Methods called when welcome tab changed
    void clearRecentMenu();
    void reloadRecentMenu();

    // Modules
public:
    TopComboBox *previewer;

private:
    void initPreviewer();
    void updatePreviewer();
    void showPreviewer();

    void initStyleSheet();

    // Events
private:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
    void changeEvent(QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    // Static
public:
    static SettingIniData settingIni;
    static ConfigData config;
    static ShortcutsData shortcuts;

    static void initSettingIni();
    static void saveSettingIni();

    static void initShortcutsData();
    static void initConfigData();

    static void initVoice();
    static void initPlugins();

    static void initThemes();
    static void initLanguages();

public:
    // File Filters
    static void reloadBackendStrings();

public:
    static QSharedMemory sharedMemory;

    static void exitOnNoIOPermission();
    static void exitOnVoiceDirMissing();
    static void exitOnPluginsDirMissing();
    static void exitOnConfigDirMissing();

    static void checkWorkingDir();
    static void checkTemporaryDir();

    static void exitPreparation();
};

#endif // MAINWINDOW_H
