#include "ShortcutsData.h"

Q_SINGLETON_DECLARE(ShortcutsData)

ShortcutsData::ShortcutsData() {
    newFileShortcut = QKeySequence("");
    importFileShortcut = QKeySequence("");
    openFileShortcut = QKeySequence("");
    openFolderFileShortcut = QKeySequence("");
    saveFileShortcut = QKeySequence("Ctrl+S");
    saveAsFileShortcut = QKeySequence("Ctrl+Shift+S");
    restoreFileShortcut = QKeySequence("");
    appendFileShortcut = QKeySequence("");
    exportSelectionShortcut = QKeySequence("");
    exportTotalShortcut = QKeySequence("");
    closeFileShortcut = QKeySequence("Ctrl+W");

    undoEditShortcut = QKeySequence("Ctrl+Z");
    redoEditShortcut = QKeySequence("Ctrl+Shift+Z");
    copyEditAction = QKeySequence("Ctrl+C");
    cutEditShortcut = QKeySequence("Ctrl+X");
    pasteEditShortcut = QKeySequence("Ctrl+V");
    deleteEditShortcut = QKeySequence("Del");
    selectAllEditShortcut = QKeySequence("Ctrl+A");
    deselectEditShortcut = QKeySequence("");

    lyricModifyShortcut = QKeySequence("Ctrl+L");
    findModifyShortcut = QKeySequence("Ctrl+F");
    pitchModifyShortcut = QKeySequence("");
    octaveUpModifyShortcut = QKeySequence("");
    octaveDownModifyShortcut = QKeySequence("");
    restRemoveModifyShortcut = QKeySequence("");
    restInsertModifyShortcut = QKeySequence("Ctrl+R");

    offsetModifyShortcut = QKeySequence("F1");
    overlapModifyShortcut = QKeySequence("F2");
    preUttrModifyShortcut = QKeySequence("F3");
    constantModifyShortcut = QKeySequence("F4");
    blankModifyShortcut = QKeySequence("F5");

    playPreviewShortcut = QKeySequence("Space");
    replayPreviewShortcut = QKeySequence("Shift+F5");
    stopPreviewShortcut = QKeySequence("F7");
    moveToStartPreviewShortcut = QKeySequence("");
    moveToEndPreviewShortcut = QKeySequence("");
    removeCachePreviewShortcut = QKeySequence("");
    exportPreviewShortcut = QKeySequence("Ctrl+Shift+P");

    voiceBankToolShortcut = QKeySequence("Ctrl+G");
    prefixMapToolShortcut = QKeySequence("");
    propertiesToolShortcut = QKeySequence("Ctrl+E");
    settingsToolShortcut = QKeySequence("");
    keyboardToolShortcut = QKeySequence("");
    themeToolShortcut = QKeySequence("");
    languageToolShortcut = QKeySequence("");

    welcomeHelpShortcut = QKeySequence("");
    instructHelpShortcut = QKeySequence("");
    checkUpdateShortcut = QKeySequence("");
    aboutQtHelpShortcut = QKeySequence("");
    aboutAppHelpShortcut = QKeySequence("");

    aliasShortcut = QKeySequence("V");
    buildInShortcut = QKeySequence("B");
    pluginsShortcut = QKeySequence("N");
}

ShortcutsData::~ShortcutsData() {
}

QString ShortcutsData::nameForId(int id) {
    QString res;
    switch (id) {
    case 0:
        res = QObject::tr("File-New");
        break;
    case 1:
        res = QObject::tr("File-Import");
        break;
    case 2:
        res = QObject::tr("File-Open");
        break;
    case 3:
        res = QObject::tr("File-Open Voice Bank");
        break;
    case 4:
        res = QObject::tr("File-Save");
        break;
    case 5:
        res = QObject::tr("File-Save As");
        break;
    case 6:
        res = QObject::tr("File-Restore");
        break;
    case 7:
        res = QObject::tr("File-Append");
        break;
    case 8:
        res = QObject::tr("File-Export Selection");
        break;
    case 9:
        res = QObject::tr("File-Export Track");
        break;
    case 10:
        res = QObject::tr("File-Close");
        break;
    case 11:
        res = QObject::tr("Edit-Undo");
        break;
    case 12:
        res = QObject::tr("Edit-Redo");
        break;
    case 13:
        res = QObject::tr("Edit-Copy");
        break;
    case 14:
        res = QObject::tr("Edit-Cut");
        break;
    case 15:
        res = QObject::tr("Edit-Paste");
        break;
    case 16:
        res = QObject::tr("Edit-Delete");
        break;
    case 17:
        res = QObject::tr("Edit-Deselect");
        break;
    case 18:
        res = QObject::tr("Modify-Insert Lyrics");
        break;
    case 19:
        res = QObject::tr("Modify-Find/Replace");
        break;
    case 20:
        res = QObject::tr("Modify-Transpose");
        break;
    case 21:
        res = QObject::tr("Modify-Octave Up");
        break;
    case 22:
        res = QObject::tr("Modify-Octave Down");
        break;
    case 23:
        res = QObject::tr("Modify-Remove Rests");
        break;
    case 24:
        res = QObject::tr("Modify-Insert Rests");
        break;
    case 25:
        res = QObject::tr("Modify-Set Offset");
        break;
    case 26:
        res = QObject::tr("Modify-Set Overlap");
        break;
    case 27:
        res = QObject::tr("Modify-Set Pre-Utterance");
        break;
    case 28:
        res = QObject::tr("Modify-Set Consonant");
        break;
    case 29:
        res = QObject::tr("Modify-Set Blank");
        break;
    case 30:
        res = QObject::tr("Preview-Play/Pause");
        break;
    case 31:
        res = QObject::tr("Preview-Replay");
        break;
    case 32:
        res = QObject::tr("Preview-Stop");
        break;
    case 33:
        res = QObject::tr("Preview-Move To Start");
        break;
    case 34:
        res = QObject::tr("Modify-Move To End");
        break;
    case 35:
        res = QObject::tr("Modify-Remove Cache");
        break;
    case 36:
        res = QObject::tr("Modify-Export Recent Audio");
        break;
    case 37:
        res = QObject::tr("Tools-Voice Bank Config");
        break;
    case 38:
        res = QObject::tr("Tools-Prefix Map Config");
        break;
    case 39:
        res = QObject::tr("Tools-Variable Properties");
        break;
    case 40:
        res = QObject::tr("Tools-Settings");
        break;
    case 41:
        res = QObject::tr("Tools-Keyboard Shortcuts");
        break;
    case 42:
        res = QObject::tr("Tools-Color Theme");
        break;
    case 43:
        res = QObject::tr("Tools-Languages");
        break;
    case 44:
        res = QObject::tr("Help-Welcome");
        break;
    case 45:
        res = QObject::tr("Help-Instructions");
        break;
    case 46:
        res = QObject::tr("Help-Check Update");
        break;
    case 47:
        res = QObject::tr("Help-About QSynthesis");
        break;
    case 48:
        res = QObject::tr("Help-About Qt");
        break;
    case 49:
        res = QObject::tr("Build-in Tools");
        break;
    case 50:
        res = QObject::tr("Plugins");
        break;
    case 51:
        res = QObject::tr("Similar Samples");
        break;
    default:
        break;
    }

    return res;
}

int ShortcutsData::idStart() {
    return 0;
}

int ShortcutsData::idEnd() {
    return 52;
}

QKeySequence ShortcutsData::keyForId(int id) const {
    QKeySequence res("");
    switch (id) {
    case 0:
        res = newFileShortcut;
        break;
    case 1:
        res = importFileShortcut;
        break;
    case 2:
        res = openFileShortcut;
        break;
    case 3:
        res = openFolderFileShortcut;
        break;
    case 4:
        res = saveFileShortcut;
        break;
    case 5:
        res = saveAsFileShortcut;
        break;
    case 6:
        res = restoreFileShortcut;
        break;
    case 7:
        res = appendFileShortcut;
        break;
    case 8:
        res = exportSelectionShortcut;
        break;
    case 9:
        res = exportTotalShortcut;
        break;
    case 10:
        res = closeFileShortcut;
        break;
    case 11:
        res = undoEditShortcut;
        break;
    case 12:
        res = redoEditShortcut;
        break;
    case 13:
        res = copyEditAction;
        break;
    case 14:
        res = cutEditShortcut;
        break;
    case 15:
        res = pasteEditShortcut;
        break;
    case 16:
        res = deleteEditShortcut;
        break;
    case 17:
        res = deselectEditShortcut;
        break;
    case 18:
        res = lyricModifyShortcut;
        break;
    case 19:
        res = findModifyShortcut;
        break;
    case 20:
        res = pitchModifyShortcut;
        break;
    case 21:
        res = octaveUpModifyShortcut;
        break;
    case 22:
        res = octaveDownModifyShortcut;
        break;
    case 23:
        res = restRemoveModifyShortcut;
        break;
    case 24:
        res = restInsertModifyShortcut;
        break;
    case 25:
        res = offsetModifyShortcut;
        break;
    case 26:
        res = overlapModifyShortcut;
        break;
    case 27:
        res = preUttrModifyShortcut;
        break;
    case 28:
        res = constantModifyShortcut;
        break;
    case 29:
        res = blankModifyShortcut;
        break;
    case 30:
        res = playPreviewShortcut;
        break;
    case 31:
        res = replayPreviewShortcut;
        break;
    case 32:
        res = stopPreviewShortcut;
        break;
    case 33:
        res = moveToStartPreviewShortcut;
        break;
    case 34:
        res = moveToEndPreviewShortcut;
        break;
    case 35:
        res = removeCachePreviewShortcut;
        break;
    case 36:
        res = exportPreviewShortcut;
        break;
    case 37:
        res = voiceBankToolShortcut;
        break;
    case 38:
        res = prefixMapToolShortcut;
        break;
    case 39:
        res = propertiesToolShortcut;
        break;
    case 40:
        res = settingsToolShortcut;
        break;
    case 41:
        res = keyboardToolShortcut;
        break;
    case 42:
        res = themeToolShortcut;
        break;
    case 43:
        res = languageToolShortcut;
        break;
    case 44:
        res = welcomeHelpShortcut;
        break;
    case 45:
        res = instructHelpShortcut;
        break;
    case 46:
        res = checkUpdateShortcut;
        break;
    case 47:
        res = aboutAppHelpShortcut;
        break;
    case 48:
        res = aboutQtHelpShortcut;
        break;
    case 49:
        res = aliasShortcut;
        break;
    case 50:
        res = buildInShortcut;
        break;
    case 51:
        res = pluginsShortcut;
        break;
    default:
        break;
    }

    return res;
}

void ShortcutsData::setKeyForId(int id, const QKeySequence &key) {
    switch (id) {
    case 0:
        newFileShortcut = key;
        break;
    case 1:
        importFileShortcut = key;
        break;
    case 2:
        openFileShortcut = key;
        break;
    case 3:
        openFolderFileShortcut = key;
        break;
    case 4:
        saveFileShortcut = key;
        break;
    case 5:
        saveAsFileShortcut = key;
        break;
    case 6:
        restoreFileShortcut = key;
        break;
    case 7:
        appendFileShortcut = key;
        break;
    case 8:
        exportSelectionShortcut = key;
        break;
    case 9:
        exportTotalShortcut = key;
        break;
    case 10:
        closeFileShortcut = key;
        break;
    case 11:
        undoEditShortcut = key;
        break;
    case 12:
        redoEditShortcut = key;
        break;
    case 13:
        copyEditAction = key;
        break;
    case 14:
        cutEditShortcut = key;
        break;
    case 15:
        pasteEditShortcut = key;
        break;
    case 16:
        deleteEditShortcut = key;
        break;
    case 17:
        deselectEditShortcut = key;
        break;
    case 18:
        lyricModifyShortcut = key;
        break;
    case 19:
        findModifyShortcut = key;
        break;
    case 20:
        pitchModifyShortcut = key;
        break;
    case 21:
        octaveUpModifyShortcut = key;
        break;
    case 22:
        octaveDownModifyShortcut = key;
        break;
    case 23:
        restRemoveModifyShortcut = key;
        break;
    case 24:
        restInsertModifyShortcut = key;
        break;
    case 25:
        offsetModifyShortcut = key;
        break;
    case 26:
        overlapModifyShortcut = key;
        break;
    case 27:
        preUttrModifyShortcut = key;
        break;
    case 28:
        constantModifyShortcut = key;
        break;
    case 29:
        blankModifyShortcut = key;
        break;
    case 30:
        playPreviewShortcut = key;
        break;
    case 31:
        replayPreviewShortcut = key;
        break;
    case 32:
        stopPreviewShortcut = key;
        break;
    case 33:
        moveToStartPreviewShortcut = key;
        break;
    case 34:
        moveToEndPreviewShortcut = key;
        break;
    case 35:
        removeCachePreviewShortcut = key;
        break;
    case 36:
        exportPreviewShortcut = key;
        break;
    case 37:
        voiceBankToolShortcut = key;
        break;
    case 38:
        prefixMapToolShortcut = key;
        break;
    case 39:
        propertiesToolShortcut = key;
        break;
    case 40:
        settingsToolShortcut = key;
        break;
    case 41:
        keyboardToolShortcut = key;
        break;
    case 42:
        themeToolShortcut = key;
        break;
    case 43:
        languageToolShortcut = key;
        break;
    case 44:
        welcomeHelpShortcut = key;
        break;
    case 45:
        instructHelpShortcut = key;
        break;
    case 46:
        checkUpdateShortcut = key;
        break;
    case 47:
        aboutAppHelpShortcut = key;
        break;
    case 48:
        aboutQtHelpShortcut = key;
        break;
    case 49:
        aliasShortcut = key;
        break;
    case 50:
        buildInShortcut = key;
        break;
    case 51:
        pluginsShortcut = key;
        break;
    default:
        break;
    }
}
