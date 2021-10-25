#ifndef TUNINGTAB_H
#define TUNINGTAB_H

#include <QAudioOutput>
#include <QClipboard>
#include <QJsonDocument>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QMimeData>
#include <QObject>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>

#include "../Central/CentralTab.h"
#include "Actions/TuningActionList.h"
#include "Controls/Others/TemporaryMenu.h"
#include "MiniSystem/MiniSystemNotifier.h"
#include "PluginInfo.h"
#include "Process/RealtimeRenderer.h"
#include "QUtauRender.h"
#include "SequenceTextFile.h"
#include "VoiceBank/QOtoReference.h"

class TuningGroup;
class TuneOperation;

class EditorForm;
class ParamsForm;
class TracksForm;
class FormSplitter;

class ProjectInfoHandler;

// Main Editing Tab Class
class TuningTab : public CentralTab {
    Q_OBJECT
public:
    explicit TuningTab(CentralTabWidget *parent = nullptr);
    ~TuningTab();

    TuningActionList *tabActions;

    SequenceTextFile ustFile;
    QOtoReference *oto;

private:
    MiniSystemNotifier *notifier;

    void addNotifier();
    void removeNotifier();

public:
    bool load() override; // All load function will be called only once
    bool save() override;
    bool saveAs(const QString &filename) override;
    bool restore() override;

    void awake() override;
    void sleep() override;

    void enter() override;
    void leave() override;

    void newFile(const SectionNotes &notes);
    void appendFile(const SectionNotes &notes);

    void setFilename(const QString &value) override;
    TuningGroup *ptrs() const;

protected:
    void setEdited(bool value) override; // Set the status of edited

    void setTabName(const QString &value) override;
    void updateTabName() override;

    void updateMenuRoot() override;
    void updateStatusRoot() override;
    void updateMenuCore() override;

    void updatePasteMenu();

    void handleSavedStateChanged() override;

private:
    void handleFileChanged(const QStringList &files);

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
    void showCharsetSettings();

private:
    ProjectInfoHandler *projectInfo;

    SectionSettings currentSettings() const;
    void setCurrentSettings(const SectionSettings &sectionSettings) const;

    // Init
private:
    void initTab(); // Common initialization for building function

    void initComponents();
    void initValues();
    void initWorkingDir();

private:
    QVBoxLayout *mainLayout;
    FormSplitter *mainSplitter;

    ParamsForm *paramsForm;
    TracksForm *tracksForm;
    EditorForm *editorForm;

    TuningGroup *m_ptrs;

    // Modify
public:
    void showNoteProperty();
    void resetNoteProperty();

    void showLyricInsertion();

    void showTempoEdit(bool remove = false);

    void insertRest();
    void removeRest();

    void setP2P3Fade();
    void setP1P4Fade();
    void resetEnvelope();

    void transpose(int offset = 0);

    void selectAlias();

    // Plugin
public:
    void selectPlugin();
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

    void handleFormStatusChanged();

    bool isFree() const;
    bool isFreeButPlaying() const;

    void setLengthUnit(int n);

    void switchNoteVisibility();
    void switchPitchVisibility();
    void switchEnvelopeVisibility();
    void switchParamsVisibility();

    void showPlayHeadOnly();
    void showPlayHeadCenter();

    void showSpriteAdjust();
    void showFindReplace();

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
    bool externModified;

    // Render
private:
    QString m_workingDir;

private:
    bool renderCore();
    bool renderSelection();

    void fixRenderArgs(RenderArgs &args);

    // Play
private:
    double m_startTime;

public:
    // Preview
    void play() override;
    void replay() override;
    void stop() override;

    qint64 duration() const;
    qint64 position() const;

    bool isPlaying() const;

private:
    void forcePausePlaying();

public:
    // Realtime
    void updateCache(int tick);

    bool isRendered(int index) const;
    bool isNotRendered(int index) const;

    void removeCacheFrom(int index);
    void removeCacheAt(int index);
    void removeCacheWithin(int x, int y);
    void clearCache();

private:
    void initAudio();
    void quitAudio();

    void updateCacheCore(int index, int length = -1);
    void updateBufferCore(int toIndex);

    void handleWorkFinished(int seq, const QString &filename);

private:
    QSet<int> renderingWorks;
    QMap<int, QString> renderedWorks;

    RealtimeRenderer *renderer;
    QTimer *audioTimer;

    QAudioOutput *m_audio;
    QIODevice *m_audioBuf;

    QByteArray m_audioData;
    int m_startBuffer;
    int m_startIndex, m_processedIndex;

    double m_audioDelay, m_audioTail;

    void initRenderer();

    void handleAudioTimeout();
    void handleAudioStateChanged(QAudio::State state);

    // Oto
public:
    void switchToOtoReferenceMap(const QString &voiceDir);

private:
    void handleOtoRefreshed();
};

#endif // TUNINGTAB_H
