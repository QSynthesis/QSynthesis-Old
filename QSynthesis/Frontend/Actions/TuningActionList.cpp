#include "TuningActionList.h"

Q_SINGLETON_DECLARE(TuningActionList)

TuningActionList::TuningActionList(QObject *parent) : BaseActionList(parent) {
    createCasePrivate();
}

TuningActionList::TuningActionList(Qs::VariableSource source) {
    Q_ASSERT(source == Qs::Default);
}

TuningActionList::~TuningActionList() {
}
void TuningActionList::setNaturalStatus() {
    setCommonActionsEnabled(true);
    setActionsEnabled(true);

    fullAdsorb->setCheckable(true);
    halfAdsorb->setCheckable(true);
    quarterAdsorb->setCheckable(true);
    sixthAdsorb->setCheckable(true);
    eighthAdsorb->setCheckable(true);
    twelfthAdsorb->setCheckable(true);
    sixteenthAdsorb->setCheckable(true);
    twentyForthAdsorb->setCheckable(true);
    thirtySecondAdsorb->setCheckable(true);
    noAdsorb->setCheckable(true);

    switchNoteState->setCheckable(true);
    switchPitchState->setCheckable(true);
    switchEnvelopeState->setCheckable(true);
    switchParamsState->setCheckable(true);

    playHeadDisplay->setCheckable(true);
    playHeadCenter->setCheckable(true);
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
    openBuildInList->setText(tr("Open build-in tools list"));
    openPluginList->setText(tr("Open plug-in list"));
    openAliasList->setText(tr("Open alias list"));
    switchTrack->setText(tr("Switch to overview mode"));
    switchConfig->setText(tr("Switch to configuration mode"));
    switchNote->setText(tr("Switch to note mode"));
    switchPitch->setText(tr("Switch to pitch mode"));
    switchEnvelope->setText(tr("Switch to envelope mode"));
    switchInt->setText(tr("Switch to intensity mode"));
    switchMod->setText(tr("Switch to modulation mode"));
    switchVel->setText(tr("Switch to velocity mode"));

    QString shortcutsType = tr("Shortcut");
    textToName(openBuildInList, shortcutsType);
    textToName(openPluginList, shortcutsType);
    textToName(openAliasList, shortcutsType);
    textToName(switchTrack, shortcutsType);
    textToName(switchConfig, shortcutsType);
    textToName(switchNote, shortcutsType);
    textToName(switchPitch, shortcutsType);
    textToName(switchEnvelope, shortcutsType);
    textToName(switchInt, shortcutsType);
    textToName(switchMod, shortcutsType);
    textToName(switchVel, shortcutsType);

    // Tracks
    openProjectSettings->setText(tr("Project Settings..."));
    openCharsetSettings->setText(tr("Charset..."));

    QString tracksType = tr("Global");
    textToName(openProjectSettings, tracksType);
    textToName(openCharsetSettings, tracksType);

    // Editor
    adsorbMenu->setTitle(tr("Quantization"));
    stateMenu->setTitle(tr("State"));
    playHeadMenu->setTitle(tr("Playhead"));

    fullAdsorb->setText(tr("Quarter"));
    halfAdsorb->setText(tr("1/2 Quarter"));
    quarterAdsorb->setText(tr("1/4 Quarter"));
    sixthAdsorb->setText(tr("1/6 Quarter"));
    eighthAdsorb->setText(tr("1/8 Quarter"));
    twelfthAdsorb->setText(tr("1/12 Quarter"));
    sixteenthAdsorb->setText(tr("1/16 Quarter"));
    twentyForthAdsorb->setText(tr("1/24 Quarter"));
    thirtySecondAdsorb->setText(tr("1/32 Quarter"));
    noAdsorb->setText(tr("None"));

    switchNoteState->setText(tr("Display note block"));
    switchPitchState->setText(tr("Display pitch curves"));
    switchEnvelopeState->setText(tr("Display envelope"));
    switchParamsState->setText(tr("Display parameters"));

    playHeadDisplay->setText(tr("Page display"));
    playHeadCenter->setText(tr("Slide display"));

    showSpriteAdjust->setText(tr("Adjust foreground"));

    QString editorType = tr("Piano Roll");

    QString adsorbType = editorType + nameConnector + adsorbMenu->title();
    textToName(fullAdsorb, adsorbType);
    textToName(halfAdsorb, adsorbType);
    textToName(quarterAdsorb, adsorbType);
    textToName(sixthAdsorb, adsorbType);
    textToName(eighthAdsorb, adsorbType);
    textToName(twelfthAdsorb, adsorbType);
    textToName(sixteenthAdsorb, adsorbType);
    textToName(twentyForthAdsorb, adsorbType);
    textToName(thirtySecondAdsorb, adsorbType);
    textToName(noAdsorb, adsorbType);

    QString stateType = editorType + nameConnector + stateMenu->title();
    textToName(switchNoteState, stateType);
    textToName(switchPitchState, stateType);
    textToName(switchEnvelopeState, stateType);
    textToName(switchParamsState, stateType);

    QString playHeadType = editorType + nameConnector + playHeadMenu->title();
    textToName(playHeadDisplay, playHeadType);
    textToName(playHeadCenter, playHeadType);

    textToName(showSpriteAdjust, editorType);
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

    openAliasList->setShortcut(QKeySequence("V"));
    openBuildInList->setShortcut(QKeySequence("B"));
    openPluginList->setShortcut(QKeySequence("N"));

    switchNote->setShortcut(QKeySequence("Q"));
    switchPitch->setShortcut(QKeySequence("W"));
    switchEnvelope->setShortcut(QKeySequence("E"));

    switchInt->setShortcut(QKeySequence("A"));
    switchMod->setShortcut(QKeySequence("S"));
    switchVel->setShortcut(QKeySequence("D"));

    switchNoteState->setShortcut(QKeySequence("X"));
    switchParamsState->setShortcut(QKeySequence("Z"));
    switchEnvelope->setShortcut(QKeySequence("C"));

    showSpriteAdjust->setShortcut(QKeySequence("Ctrl+Shift+F"));
}

QList<QKeySequence> TuningActionList::defaultShortcuts() {
    TuningActionList actionList(Qs::Default);
    QList<QAction **> actionsRef = actionList.actionsRef();
    QList<QKeySequence> shortcuts;

    // Create
    for (auto it = actionsRef.begin(); it != actionsRef.end(); ++it) {
        QAction **ref = *it;
        *ref = new QAction();
    }
    // Set
    actionList.makeDefaultShortcuts();
    // Export
    shortcuts = actionList.shortcuts();
    // Destroy
    for (auto it = actionsRef.begin(); it != actionsRef.end(); ++it) {
        QAction **ref = *it;
        delete *ref;
    }

    return shortcuts;
}

QList<QAction **> TuningActionList::actionsRef() {
    return {
        &appendFile,
        &exportSelection,
        &exportTrack,
        &copy,
        &cut,
        &paste,
        &remove,
        &insertLyrics,
        &findReplace,
        &transpose,
        &octaveUp,
        &octaveDown,
        &removeRest,
        &insertRest,
        &p2p3Fade,
        &p1p4Fade,
        &resetEnvelope,
        &noteProperty,
        &moveStart,
        &moveEnd,
        &removeCache,
        &exportAudio,
        &lyricConfig,
        &prefixConfig,
        &openBuildInList,
        &openPluginList,
        &openAliasList,
        &switchTrack,
        &switchConfig,
        &switchNote,
        &switchPitch,
        &switchEnvelope,
        &switchInt,
        &switchMod,
        &switchVel,
        &openProjectSettings,
        &openCharsetSettings,
        &fullAdsorb,
        &halfAdsorb,
        &quarterAdsorb,
        &sixthAdsorb,
        &eighthAdsorb,
        &twelfthAdsorb,
        &sixteenthAdsorb,
        &twentyForthAdsorb,
        &thirtySecondAdsorb,
        &noAdsorb,
        &switchNoteState,
        &switchPitchState,
        &switchEnvelopeState,
        &switchParamsState,
        &playHeadDisplay,
        &playHeadCenter,
        &showSpriteAdjust,
    };
}
