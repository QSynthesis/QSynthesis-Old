#ifndef TUNINGTAB_H
#define TUNINGTAB_H

#include <QClipboard>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QObject>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>

#include "CentralTab.h"
#include "Directory/PluginInfo.h"
#include "File/SequenceTextFile.h"
#include "Render/RenderArgs.h"
#include "Templates/TemporaryMenu.h"
#include "VoiceBank/QOtoReference.h"

class TuningGroup;
class TuneOperation;

class EditorForm;
class ParamsForm;
class TracksForm;
class FormSplitter;
class TuningActionList;

class ProjectInfoHandler;

// Main Editing Tab Class
class TuningTab : public CentralTab {
    Q_OBJECT
public:
    explicit TuningTab(TabWidget *parent = nullptr);
    ~TuningTab();

    TuningActionList *tabActions;

    SequenceTextFile ustFile;
    QOtoReference *oto;

public:
    bool load() override; // All load function will be called only once
    bool save() override;
    bool saveAs(const QString &filename) override;
    bool restore() override;

    void awake() override;
    void sleep() override;

    void newFile(const SectionNotes &notes);
    void appendFile(const SectionNotes &notes);

    void setFilename(const QString &value) override;
    TuningGroup *ptrs() const;

private:
    void handleFileChanged();

    // Proeperties
public:
    QString fullFileName() const;

    bool isUntitled() const;
    void setUntitled(bool value);

    bool isDeleted() const;
    void setDeleted(bool value);

    QString workingDir() const;

    QString defaultCacheDir() const;
    QString relativeCacheDir() const;

    QString tempAudioFile() const;

protected:
    void setEdited(bool value) override; // Set the status of edited

    void setTabName(const QString &value) override;
    void updateTabName() override;

    void updateMenuRoot() override;
    void updateStatusRoot() override;
    void updateMenuCore() override;

    void updatePasteMenu();

    // Core
private:
    void loadCore();
    void saveCore();
    void exitCore();

    bool saveOrSaveAs(const QString &filename);
    bool saveTempFile();

    // Project Settings
public:
    void showProjectSettings();

private:
    ProjectInfoHandler *projectInfo;

    SectionSettings currentSettings() const;
    void setCurrentSettings(const SectionSettings &sectionSettings) const;

    // Init
private:
    void initTab(); // Common initialization for building function

    void initComponents();
    void initPlayer();
    void initValues();
    void initWorkingDir();

private:
    QVBoxLayout *mainLayout;
    FormSplitter *mainSplitter;

    ParamsForm *paramsForm;
    TracksForm *tracksForm;
    EditorForm *editorForm;

    TemporaryMenu *m_tempMenu;

    TuningGroup *m_ptrs;

    // Modify
public:
    void showNoteProperty();
    void resetNoteProperty();

    void showLyricInsertion();

    void showTempoEdit(bool remove = false);
    void showProjectCharset();

    void insertRest();
    void removeRest();

    void setP2P3Fade();
    void setP1P4Fade();
    void resetEnvelope();

    void transpose(int offset = 0);
    void modifyAlias();

    // Plugin
public:
    void handleRunPlugin(const PluginInfo &plugin);

    // Unchange
public:
    void moveToStart();
    void moveToEnd();

    void removeAllCaches();
    void exportRecentAudio();

    void configueLyric();
    void configuePrefix();

    void switchTrackStatus(Qs::Panels::Tracks status);
    void switchEditorStatus(Qs::Panels::Editor status);
    void switchParamsStatus(Qs::Panels::Params status);

public:
    // Edit
    void undo() override;
    void redo() override;
    void selectAll() override;
    void deselect() override;

    void reset() override;

    void copy();
    void cut();
    void paste();
    void remove();

    bool earliest() const;
    bool latest() const;

    void addHistory(TuneOperation *n);
    void clearHistory();

private:
    QVector<TuneOperation *> historyList;
    int historyIndex;

    int savedHistoryIndex;

protected:
    bool untitled;
    bool deleted;

    // Render
private:
    QMap<int, RenderArgs> savedRenderArgs;
    QList<RenderArgs> currentRenderArgs;

    QString m_workingDir;

private:
    bool renderCore();

    void renderBefore();
    bool renderSelection();

    // Play
private:
    QMediaPlayer *m_player;

    bool m_playing;
    bool m_playable;

public:
    // Preview
    void play() override;
    void replay() override;
    void stop() override;

    void pause();
    void resume();

    bool isPlaying() const;
    void setPlaying(bool playing);

    void setPlayable(bool playable);
    void onPlaying(qint64 n);

private:
    void handleStateChanged(QMediaPlayer::State newState);
    void handleStatusChanged(QMediaPlayer::MediaStatus newStatus);

    // Oto
public:
    void switchToOtoReferenceMap(const QString &voiceDir);

private:
    void handleOtoRefreshed();
};

#endif // TUNINGTAB_H
