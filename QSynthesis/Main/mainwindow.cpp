#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createCasePrivate();

    setAcceptDrops(true); // Accept Drops
    initValues();
}

void MainWindow::initAndShow() {
    reloadBackendStrings();

    initMenuBar();
    initActionLists();

    initTabs(); // Initialize Tab Manager
    initStyleSheet();

    reloadRecentMenu(); // load recent menu
    reloadMenu();       // load menu strings
    reloadPlugins();    // load plugins
    reloadShortcuts();  // load shortcuts

    connect(voice, &VoiceCollect::changed, this, &MainWindow::reloadVoice);
    connect(plugins, &PluginsCollect::changed, this, &MainWindow::reloadPlugins);

    initWindow();
}

MainWindow::~MainWindow() {
    qDebug() << "[Destruct] MainWindow";
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
}

void MainWindow::initValues() {
    untitledCount = 0;
}
