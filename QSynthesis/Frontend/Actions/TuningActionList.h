#ifndef TUNINGACTIONLIST_H
#define TUNINGACTIONLIST_H

#include "BaseActionList.h"

class TuningActionList : public BaseActionList {
    Q_OBJECT
    Q_SINGLETON(TuningActionList)
public:
    TuningActionList(QObject *parent = nullptr);

    ~TuningActionList();

private:
    TuningActionList(Qs::VariableSource source);

public:
    // File
    QAction *appendFile;
    QAction *exportSelection;
    QAction *exportTrack;

    QMenu *exportMenu;

    // Edit
    QAction *copy;
    QAction *cut;
    QAction *paste;
    QAction *remove;

    // Modify
    QAction *insertLyrics;
    QAction *findReplace;
    QAction *transpose;
    QAction *octaveUp;
    QAction *octaveDown;
    QAction *removeRest;
    QAction *insertRest;
    QAction *p2p3Fade;
    QAction *p1p4Fade;
    QAction *resetEnvelope;
    QAction *noteProperty;

    // Preview
    QAction *moveStart;
    QAction *moveEnd;
    QAction *removeCache;
    QAction *exportAudio;

    // Tools
    QAction *lyricConfig;
    QAction *prefixConfig;

    QMenu *buildInMenu; // *
    QMenu *pluginMenu;  // *

    // Help

    // Shortcuts
    QAction *openBuildInList;
    QAction *openPluginList;
    QAction *openAliasList;

    QAction *switchTrack;
    QAction *switchConfig;

    QAction *switchNote;
    QAction *switchPitch;
    QAction *switchEnvelope;

    QAction *switchInt;
    QAction *switchMod;
    QAction *switchVel;

    // Tracks
    QMenu *tracksMenu;

    QAction *openProjectSettings;
    QAction *openCharsetSettings;

    // Editor
    QMenu *editorMenu;

    QMenu *adsorbMenu;
    QMenu *stateMenu;
    QMenu *playHeadMenu;

    QAction *fullAdsorb;
    QAction *halfAdsorb;
    QAction *quarterAdsorb;
    QAction *sixthAdsorb;
    QAction *eighthAdsorb;
    QAction *twelfthAdsorb;
    QAction *sixteenthAdsorb;
    QAction *twentyForthAdsorb;
    QAction *thirtySecondAdsorb;
    QAction *noAdsorb;

    QAction *switchNoteState;
    QAction *switchPitchState;
    QAction *switchEnvelopeState;
    QAction *switchParamsState;

    QAction *playHeadDisplay;
    QAction *playHeadCenter;

    QAction *showSpriteAdjust;

public:
    void setNaturalStatus() override;

    void updateStrings() override;
    void makeDefaultShortcuts() override;

    static QList<QKeySequence> defaultShortcuts();

    QList<QAction **> actionsRef() override;
};

#endif // TUNINGACTIONLIST_H
