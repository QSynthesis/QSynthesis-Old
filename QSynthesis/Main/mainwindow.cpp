#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setAcceptDrops(true); // Accept Drops
    initValues();

    qDebug() << QTextCodec::availableCodecs();
}

void MainWindow::initAndShow() {
    reloadBackendStrings();

    initMenuBar();
    initActionLists();

    initTabs();      // Initialize Tab Manager
    initPreviewer(); // Initialize other Modules
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
    settingIni.windowRect = geometry();
    settingIni.windowMaximized = windowState() == Qt::WindowMaximized;

    qDebug() << "[Destruct] MainWindow";
}

void MainWindow::initValues() {
    untitledCount = 0;
}

void MainWindow::initWindow() {
    bool hasSize = false;
    QRect rect = settingIni.windowRect;
    bool max = settingIni.windowMaximized;
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
