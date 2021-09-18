#ifndef VOICEACTIONLIST_H
#define VOICEACTIONLIST_H

#include "BaseActionList.h"

class VoiceActionList : public BaseActionList {
    Q_OBJECT
    Q_SINGLETON(VoiceActionList)
public:
    VoiceActionList(QObject *parent = nullptr);
    ~VoiceActionList();

public:
    // File
    QAction *exportCurrent;

    // Edit
    QAction *moveUp;
    QAction *moveDown;
    QAction *moveTop;
    QAction *moveBottom;
    QAction *duplicate;
    QAction *remove;

    // Modify
    QAction *generateFrq;
    QAction *modifyAlias;
    QAction *removeInvalid;
    QAction *setOffset;
    QAction *setOverlap;
    QAction *setPreUttr;
    QAction *setConstant;
    QAction *setBlank;

    // Preview

    // Tools
    QMenu *buildInMenu; //*

    // Help

public:
    void setNaturalStatus() override;

    void updateStrings() override;
    void makeDefaultShortcuts() override;
    QList<QAction *> actions() const override;
};

#endif // VOICEACTIONLIST_H
