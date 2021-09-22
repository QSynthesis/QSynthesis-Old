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
    QAction *openBuildInMenu;
    QAction *openPluginMenu;
    QAction *openAliasMenu;

    QAction *switchTrack;
    QAction *switchConfig;

    QAction *switchNote;
    QAction *switchPitch;
    QAction *switchEnvelope;

    QAction *switchInt;
    QAction *switchMod;
    QAction *switchVel;

public:
    void setNaturalStatus() override;

    void updateStrings() override;
    void makeDefaultShortcuts() override;

    static QList<QKeySequence> defaultShortcuts();

    QList<QAction **> actionsRef() override;
};

#endif // TUNINGACTIONLIST_H
