#include "mainwindow.h"

void MainWindow::initMenuBar() {
    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    modifyMenu = new QMenu(this);
    previewMenu = new QMenu(this);
    toolMenu = new QMenu(this);
    helpMenu = new QMenu(this);

    QMenuBar *bar = menuBar();
    bar->addMenu(fileMenu);
    bar->addMenu(editMenu);
    bar->addMenu(modifyMenu);
    bar->addMenu(previewMenu);
    bar->addMenu(toolMenu);
    bar->addMenu(helpMenu);
}

void MainWindow::initActionLists() {
    // Action Lists
    welcomeActions = new WelcomeActionList(this);
    tuningActions = new TuningActionList(this);
    voiceActions = new VoiceActionList(this);
    keyboardActions = new KeyboardActionList(this);
    settingActions = new SettingActionList(this);

    // Set Common
    {
        QAction *newFile = new QAction(this);
        QAction *importFile = new QAction(this);
        QAction *openFile = new QAction(this);
        QAction *openFolder = new QAction(this);
        QAction *saveFile = new QAction(this);
        QAction *saveAsFile = new QAction(this);
        QAction *restoreFile = new QAction(this);
        QAction *switchFile = new QAction(this);
        QAction *closeFile = new QAction(this);

        QMenu *recentMenu = new QMenu(this);

        QAction *undo = new QAction(this);
        QAction *redo = new QAction(this);
        QAction *selectAll = new QAction(this);
        QAction *deselect = new QAction(this);

        QAction *reset = new QAction(this);
        QAction *playPause = new QAction(this);
        QAction *replay = new QAction(this);
        QAction *stop = new QAction(this);

        QAction *settings = new QAction(this);
        QAction *keyShortcuts = new QAction(this);
        QAction *themes = new QAction(this);
        QAction *languages = new QAction(this);

        QMenu *preferenceMenu = new QMenu(this);
        preferenceMenu->addActions({settings, keyShortcuts, themes, languages});

        QAction *welcome = new QAction(this);
        QAction *instructions = new QAction(this);
        QAction *checkUpdate = new QAction(this);
        QAction *aboutApp = new QAction(this);
        QAction *aboutQt = new QAction(this);

        {
            welcomeActions->newFile = newFile;
            welcomeActions->importFile = importFile;
            welcomeActions->openFile = openFile;
            welcomeActions->openFolder = openFolder;
            welcomeActions->saveFile = saveFile;
            welcomeActions->saveAsFile = saveAsFile;
            welcomeActions->restoreFile = restoreFile;
            welcomeActions->switchFile = switchFile;
            welcomeActions->closeFile = closeFile;

            welcomeActions->recentMenu = recentMenu;

            welcomeActions->undo = undo;
            welcomeActions->redo = redo;
            welcomeActions->selectAll = selectAll;
            welcomeActions->deselect = deselect;

            welcomeActions->reset = reset;

            welcomeActions->playPause = playPause;
            welcomeActions->replay = replay;
            welcomeActions->stop = stop;

            welcomeActions->settings = settings;
            welcomeActions->keyShortcuts = keyShortcuts;
            welcomeActions->themes = themes;
            welcomeActions->languages = languages;
            welcomeActions->preferenceMenu = preferenceMenu;

            welcomeActions->welcome = welcome;
            welcomeActions->instructions = instructions;
            welcomeActions->checkUpdate = checkUpdate;
            welcomeActions->aboutApp = aboutApp;
            welcomeActions->aboutQt = aboutQt;
        }
        {
            tuningActions->newFile = newFile;
            tuningActions->importFile = importFile;
            tuningActions->openFile = openFile;
            tuningActions->openFolder = openFolder;
            tuningActions->saveFile = saveFile;
            tuningActions->saveAsFile = saveAsFile;
            tuningActions->restoreFile = restoreFile;
            tuningActions->switchFile = switchFile;
            tuningActions->closeFile = closeFile;

            tuningActions->recentMenu = recentMenu;

            tuningActions->undo = undo;
            tuningActions->redo = redo;
            tuningActions->selectAll = selectAll;
            tuningActions->deselect = deselect;

            tuningActions->reset = reset;

            tuningActions->playPause = playPause;
            tuningActions->replay = replay;
            tuningActions->stop = stop;

            tuningActions->settings = settings;
            tuningActions->keyShortcuts = keyShortcuts;
            tuningActions->themes = themes;
            tuningActions->languages = languages;
            tuningActions->preferenceMenu = preferenceMenu;

            tuningActions->welcome = welcome;
            tuningActions->instructions = instructions;
            tuningActions->checkUpdate = checkUpdate;
            tuningActions->aboutApp = aboutApp;
            tuningActions->aboutQt = aboutQt;
        }
        {
            voiceActions->newFile = newFile;
            voiceActions->importFile = importFile;
            voiceActions->openFile = openFile;
            voiceActions->openFolder = openFolder;
            voiceActions->saveFile = saveFile;
            voiceActions->saveAsFile = saveAsFile;
            voiceActions->restoreFile = restoreFile;
            voiceActions->switchFile = switchFile;
            voiceActions->closeFile = closeFile;

            voiceActions->recentMenu = recentMenu;

            voiceActions->undo = undo;
            voiceActions->redo = redo;
            voiceActions->selectAll = selectAll;
            voiceActions->deselect = deselect;

            voiceActions->reset = reset;

            voiceActions->playPause = playPause;
            voiceActions->replay = replay;
            voiceActions->stop = stop;

            voiceActions->settings = settings;
            voiceActions->keyShortcuts = keyShortcuts;
            voiceActions->themes = themes;
            voiceActions->languages = languages;
            voiceActions->preferenceMenu = preferenceMenu;

            voiceActions->welcome = welcome;
            voiceActions->instructions = instructions;
            voiceActions->checkUpdate = checkUpdate;
            voiceActions->aboutApp = aboutApp;
            voiceActions->aboutQt = aboutQt;
        }
        {
            keyboardActions->newFile = newFile;
            keyboardActions->importFile = importFile;
            keyboardActions->openFile = openFile;
            keyboardActions->openFolder = openFolder;
            keyboardActions->saveFile = saveFile;
            keyboardActions->saveAsFile = saveAsFile;
            keyboardActions->restoreFile = restoreFile;
            keyboardActions->closeFile = closeFile;

            keyboardActions->recentMenu = recentMenu;

            keyboardActions->undo = undo;
            keyboardActions->redo = redo;
            keyboardActions->selectAll = selectAll;
            keyboardActions->deselect = deselect;

            keyboardActions->reset = reset;

            keyboardActions->playPause = playPause;
            keyboardActions->replay = replay;
            keyboardActions->stop = stop;

            keyboardActions->settings = settings;
            keyboardActions->keyShortcuts = keyShortcuts;
            keyboardActions->themes = themes;
            keyboardActions->languages = languages;
            keyboardActions->preferenceMenu = preferenceMenu;

            keyboardActions->welcome = welcome;
            keyboardActions->instructions = instructions;
            keyboardActions->checkUpdate = checkUpdate;
            keyboardActions->aboutApp = aboutApp;
            keyboardActions->aboutQt = aboutQt;
        }
        {
            settingActions->newFile = newFile;
            settingActions->importFile = importFile;
            settingActions->openFile = openFile;
            settingActions->openFolder = openFolder;
            settingActions->saveFile = saveFile;
            settingActions->saveAsFile = saveAsFile;
            settingActions->restoreFile = restoreFile;
            settingActions->switchFile = switchFile;
            settingActions->closeFile = closeFile;

            settingActions->recentMenu = recentMenu;

            settingActions->undo = undo;
            settingActions->redo = redo;
            settingActions->selectAll = selectAll;
            settingActions->deselect = deselect;

            settingActions->reset = reset;

            settingActions->playPause = playPause;
            settingActions->replay = replay;
            settingActions->stop = stop;

            settingActions->settings = settings;
            settingActions->keyShortcuts = keyShortcuts;
            settingActions->themes = themes;
            settingActions->languages = languages;
            settingActions->preferenceMenu = preferenceMenu;

            settingActions->welcome = welcome;
            settingActions->instructions = instructions;
            settingActions->checkUpdate = checkUpdate;
            settingActions->aboutApp = aboutApp;
            settingActions->aboutQt = aboutQt;
        }

        connect(newFile, &QAction::triggered, this, &MainWindow::handleNewFile);
        connect(importFile, &QAction::triggered, this, &MainWindow::handleImportFile);
        connect(openFile, &QAction::triggered, this, &MainWindow::handleOpenFile);
        connect(openFolder, &QAction::triggered, this, &MainWindow::handleOpenFolder);
        connect(saveFile, &QAction::triggered, this, &MainWindow::handleSaveFile);
        connect(saveAsFile, &QAction::triggered, this, &MainWindow::handleSaveAsFile);
        connect(restoreFile, &QAction::triggered, this, &MainWindow::handleRestoreFile);
        connect(switchFile, &QAction::triggered, this, &MainWindow::handleSwitchFile);
        connect(closeFile, &QAction::triggered, this, &MainWindow::handleCloseFile);

        connect(undo, &QAction::triggered, this, &MainWindow::handleUndo);
        connect(redo, &QAction::triggered, this, &MainWindow::handleRedo);
        connect(selectAll, &QAction::triggered, this, &MainWindow::handleSelectAll);
        connect(deselect, &QAction::triggered, this, &MainWindow::handleDeselect);

        connect(reset, &QAction::triggered, this, &MainWindow::handleReset);

        connect(playPause, &QAction::triggered, this, &MainWindow::handlePlayPause);
        connect(replay, &QAction::triggered, this, &MainWindow::handleReplay);
        connect(stop, &QAction::triggered, this, &MainWindow::handleStop);

        connect(settings, &QAction::triggered, this, &MainWindow::handleOpenSettings);
        connect(keyShortcuts, &QAction::triggered, this, &MainWindow::handleOpenKeyShortcuts);
        connect(themes, &QAction::triggered, this, &MainWindow::handleOpenThemes);
        connect(languages, &QAction::triggered, this, &MainWindow::handleOpenLanguages);

        connect(welcome, &QAction::triggered, this, &MainWindow::handleOpenWelcome);
        connect(instructions, &QAction::triggered, this, &MainWindow::handleInstructions);
        connect(checkUpdate, &QAction::triggered, this, &MainWindow::handleCheckUpdate);
        connect(aboutApp, &QAction::triggered, this, &MainWindow::handleAboutApp);
        connect(aboutQt, &QAction::triggered, this, &MainWindow::handleAboutQt);
    }

    // Set Tuning Actions
    {
        QAction *appendFile = new QAction(this);
        QAction *exportSelection = new QAction(this);
        QAction *exportTrack = new QAction(this);

        QMenu *exportMenu = new QMenu(this);
        exportMenu->addActions({exportSelection, exportTrack});

        QAction *copy = new QAction(this);
        QAction *cut = new QAction(this);
        QAction *paste = new QAction(this);
        QAction *remove = new QAction(this);

        QAction *insertLyrics = new QAction(this);
        QAction *findReplace = new QAction(this);
        QAction *transpose = new QAction(this);
        QAction *octaveUp = new QAction(this);
        QAction *octaveDown = new QAction(this);
        QAction *removeRest = new QAction(this);
        QAction *insertRest = new QAction(this);
        QAction *p2p3Fade = new QAction(this);
        QAction *p1p4Fade = new QAction(this);
        QAction *resetEnvelope = new QAction(this);
        QAction *noteProperty = new QAction(this);

        QAction *moveStart = new QAction(this);
        QAction *moveEnd = new QAction(this);
        QAction *removeCache = new QAction(this);
        QAction *exportAudio = new QAction(this);

        QAction *lyricConfig = new QAction(this);
        QAction *prefixConfig = new QAction(this);

        QMenu *buildInMenu = new QMenu(this);
        QMenu *pluginMenu = new QMenu(this);

        QAction *openBuildInMenu = new QAction(this);
        QAction *openPluginMenu = new QAction(this);
        QAction *openAliasMenu = new QAction(this);

        QAction *switchTrack = new QAction(this);
        QAction *switchConfig = new QAction(this);

        QAction *switchNote = new QAction(this);
        QAction *switchPitch = new QAction(this);
        QAction *switchEnvelope = new QAction(this);

        QAction *switchInt = new QAction(this);
        QAction *switchMod = new QAction(this);
        QAction *switchVel = new QAction(this);

        tuningActions->appendFile = appendFile;
        tuningActions->exportSelection = exportSelection;
        tuningActions->exportTrack = exportTrack;

        tuningActions->exportMenu = exportMenu;

        tuningActions->copy = copy;
        tuningActions->cut = cut;
        tuningActions->paste = paste;
        tuningActions->remove = remove;

        tuningActions->insertLyrics = insertLyrics;
        tuningActions->findReplace = findReplace;
        tuningActions->transpose = transpose;
        tuningActions->octaveUp = octaveUp;
        tuningActions->octaveDown = octaveDown;
        tuningActions->removeRest = removeRest;
        tuningActions->insertRest = insertRest;
        tuningActions->p2p3Fade = p2p3Fade;
        tuningActions->p1p4Fade = p1p4Fade;
        tuningActions->resetEnvelope = resetEnvelope;
        tuningActions->noteProperty = noteProperty;

        tuningActions->moveStart = moveStart;
        tuningActions->moveEnd = moveEnd;
        tuningActions->removeCache = removeCache;
        tuningActions->exportAudio = exportAudio;

        tuningActions->lyricConfig = lyricConfig;
        tuningActions->prefixConfig = prefixConfig;

        tuningActions->buildInMenu = buildInMenu;
        tuningActions->pluginMenu = pluginMenu;

        tuningActions->openBuildInMenu = openBuildInMenu;
        tuningActions->openPluginMenu = openPluginMenu;
        tuningActions->openAliasMenu = openAliasMenu;

        tuningActions->switchTrack = switchTrack;
        tuningActions->switchConfig = switchConfig;

        tuningActions->switchNote = switchNote;
        tuningActions->switchPitch = switchPitch;
        tuningActions->switchEnvelope = switchEnvelope;

        tuningActions->switchInt = switchInt;
        tuningActions->switchMod = switchMod;
        tuningActions->switchVel = switchVel;

        connect(appendFile, &QAction::triggered, this, &MainWindow::handleAppendFile);
        connect(exportSelection, &QAction::triggered, this, &MainWindow::handleExportSelection);
        connect(exportTrack, &QAction::triggered, this, &MainWindow::handleExportTrack);

        connect(copy, &QAction::triggered, this, &MainWindow::handleCopyNotes);
        connect(cut, &QAction::triggered, this, &MainWindow::handleCutNotes);
        connect(paste, &QAction::triggered, this, &MainWindow::handlePasteNotes);
        connect(remove, &QAction::triggered, this, &MainWindow::handleRemoveNotes);

        connect(insertLyrics, &QAction::triggered, this, &MainWindow::handleInsertLyrics);
        connect(findReplace, &QAction::triggered, this, &MainWindow::handleFindReplace);
        connect(transpose, &QAction::triggered, this, &MainWindow::handleTranspose);
        connect(octaveUp, &QAction::triggered, this, &MainWindow::handleOctaveUp);
        connect(octaveDown, &QAction::triggered, this, &MainWindow::handleOctaveDown);
        connect(removeRest, &QAction::triggered, this, &MainWindow::handleRemoveRest);
        connect(insertRest, &QAction::triggered, this, &MainWindow::handleInsertRest);
        connect(p2p3Fade, &QAction::triggered, this, &MainWindow::handleP2P3Fade);
        connect(p1p4Fade, &QAction::triggered, this, &MainWindow::handleP1P4Fade);
        connect(resetEnvelope, &QAction::triggered, this, &MainWindow::handleResetEnvelope);
        connect(noteProperty, &QAction::triggered, this, &MainWindow::handleNoteProperty);

        connect(moveStart, &QAction::triggered, this, &MainWindow::handleMoveToStart);
        connect(moveEnd, &QAction::triggered, this, &MainWindow::handleMoveToEnd);
        connect(removeCache, &QAction::triggered, this, &MainWindow::handleRemoveCache);
        connect(exportAudio, &QAction::triggered, this, &MainWindow::handleExportAudio);

        connect(lyricConfig, &QAction::triggered, this, &MainWindow::handleLyricConfig);
        connect(prefixConfig, &QAction::triggered, this, &MainWindow::handlePrefixConfig);

        connect(openBuildInMenu, &QAction::triggered, this, &MainWindow::handleOpenBuildInMenu);
        connect(openPluginMenu, &QAction::triggered, this, &MainWindow::handleOpenPluginMenu);
        connect(openAliasMenu, &QAction::triggered, this, &MainWindow::handleOpenAliasMenu);

        connect(switchTrack, &QAction::triggered, this, &MainWindow::handleSwitchTrack);
        connect(switchConfig, &QAction::triggered, this, &MainWindow::handleSwitchConfig);

        connect(switchNote, &QAction::triggered, this, &MainWindow::handleSwitchNote);
        connect(switchPitch, &QAction::triggered, this, &MainWindow::handleSwitchPitch);
        connect(switchEnvelope, &QAction::triggered, this, &MainWindow::handleSwitchEnvelope);

        connect(switchInt, &QAction::triggered, this, &MainWindow::handleSwitchInt);
        connect(switchMod, &QAction::triggered, this, &MainWindow::handleSwitchMod);
        connect(switchVel, &QAction::triggered, this, &MainWindow::handleSwitchVel);
    }

    // Set Voice Actions
    {
        QAction *exportCurrent = new QAction(this);

        QAction *moveUp = new QAction(this);
        QAction *moveDown = new QAction(this);
        QAction *moveTop = new QAction(this);
        QAction *moveBottom = new QAction(this);
        QAction *duplicate = new QAction(this);
        QAction *remove = new QAction(this);

        QAction *generateFrq = new QAction(this);
        QAction *modifyAlias = new QAction(this);
        QAction *removeInvalid = new QAction(this);
        QAction *setOffset = new QAction(this);
        QAction *setOverlap = new QAction(this);
        QAction *setPreUttr = new QAction(this);
        QAction *setConstant = new QAction(this);
        QAction *setBlank = new QAction(this);

        QMenu *buildInMenu = new QMenu(this);

        voiceActions->exportCurrent = exportCurrent;

        voiceActions->moveUp = moveUp;
        voiceActions->moveDown = moveDown;
        voiceActions->moveTop = moveTop;
        voiceActions->moveBottom = moveBottom;
        voiceActions->duplicate = duplicate;
        voiceActions->remove = remove;

        voiceActions->generateFrq = generateFrq;
        voiceActions->modifyAlias = modifyAlias;
        voiceActions->removeInvalid = removeInvalid;
        voiceActions->setOffset = setOffset;
        voiceActions->setOverlap = setOverlap;
        voiceActions->setPreUttr = setPreUttr;
        voiceActions->setConstant = setConstant;
        voiceActions->setBlank = setBlank;

        voiceActions->buildInMenu = buildInMenu;

        connect(exportCurrent, &QAction::triggered, this, &MainWindow::handleExportCurrent);

        connect(moveUp, &QAction::triggered, this, &MainWindow::handleMoveUpSample);
        connect(moveDown, &QAction::triggered, this, &MainWindow::handleMoveDownSample);
        connect(moveTop, &QAction::triggered, this, &MainWindow::handleMoveTopSample);
        connect(moveBottom, &QAction::triggered, this, &MainWindow::handleMoveBottomSample);
        connect(duplicate, &QAction::triggered, this, &MainWindow::handleDuplicateSample);
        connect(remove, &QAction::triggered, this, &MainWindow::handleRemoveSample);

        connect(generateFrq, &QAction::triggered, this, &MainWindow::handleGenerateFrq);
        connect(modifyAlias, &QAction::triggered, this, &MainWindow::handleModifyAlias);
        connect(removeInvalid, &QAction::triggered, this, &MainWindow::handleRemoveInvalidSamples);
        connect(setOffset, &QAction::triggered, this, &MainWindow::handleSetOffset);
        connect(setOverlap, &QAction::triggered, this, &MainWindow::handleSetOverlap);
        connect(setPreUttr, &QAction::triggered, this, &MainWindow::handleSetPreUttr);
        connect(setConstant, &QAction::triggered, this, &MainWindow::handleSetConstant);
        connect(setBlank, &QAction::triggered, this, &MainWindow::handleSetBlank);
    }
}

void MainWindow::setCurrentActions(Qs::MainTabs type) {
    fileMenu->clear();
    editMenu->clear();
    modifyMenu->clear();
    previewMenu->clear();
    toolMenu->clear();
    helpMenu->clear();

    QList<QAction *> actions = this->actions();
    for (QAction *action : actions) {
        removeAction(action);
    }

    switch (type) {
    case Qs::Welcome: {
        fileMenu->addAction(welcomeActions->newFile);
        fileMenu->addAction(welcomeActions->importFile);
        fileMenu->addSeparator();
        fileMenu->addAction(welcomeActions->openFile);
        fileMenu->addAction(welcomeActions->openFolder);
        fileMenu->addMenu(welcomeActions->recentMenu);
        fileMenu->addSeparator();
        fileMenu->addAction(welcomeActions->saveFile);
        fileMenu->addAction(welcomeActions->saveAsFile);
        fileMenu->addSeparator();
        fileMenu->addAction(welcomeActions->restoreFile);
        fileMenu->addSeparator();
        fileMenu->addAction(welcomeActions->switchFile);
        fileMenu->addAction(welcomeActions->closeFile);

        editMenu->addAction(welcomeActions->undo);
        editMenu->addAction(welcomeActions->redo);
        editMenu->addSeparator();
        editMenu->addAction(welcomeActions->selectAll);
        editMenu->addAction(welcomeActions->deselect);

        modifyMenu->addAction(welcomeActions->reset);

        previewMenu->addAction(welcomeActions->playPause);
        previewMenu->addAction(welcomeActions->replay);
        previewMenu->addAction(welcomeActions->stop);

        toolMenu->addMenu(welcomeActions->preferenceMenu);

        helpMenu->addAction(welcomeActions->welcome);
        helpMenu->addAction(welcomeActions->instructions);
        helpMenu->addSeparator();
        helpMenu->addAction(welcomeActions->checkUpdate);
        helpMenu->addSeparator();
        helpMenu->addAction(welcomeActions->aboutApp);
        helpMenu->addAction(welcomeActions->aboutQt);
        break;
    }
    case Qs::Setting: {
        fileMenu->addAction(settingActions->newFile);
        fileMenu->addAction(settingActions->importFile);
        fileMenu->addSeparator();
        fileMenu->addAction(settingActions->openFile);
        fileMenu->addAction(settingActions->openFolder);
        fileMenu->addMenu(settingActions->recentMenu);
        fileMenu->addSeparator();
        fileMenu->addAction(settingActions->saveFile);
        fileMenu->addAction(settingActions->saveAsFile);
        fileMenu->addSeparator();
        fileMenu->addAction(settingActions->restoreFile);
        fileMenu->addSeparator();
        fileMenu->addAction(settingActions->switchFile);
        fileMenu->addAction(settingActions->closeFile);

        editMenu->addAction(settingActions->undo);
        editMenu->addAction(settingActions->redo);
        editMenu->addSeparator();
        editMenu->addAction(settingActions->selectAll);
        editMenu->addAction(settingActions->deselect);

        modifyMenu->addAction(settingActions->reset);

        previewMenu->addAction(settingActions->playPause);
        previewMenu->addAction(settingActions->replay);
        previewMenu->addAction(settingActions->stop);

        toolMenu->addMenu(settingActions->preferenceMenu);

        helpMenu->addAction(settingActions->welcome);
        helpMenu->addAction(settingActions->instructions);
        helpMenu->addSeparator();
        helpMenu->addAction(settingActions->checkUpdate);
        helpMenu->addSeparator();
        helpMenu->addAction(settingActions->aboutApp);
        helpMenu->addAction(settingActions->aboutQt);
        break;
    }
    case Qs::Keyboard: {
        fileMenu->addAction(keyboardActions->newFile);
        fileMenu->addAction(keyboardActions->importFile);
        fileMenu->addSeparator();
        fileMenu->addAction(keyboardActions->openFile);
        fileMenu->addAction(keyboardActions->openFolder);
        fileMenu->addMenu(keyboardActions->recentMenu);
        fileMenu->addSeparator();
        fileMenu->addAction(keyboardActions->saveFile);
        fileMenu->addAction(keyboardActions->saveAsFile);
        fileMenu->addSeparator();
        fileMenu->addAction(keyboardActions->restoreFile);
        fileMenu->addSeparator();
        fileMenu->addAction(keyboardActions->switchFile);
        fileMenu->addAction(keyboardActions->closeFile);

        editMenu->addAction(keyboardActions->undo);
        editMenu->addAction(keyboardActions->redo);
        editMenu->addSeparator();
        editMenu->addAction(keyboardActions->selectAll);
        editMenu->addAction(keyboardActions->deselect);

        modifyMenu->addAction(keyboardActions->reset);

        previewMenu->addAction(keyboardActions->playPause);
        previewMenu->addAction(keyboardActions->replay);
        previewMenu->addAction(keyboardActions->stop);

        toolMenu->addMenu(keyboardActions->preferenceMenu);

        helpMenu->addAction(keyboardActions->welcome);
        helpMenu->addAction(keyboardActions->instructions);
        helpMenu->addSeparator();
        helpMenu->addAction(keyboardActions->checkUpdate);
        helpMenu->addSeparator();
        helpMenu->addAction(keyboardActions->aboutApp);
        helpMenu->addAction(keyboardActions->aboutQt);
        break;
    }
    case Qs::Tuning: {
        fileMenu->addAction(tuningActions->newFile);
        fileMenu->addAction(tuningActions->importFile);
        fileMenu->addSeparator();
        fileMenu->addAction(tuningActions->openFile);
        fileMenu->addAction(tuningActions->openFolder);
        fileMenu->addMenu(tuningActions->recentMenu);
        fileMenu->addSeparator();
        fileMenu->addAction(tuningActions->saveFile);
        fileMenu->addAction(tuningActions->saveAsFile);
        fileMenu->addSeparator();
        fileMenu->addAction(tuningActions->restoreFile);
        fileMenu->addSeparator();
        fileMenu->addAction(tuningActions->appendFile);
        fileMenu->addMenu(tuningActions->exportMenu);
        fileMenu->addSeparator();
        fileMenu->addAction(tuningActions->switchFile);
        fileMenu->addAction(tuningActions->closeFile);

        editMenu->addAction(tuningActions->undo);
        editMenu->addAction(tuningActions->redo);
        editMenu->addSeparator();
        editMenu->addAction(tuningActions->copy);
        editMenu->addAction(tuningActions->cut);
        editMenu->addAction(tuningActions->paste);
        editMenu->addAction(tuningActions->remove);
        editMenu->addSeparator();
        editMenu->addAction(tuningActions->selectAll);
        editMenu->addAction(tuningActions->deselect);

        modifyMenu->addAction(tuningActions->insertLyrics);
        modifyMenu->addSeparator();
        modifyMenu->addAction(tuningActions->findReplace);
        modifyMenu->addSeparator();
        modifyMenu->addAction(tuningActions->transpose);
        modifyMenu->addAction(tuningActions->octaveUp);
        modifyMenu->addAction(tuningActions->octaveDown);
        modifyMenu->addSeparator();
        modifyMenu->addAction(tuningActions->removeRest);
        modifyMenu->addAction(tuningActions->insertRest);
        modifyMenu->addSeparator();
        modifyMenu->addAction(tuningActions->p2p3Fade);
        modifyMenu->addAction(tuningActions->p1p4Fade);
        modifyMenu->addAction(tuningActions->resetEnvelope);
        modifyMenu->addSeparator();
        modifyMenu->addAction(tuningActions->reset);
        modifyMenu->addAction(tuningActions->noteProperty);

        previewMenu->addAction(tuningActions->playPause);
        previewMenu->addAction(tuningActions->replay);
        previewMenu->addAction(tuningActions->stop);
        previewMenu->addSeparator();
        previewMenu->addAction(tuningActions->moveStart);
        previewMenu->addAction(tuningActions->moveEnd);
        previewMenu->addSeparator();
        previewMenu->addAction(tuningActions->removeCache);
        previewMenu->addAction(tuningActions->exportAudio);

        toolMenu->addAction(tuningActions->lyricConfig);
        toolMenu->addAction(tuningActions->prefixConfig);
        toolMenu->addSeparator();
        toolMenu->addMenu(tuningActions->buildInMenu);
        toolMenu->addMenu(tuningActions->pluginMenu);
        toolMenu->addSeparator();
        toolMenu->addMenu(tuningActions->preferenceMenu);

        helpMenu->addAction(tuningActions->welcome);
        helpMenu->addAction(tuningActions->instructions);
        helpMenu->addSeparator();
        helpMenu->addAction(tuningActions->checkUpdate);
        helpMenu->addSeparator();
        helpMenu->addAction(tuningActions->aboutApp);
        helpMenu->addAction(tuningActions->aboutQt);

        // Shortcuts
        addAction(tuningActions->openBuildInMenu);
        addAction(tuningActions->openPluginMenu);
        addAction(tuningActions->openAliasMenu);

        addAction(tuningActions->switchTrack);
        addAction(tuningActions->switchConfig);

        addAction(tuningActions->switchNote);
        addAction(tuningActions->switchPitch);
        addAction(tuningActions->switchEnvelope);

        addAction(tuningActions->switchInt);
        addAction(tuningActions->switchMod);
        addAction(tuningActions->switchVel);

        break;
    };
    case Qs::Folder: {
        fileMenu->addAction(voiceActions->newFile);
        fileMenu->addAction(voiceActions->importFile);
        fileMenu->addSeparator();
        fileMenu->addAction(voiceActions->openFile);
        fileMenu->addAction(voiceActions->openFolder);
        fileMenu->addMenu(voiceActions->recentMenu);
        fileMenu->addSeparator();
        fileMenu->addAction(voiceActions->saveFile);
        fileMenu->addAction(voiceActions->saveAsFile);
        fileMenu->addSeparator();
        fileMenu->addAction(voiceActions->restoreFile);
        fileMenu->addSeparator();
        fileMenu->addAction(voiceActions->exportCurrent);
        fileMenu->addSeparator();
        fileMenu->addAction(voiceActions->switchFile);
        fileMenu->addAction(voiceActions->closeFile);

        editMenu->addAction(voiceActions->undo);
        editMenu->addAction(voiceActions->redo);
        editMenu->addSeparator();
        editMenu->addAction(voiceActions->moveUp);
        editMenu->addAction(voiceActions->moveDown);
        editMenu->addAction(voiceActions->moveTop);
        editMenu->addAction(voiceActions->moveBottom);
        editMenu->addSeparator();
        editMenu->addAction(voiceActions->duplicate);
        editMenu->addAction(voiceActions->remove);
        editMenu->addSeparator();
        editMenu->addAction(voiceActions->selectAll);
        editMenu->addAction(voiceActions->deselect);

        modifyMenu->addAction(voiceActions->generateFrq);
        modifyMenu->addAction(voiceActions->modifyAlias);
        modifyMenu->addAction(voiceActions->removeInvalid);
        modifyMenu->addSeparator();
        modifyMenu->addAction(voiceActions->reset);
        modifyMenu->addSeparator();
        modifyMenu->addAction(voiceActions->setOffset);
        modifyMenu->addAction(voiceActions->setOverlap);
        modifyMenu->addAction(voiceActions->setPreUttr);
        modifyMenu->addAction(voiceActions->setConstant);
        modifyMenu->addAction(voiceActions->setBlank);

        previewMenu->addAction(voiceActions->playPause);
        previewMenu->addAction(voiceActions->replay);
        previewMenu->addAction(voiceActions->stop);

        toolMenu->addMenu(voiceActions->buildInMenu);
        toolMenu->addSeparator();
        toolMenu->addMenu(voiceActions->preferenceMenu);

        helpMenu->addAction(voiceActions->welcome);
        helpMenu->addAction(voiceActions->instructions);
        helpMenu->addSeparator();
        helpMenu->addAction(voiceActions->checkUpdate);
        helpMenu->addSeparator();
        helpMenu->addAction(voiceActions->aboutApp);
        helpMenu->addAction(voiceActions->aboutQt);
        break;
    }
    default:
        break;
    }
}
