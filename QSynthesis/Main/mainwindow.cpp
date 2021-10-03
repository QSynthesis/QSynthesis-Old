﻿#include "mainwindow.h"
#include "Document/SettingIniFile.h"
#include "Managers/DataManager.h"

Q_SINGLETON_DECLARE(MainWindow)

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createCasePrivate();

    setAcceptDrops(true); // Accept Drops

    // Components
    initValues();
    initMenuBar();
    initActionLists();
    initTabs();

    // Temporary Settings
    initSettingIni();
}

MainWindow::~MainWindow() {
    qDebug() << "[Destruct] MainWindow";
}

void MainWindow::initAndShow() {
    // Modules
    initModules();

    initConfig();
    initShortcuts();

    initMemory(); // Check If Last Crushed

    // Start
    qData->reloadStrings();

    reloadRecentMenu(); // load recent menu
    reloadMenu();       // load menu strings
    reloadShortcuts();  // load shortcuts

    reloadPlugins();
    reloadVoice();
    reloadThemes();
    reloadLanguages();

    initWindow();
}

void MainWindow::freeAndQuit() {
    quitWindow();

    // Modules
    freeModules();
}

void MainWindow::initWindow() {
    bool hasSize = false;
    QRect rect = qSetting->windowRect;
    bool max = qSetting->windowMaximized;
    if (rect != NO_RECT) {
        hasSize = true;
        setGeometry(rect);

        if (max) {
            setWindowState(Qt::WindowMaximized);
        }
    }
    if (!hasSize) {
        resize(800, 600);
    }
    show();
}

void MainWindow::quitWindow() {
    qSetting->windowRect = geometry();
    qSetting->windowMaximized = windowState() == Qt::WindowMaximized;

    saveSettingIni();
}

void MainWindow::initValues() {
    untitledCount = 0;
}
