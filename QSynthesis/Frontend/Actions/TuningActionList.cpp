#include "TuningActionList.h"

Q_SINGLETON_DECLARE(TuningActionList)

TuningActionList::TuningActionList(QObject *parent) : BaseActionList(parent) {
    createCasePrivate();
}

TuningActionList::~TuningActionList() {
}

void TuningActionList::setNaturalStatus() {
    setCommonActionsEnabled(true);
    setActionsEnabled(true);
}

void TuningActionList::updateStrings() {
    // File
    appendFile->setText(tr("Append..."));
    exportSelection->setText(tr("Export selection..."));
    exportTrack->setText(tr("Export entire track..."));

    QString fileType = tr("File");
    textToName(appendFile, fileType);
    textToName(exportSelection, fileType);
    textToName(exportTrack, fileType);

    exportMenu->setTitle(tr("Export"));

    // Edit
    copy->setText(tr("Copy"));
    cut->setText(tr("Cut"));
    paste->setText(tr("Paste"));
    remove->setText(tr("Delete"));

    QString editType = tr("Edit");
    textToName(copy, editType);
    textToName(cut, editType);
    textToName(paste, editType);
    textToName(remove, editType);

    // Modify
    insertLyrics->setText(tr("Insert lyrics..."));
    findReplace->setText(tr("Find/replace"));
    transpose->setText(tr("Transpose..."));
    octaveUp->setText(tr("Shift up by an octave"));
    octaveDown->setText(tr("Shift down by an octave"));
    removeRest->setText(tr("Remove rest..."));
    insertRest->setText(tr("Insert rest"));
    p2p3Fade->setText(tr("Envelope crossFade (p2p3)"));
    p1p4Fade->setText(tr("Envelope crossFade (p1p4)"));
    resetEnvelope->setText(tr("Reset Envelope"));
    noteProperty->setText(tr("Note properties..."));

    QString modifyType = tr("Modify");
    textToName(insertLyrics, modifyType);
    textToName(findReplace, modifyType);
    textToName(transpose, modifyType);
    textToName(octaveUp, modifyType);
    textToName(octaveDown, modifyType);
    textToName(removeRest, modifyType);
    textToName(insertRest, modifyType);
    textToName(p2p3Fade, modifyType);
    textToName(p1p4Fade, modifyType);
    textToName(resetEnvelope, modifyType);
    textToName(noteProperty, modifyType);

    // Preview
    moveStart->setText(tr("Move to start"));
    moveEnd->setText(tr("Move to end"));
    removeCache->setText(tr("Remove cache"));
    exportAudio->setText(tr("Export recent audio"));

    QString previewType = tr("Preview");
    textToName(moveStart, previewType);
    textToName(moveEnd, previewType);
    textToName(removeCache, previewType);
    textToName(exportAudio, previewType);

    // Tools
    lyricConfig->setText(tr("Voice bank configue"));
    prefixConfig->setText(tr("Prefix map configue"));

    QString toolsType = tr("Tools");
    textToName(lyricConfig, toolsType);
    textToName(prefixConfig, toolsType);

    buildInMenu->setTitle(tr("Build-in tools"));
    pluginMenu->setTitle(tr("Plugins"));

    // Help

    // Shortcuts
    openBuildInMenu->setText(tr("Open build-in tools list"));
    openPluginMenu->setText(tr("Open plug-in list"));
    openAliasMenu->setText(tr("Open alias list"));
    switchTrack->setText(tr("Switch to overview mode"));
    switchConfig->setText(tr("Switch to configuration mode"));
    switchNote->setText(tr("Switch to note mode"));
    switchPitch->setText(tr("Switch to pitch mode"));
    switchEnvelope->setText(tr("Switch to envelope mode"));
    switchInt->setText(tr("Switch to intensity mode"));
    switchMod->setText(tr("Switch to modulation mode"));
    switchVel->setText(tr("Switch to velocity mode"));

    QString shortcutsType = tr("Shortcut");
    textToName(openBuildInMenu, shortcutsType);
    textToName(openPluginMenu, shortcutsType);
    textToName(openAliasMenu, shortcutsType);
    textToName(switchTrack, shortcutsType);
    textToName(switchConfig, shortcutsType);
    textToName(switchNote, shortcutsType);
    textToName(switchPitch, shortcutsType);
    textToName(switchEnvelope, shortcutsType);
    textToName(switchInt, shortcutsType);
    textToName(switchMod, shortcutsType);
    textToName(switchVel, shortcutsType);
}

void TuningActionList::makeDefaultShortcuts() {
    copy->setShortcut(QKeySequence("Ctrl+C"));
    cut->setShortcut(QKeySequence("Ctrl+X"));
    paste->setShortcut(QKeySequence("Ctrl+V"));
    remove->setShortcut(QKeySequence("Del"));

    insertLyrics->setShortcut(QKeySequence("Ctrl+L"));
    findReplace->setShortcut(QKeySequence("Ctrl+F"));
    insertRest->setShortcut(QKeySequence("Ctrl+R"));
    noteProperty->setShortcut(QKeySequence("Ctrl+E"));

    exportAudio->setShortcut(QKeySequence("Ctrl+Shift+P"));

    lyricConfig->setShortcut(QKeySequence("Ctrl+G"));

    openAliasMenu->setShortcut(QKeySequence("V"));
    openBuildInMenu->setShortcut(QKeySequence("B"));
    openPluginMenu->setShortcut(QKeySequence("N"));

    switchNote->setShortcut(QKeySequence("Q"));
    switchPitch->setShortcut(QKeySequence("W"));
    switchEnvelope->setShortcut(QKeySequence("E"));

    switchInt->setShortcut(QKeySequence("A"));
    switchMod->setShortcut(QKeySequence("S"));
    switchVel->setShortcut(QKeySequence("D"));
}

QList<QAction *> TuningActionList::actions() const {
    return {
        appendFile,   exportSelection, exportTrack,    copy,           cut,
        paste,        remove,          insertLyrics,   findReplace,    transpose,
        octaveUp,     octaveDown,      removeRest,     insertRest,     noteProperty,
        moveStart,    moveEnd,         removeCache,    exportAudio,    lyricConfig,
        prefixConfig, openBuildInMenu, openPluginMenu, openAliasMenu,  switchTrack,
        switchConfig, switchNote,      switchPitch,    switchEnvelope, switchInt,
        switchMod,    switchVel,
    };
}
