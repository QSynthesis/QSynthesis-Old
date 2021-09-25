#include "mainwindow.h"

void MainWindow::initMenuBar() {
    fileMenu = new QMenu(this);
    editMenu = new QMenu(this);
    modifyMenu = new QMenu(this);
    previewMenu = new QMenu(this);
    toolMenu = new QMenu(this);
    helpMenu = new QMenu(this);

    fileMenu->setFocusPolicy(Qt::StrongFocus);
    editMenu->setFocusPolicy(Qt::StrongFocus);
    modifyMenu->setFocusPolicy(Qt::StrongFocus);
    previewMenu->setFocusPolicy(Qt::StrongFocus);
    toolMenu->setFocusPolicy(Qt::StrongFocus);
    helpMenu->setFocusPolicy(Qt::StrongFocus);

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

    // Set Common Actions
    {
        QMenu *recentMenu = new QMenu(this);
        QMenu *preferenceMenu = new QMenu(this);

        QList<void (MainWindow::*)()> handlers{
            &MainWindow::handleNewFile,
            &MainWindow::handleImportFile,
            &MainWindow::handleOpenFile,
            &MainWindow::handleOpenFolder,
            &MainWindow::handleSaveFile,
            &MainWindow::handleSaveAsFile,
            &MainWindow::handleRestoreFile,
            &MainWindow::handleSwitchFile,
            &MainWindow::handleCloseFile,
            &MainWindow::handleUndo,
            &MainWindow::handleRedo,
            &MainWindow::handleSelectAll,
            &MainWindow::handleDeselect,
            &MainWindow::handleReset,
            &MainWindow::handlePlayPause,
            &MainWindow::handleReplay,
            &MainWindow::handleStop,
            &MainWindow::handleOpenSettings,
            &MainWindow::handleOpenKeyShortcuts,
            &MainWindow::handleOpenThemes,
            &MainWindow::handleOpenLanguages,
            &MainWindow::handleOpenWelcome,
            &MainWindow::handleInstructions,
            &MainWindow::handleCheckUpdate,
            &MainWindow::handleAboutApp,
            &MainWindow::handleAboutQt,
        };

        QList<QAction **> commonActionsRef = welcomeActions->commonActionsRef();
        {
            auto it0 = handlers.begin();
            for (auto it = commonActionsRef.begin(); it != commonActionsRef.end(); ++it, ++it0) {
                QAction *&action = **it;
                action = new QAction(this);
                connect(action, &QAction::triggered, this, *it0);
            }
            preferenceMenu->addActions({welcomeActions->settings, welcomeActions->keyShortcuts,
                                        welcomeActions->themes, welcomeActions->languages});
            welcomeActions->recentMenu = recentMenu;
            welcomeActions->preferenceMenu = preferenceMenu;
        }
        QList<QAction **> tCommonActionsRef = tuningActions->commonActionsRef();
        {
            auto it0 = commonActionsRef.begin();
            for (auto it = tCommonActionsRef.begin(); it != tCommonActionsRef.end(); ++it, ++it0) {
                *(*it) = *(*it0);
            }
            tuningActions->recentMenu = recentMenu;
            tuningActions->preferenceMenu = preferenceMenu;
        }

        QList<QAction **> vCommonActionsRef = voiceActions->commonActionsRef();
        {
            auto it0 = commonActionsRef.begin();
            for (auto it = vCommonActionsRef.begin(); it != vCommonActionsRef.end(); ++it, ++it0) {
                *(*it) = *(*it0);
            }
            voiceActions->recentMenu = recentMenu;
            voiceActions->preferenceMenu = preferenceMenu;
        }

        QList<QAction **> kCommonActionsRef = keyboardActions->commonActionsRef();
        {
            auto it0 = commonActionsRef.begin();
            for (auto it = kCommonActionsRef.begin(); it != kCommonActionsRef.end(); ++it, ++it0) {
                *(*it) = *(*it0);
            }
            keyboardActions->recentMenu = recentMenu;
            keyboardActions->preferenceMenu = preferenceMenu;
        }

        QList<QAction **> sCommonActionsRef = settingActions->commonActionsRef();
        {
            auto it0 = commonActionsRef.begin();
            for (auto it = sCommonActionsRef.begin(); it != sCommonActionsRef.end(); ++it, ++it0) {
                *(*it) = *(*it0);
            }
            settingActions->recentMenu = recentMenu;
            settingActions->preferenceMenu = preferenceMenu;
        }
    }

    // Set Tuning Actions
    {
        QMenu *tracksMenu = new QMenu(this);
        QMenu *editorMenu = new QMenu(this);

        QMenu *exportMenu = new QMenu(this);
        QMenu *buildInMenu = new QMenu(this);
        QMenu *pluginMenu = new QMenu(this);

        QMenu *adsorbMenu = new QMenu(this);
        QMenu *stateMenu = new QMenu(this);
        QMenu *playHeadMenu = new QMenu(this);

        QList<void (MainWindow::*)()> handlers{
            &MainWindow::handleAppendFile,
            &MainWindow::handleExportSelection,
            &MainWindow::handleExportTrack,

            &MainWindow::handleCopyNotes,
            &MainWindow::handleCutNotes,
            &MainWindow::handlePasteNotes,
            &MainWindow::handleRemoveNotes,
            &MainWindow::handleInsertLyrics,

            &MainWindow::handleFindReplace,
            &MainWindow::handleTranspose,
            &MainWindow::handleOctaveUp,
            &MainWindow::handleOctaveDown,
            &MainWindow::handleRemoveRest,
            &MainWindow::handleInsertRest,
            &MainWindow::handleP2P3Fade,
            &MainWindow::handleP1P4Fade,
            &MainWindow::handleResetEnvelope,
            &MainWindow::handleNoteProperty,

            &MainWindow::handleMoveToStart,
            &MainWindow::handleMoveToEnd,
            &MainWindow::handleRemoveCache,
            &MainWindow::handleExportAudio,
            &MainWindow::handleLyricConfig,
            &MainWindow::handlePrefixConfig,

            &MainWindow::handleOpenBuildInMenu,
            &MainWindow::handleOpenPluginMenu,
            &MainWindow::handleOpenAliasMenu,

            &MainWindow::handleSwitchTrack,
            &MainWindow::handleSwitchConfig,
            &MainWindow::handleSwitchNote,
            &MainWindow::handleSwitchPitch,
            &MainWindow::handleSwitchEnvelope,
            &MainWindow::handleSwitchInt,
            &MainWindow::handleSwitchMod,
            &MainWindow::handleSwitchVel,

            &MainWindow::handleOpenProjectSettings,
            &MainWindow::handleOpenCharsetSettings,

            &MainWindow::handleFullAdsorb,
            &MainWindow::handleHalfAdsorb,
            &MainWindow::handleQuarterAdsorb,
            &MainWindow::handleSixthAdsorb,
            &MainWindow::handleEighthAdsorb,
            &MainWindow::handleTwelfthAdsorb,
            &MainWindow::handleSixteenthAdsorb,
            &MainWindow::handleTwentyForthAdsorb,
            &MainWindow::handleThirtySecondAdsorb,
            &MainWindow::handleNoneAdsorb,

            &MainWindow::handleSwitchNoteVisibility,
            &MainWindow::handleSwitchPitchVisibility,
            &MainWindow::handleSwitchEnvelopeVisibility,
            &MainWindow::handleSwitchParamsVisibility,

            &MainWindow::handlePlayHeadDisplay,
            &MainWindow::handlePlayHeadCenter,

            &MainWindow::handleShowSpriteAdjust,
        };

        QList<QAction **> actionsRef = tuningActions->actionsRef();
        auto it0 = handlers.begin();
        for (auto it = actionsRef.begin(); it != actionsRef.end(); ++it, ++it0) {
            QAction *&action = **it;
            action = new QAction(this);
            connect(action, &QAction::triggered, this, *it0);
        }

        exportMenu->addActions({tuningActions->exportSelection, tuningActions->exportTrack});

        adsorbMenu->addActions({tuningActions->fullAdsorb, tuningActions->halfAdsorb,
                                tuningActions->quarterAdsorb, tuningActions->sixthAdsorb,
                                tuningActions->eighthAdsorb, tuningActions->twelfthAdsorb,
                                tuningActions->sixteenthAdsorb, tuningActions->twentyForthAdsorb,
                                tuningActions->thirtySecondAdsorb, tuningActions->noAdsorb});
        stateMenu->addActions({tuningActions->switchNoteState, tuningActions->switchPitchState,
                               tuningActions->switchEnvelopeState,
                               tuningActions->switchParamsState});
        playHeadMenu->addActions({tuningActions->playHeadDisplay, tuningActions->playHeadCenter});

        tracksMenu->addAction(tuningActions->openProjectSettings);
        tracksMenu->addAction(tuningActions->openCharsetSettings);

        editorMenu->addMenu(adsorbMenu);
        editorMenu->addMenu(stateMenu);
        editorMenu->addMenu(playHeadMenu);
        editorMenu->addAction(tuningActions->showSpriteAdjust);

        tuningActions->exportMenu = exportMenu;
        tuningActions->buildInMenu = buildInMenu;
        tuningActions->pluginMenu = pluginMenu;

        tuningActions->adsorbMenu = adsorbMenu;
        tuningActions->stateMenu = stateMenu;
        tuningActions->playHeadMenu = playHeadMenu;

        tuningActions->tracksMenu = tracksMenu;
        tuningActions->editorMenu = editorMenu;

        tracksMenu->setVisible(false);
        editorMenu->setVisible(false);

        menuBar()->addMenu(tracksMenu);
        menuBar()->addMenu(editorMenu);
    }

    // Set Voice Actions
    {
        QMenu *buildInMenu = new QMenu(this);
        QList<void (MainWindow::*)()> handlers{
            &MainWindow::handleExportCurrent,    &MainWindow::handleMoveUpSample,
            &MainWindow::handleMoveDownSample,   &MainWindow::handleMoveTopSample,
            &MainWindow::handleMoveBottomSample, &MainWindow::handleDuplicateSample,
            &MainWindow::handleRemoveSample,     &MainWindow::handleGenerateFrq,
            &MainWindow::handleModifyAlias,      &MainWindow::handleRemoveInvalidSamples,
            &MainWindow::handleSetOffset,        &MainWindow::handleSetOverlap,
            &MainWindow::handleSetPreUttr,       &MainWindow::handleSetConstant,
            &MainWindow::handleSetBlank,
        };

        QList<QAction **> actionsRef = voiceActions->actionsRef();
        auto it0 = handlers.begin();
        for (auto it = actionsRef.begin(); it != actionsRef.end(); ++it, ++it0) {
            QAction *&action = **it;
            action = new QAction(this);
            connect(action, &QAction::triggered, this, *it0);
        }

        voiceActions->buildInMenu = buildInMenu;
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
        addAction(tuningActions->openBuildInList);
        addAction(tuningActions->openPluginList);
        addAction(tuningActions->openAliasList);

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
