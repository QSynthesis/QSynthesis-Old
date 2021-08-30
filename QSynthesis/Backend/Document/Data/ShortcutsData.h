#ifndef SHORTCUTSDATA_H
#define SHORTCUTSDATA_H

#include <QKeySequence>
#include <QObject>

class ShortcutsData {
public:
    QKeySequence newFileShortcut;
    QKeySequence importFileShortcut;
    QKeySequence openFileShortcut;
    QKeySequence openFolderFileShortcut;
    QKeySequence saveFileShortcut;
    QKeySequence saveAsFileShortcut;
    QKeySequence restoreFileShortcut;
    QKeySequence appendFileShortcut;
    QKeySequence exportSelectionShortcut;
    QKeySequence exportTotalShortcut;
    QKeySequence closeFileShortcut;

    QKeySequence undoEditShortcut;
    QKeySequence redoEditShortcut;
    QKeySequence copyEditAction;
    QKeySequence cutEditShortcut;
    QKeySequence pasteEditShortcut;
    QKeySequence deleteEditShortcut;
    QKeySequence selectAllEditShortcut;
    QKeySequence deselectEditShortcut;

    QKeySequence lyricModifyShortcut;
    QKeySequence findModifyShortcut;
    QKeySequence pitchModifyShortcut;
    QKeySequence octaveUpModifyShortcut;
    QKeySequence octaveDownModifyShortcut;
    QKeySequence restRemoveModifyShortcut;
    QKeySequence restInsertModifyShortcut;

    QKeySequence offsetModifyShortcut;
    QKeySequence overlapModifyShortcut;
    QKeySequence preUttrModifyShortcut;
    QKeySequence constantModifyShortcut;
    QKeySequence blankModifyShortcut;

    QKeySequence playPreviewShortcut;
    QKeySequence replayPreviewShortcut;
    QKeySequence stopPreviewShortcut;
    QKeySequence moveToStartPreviewShortcut;
    QKeySequence moveToEndPreviewShortcut;
    QKeySequence removeCachePreviewShortcut;
    QKeySequence exportPreviewShortcut;

    QKeySequence voiceBankToolShortcut;
    QKeySequence prefixMapToolShortcut;
    QKeySequence propertiesToolShortcut;
    QKeySequence settingsToolShortcut;
    QKeySequence keyboardToolShortcut;
    QKeySequence themeToolShortcut;
    QKeySequence languageToolShortcut;

    QKeySequence welcomeHelpShortcut;
    QKeySequence instructHelpShortcut;
    QKeySequence checkUpdateShortcut;
    QKeySequence aboutQtHelpShortcut;
    QKeySequence aboutAppHelpShortcut;

    QKeySequence aliasShortcut;
    QKeySequence buildInShortcut;
    QKeySequence pluginsShortcut;

    ShortcutsData();

    static QString nameForId(int id);

    static int idStart();
    static int idEnd();

    QKeySequence keyForId(int id) const;
    void setKeyForId(int id, const QKeySequence &key);
};

#endif // SHORTCUTSDATA_H
