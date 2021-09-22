#include "BaseActionList.h"

BaseActionList::BaseActionList(QObject *parent) : QObject(parent) {
}

BaseActionList::~BaseActionList() {
}

void BaseActionList::updateCommonStrings() {
    // File
    newFile->setText(tr("New"));
    importFile->setText(tr("Import..."));
    openFile->setText(tr("Open File..."));
    openFolder->setText(tr("Open Voice Bank..."));
    saveFile->setText(tr("Save"));
    saveAsFile->setText(tr("Save as..."));
    restoreFile->setText(tr("Restore"));
    switchFile->setText(tr("Switch"));
    closeFile->setText(tr("Close"));

    QString fileType = tr("File");
    textToName(newFile, fileType);
    textToName(importFile, fileType);
    textToName(openFile, fileType);
    textToName(openFolder, fileType);
    textToName(saveFile, fileType);
    textToName(saveAsFile, fileType);
    textToName(restoreFile, fileType);
    textToName(switchFile, fileType);
    textToName(closeFile, fileType);

    recentMenu->setTitle(tr("Recent"));

    // Edit
    undo->setText(tr("Undo"));
    redo->setText(tr("Redo"));
    selectAll->setText(tr("Select all"));
    deselect->setText(tr("Deselect"));

    QString editType = tr("Edit");
    textToName(undo, editType);
    textToName(redo, editType);
    textToName(selectAll, editType);
    textToName(deselect, editType);

    // Modify
    reset->setText(tr("Reset"));

    QString modifyType = tr("Modify");
    textToName(reset, modifyType);

    // Preview
    playPause->setText(tr("Play/pause"));
    replay->setText(tr("Replay"));
    stop->setText(tr("Stop"));

    QString previewType = tr("Preview");
    textToName(playPause, previewType);
    textToName(replay, previewType);
    textToName(stop, previewType);

    // Tools
    settings->setText(tr("Settings"));
    keyShortcuts->setText(tr("Keyboard shortcuts"));
    themes->setText(tr("Color themes"));
    languages->setText(tr("Languages"));

    QString toolsType = tr("Tools");
    textToName(settings, toolsType);
    textToName(keyShortcuts, toolsType);
    textToName(themes, toolsType);
    textToName(languages, toolsType);

    preferenceMenu->setTitle(tr("Preferences"));

    // Help
    welcome->setText(tr("Welcome"));
    instructions->setText(tr("Instructions"));
    checkUpdate->setText(tr("Check update"));
    aboutApp->setText(tr("About QSynthesis"));
    aboutQt->setText(tr("About Qt"));

    QString helpType = tr("Help");
    textToName(welcome, helpType);
    textToName(instructions, helpType);
    textToName(checkUpdate, helpType);
    textToName(aboutApp, helpType);
    textToName(aboutQt, helpType);
}

void BaseActionList::makeCommonDefaultShortcuts() {
    QList<QAction *> actions = commonActions();
    for (QAction *action : actions) {
        action->setShortcut(QKeySequence(""));
    }

    newFile->setShortcut(QKeySequence("Ctrl+N"));
    saveFile->setShortcut(QKeySequence("Ctrl+S"));
    saveAsFile->setShortcut(QKeySequence("Ctrl+Shift+S"));
    switchFile->setShortcut(QKeySequence("Shift+Tab"));
    closeFile->setShortcut(QKeySequence("Ctrl+W"));

    undo->setShortcut(QKeySequence("Ctrl+Z"));
    redo->setShortcut(QKeySequence("Ctrl+Shift+Z"));
    selectAll->setShortcut(QKeySequence("Ctrl+A"));

    playPause->setShortcut(QKeySequence("Space"));
    replay->setShortcut(QKeySequence("Shift+F5"));
    stop->setShortcut(QKeySequence("F7"));

    settings->setShortcut(QKeySequence("Ctrl+,"));
    keyShortcuts->setShortcut(QKeySequence("Ctrl+Shift+K"));
    themes->setShortcut(QKeySequence("Ctrl+Shift+T"));
    languages->setShortcut(QKeySequence("Ctrl+Shift+L"));
}

QList<QKeySequence> BaseActionList::commonDefaultShortcuts() {
    BaseActionList actionList;
    QList<QAction **> actionsRef = actionList.commonActionsRef();
    QList<QKeySequence> shortcuts;

    // Create
    for (auto it = actionsRef.begin(); it != actionsRef.end(); ++it) {
        QAction **ref = *it;
        *ref = new QAction();
    }
    // Set
    actionList.makeCommonDefaultShortcuts();
    // Export
    shortcuts = actionList.commonShortcuts();
    // Destroy
    for (auto it = actionsRef.begin(); it != actionsRef.end(); ++it) {
        QAction **ref = *it;
        delete *ref;
    }

    return shortcuts;
}

QList<QAction *> BaseActionList::commonActions() const {
    const QList<QAction **> actionsRef = ((BaseActionList *) this)->commonActionsRef();
    QList<QAction *> actions;
    for (auto it = actionsRef.begin(); it != actionsRef.end(); ++it) {
        actions.append(**it);
    }
    return actions;
}

QList<QAction **> BaseActionList::commonActionsRef() {
    return {
        &newFile,      &importFile, &openFile,  &openFolder, &saveFile,     &saveAsFile,
        &restoreFile,  &switchFile, &closeFile, &undo,       &redo,         &selectAll,
        &deselect,     &reset,      &playPause, &replay,     &stop,         &settings,
        &keyShortcuts, &themes,     &languages, &welcome,    &instructions, &checkUpdate,
        &aboutApp,     &aboutQt,
    };
}

void BaseActionList::setCommonActionsEnabled(bool enabled) {
    const QList<QAction *> actions = this->commonActions();
    QStringList res;
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        (*it)->setEnabled(enabled);
    }
}

QStringList BaseActionList::commonNames() const {
    const QList<QAction *> actions = this->commonActions();
    QStringList res;
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        res.append((*it)->data().toString());
    }
    return res;
}

QList<QKeySequence> BaseActionList::commonShortcuts() const {
    const QList<QAction *> actions = this->commonActions();
    QList<QKeySequence> res;
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        res.append((*it)->shortcut());
    }
    return res;
}

void BaseActionList::setCommonShortcuts(const QList<QKeySequence> &keys) const {
    const QList<QAction *> actions = this->commonActions();
    auto it0 = keys.begin();
    for (auto it = actions.begin(); it != actions.end(); ++it, ++it0) {
        (*it)->setShortcut(*it0);
    }
}

void BaseActionList::setNaturalStatus() {
}

void BaseActionList::updateStrings() {
}

void BaseActionList::makeDefaultShortcuts() {
}

QList<QAction *> BaseActionList::actions() const {
    const QList<QAction **> actionsRef = ((BaseActionList *) this)->actionsRef();
    QList<QAction *> actions;
    for (auto it = actionsRef.begin(); it != actionsRef.end(); ++it) {
        actions.append(*(*it));
    }
    return actions;
}

QList<QAction **> BaseActionList::actionsRef() {
    return {};
}

void BaseActionList::setActionsEnabled(bool enabled) {
    const QList<QAction *> actions = this->actions();
    QStringList res;
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        (*it)->setEnabled(enabled);
    }
}

QList<QKeySequence> BaseActionList::shortcuts() const {
    const QList<QAction *> actions = this->actions();
    QList<QKeySequence> res;
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        res.append((*it)->shortcut());
    }
    return res;
}

QStringList BaseActionList::names() const {
    const QList<QAction *> actions = this->actions();
    QStringList res;
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        res.append((*it)->data().toString());
    }
    return res;
}

void BaseActionList::setShortcuts(const QList<QKeySequence> &keys) {
    const QList<QAction *> actions = this->actions();
    auto it0 = keys.begin();
    for (auto it = actions.begin(); it != actions.end(); ++it, ++it0) {
        (*it)->setShortcut(*it0);
    }
}

void BaseActionList::textToName(QAction *action, const QString &menu) {
    QString text = action->text();
    if (text.endsWith("...")) {
        text = text.mid(0, text.size() - 3);
    }
    action->setData(menu + " - " + text);
}
