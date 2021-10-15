#include "QSActions.h"
#include "application.h"
#include "mainwindow.h"

void MainWindow::initModules() {
    // Voice
    qVoice->setDirname(voiceProfile());
    if (!qVoice->load()) {
        QMessageBox::critical(this, ErrorTitle, tr("Cannot load voice banks."));
        exit(2);
    }
    connect(qVoice, &VoiceManager::reloadRequested, this, &MainWindow::reloadVoice);

    // Plugins
    qPlugins->setDirname(pluginsProfile());
    if (!qPlugins->load()) {
        QMessageBox::critical(this, ErrorTitle, tr("Cannot load plugins."));
        exit(3);
    }
    connect(qPlugins, &PluginManager::reloadRequested, this, &MainWindow::reloadPlugins);

    // Themes
    if (!isDirExist(themesProfile())) {
        QMessageBox::critical(this, ErrorTitle, tr("Cannot load themes."));
        exit(4);
    }
    qTheme->loadTheme(qSetting->themeIndex);

    // Languages
    if (!isDirExist(languagesProfile())) {
        QMessageBox::critical(this, ErrorTitle, tr("Cannot load translations."));
        exit(5);
    }
    qData->load();
}

void MainWindow::freeModules() {
    qVoice->quit();
    qPlugins->quit();
}

void MainWindow::reloadVoice() {
}

void MainWindow::reloadPlugins() {
    QMenu *pluginMenu = tuningActions->pluginMenu;

    pluginMenu->clear();
    QList<PluginInfo> dirs = qPlugins->plugins();

    if (dirs.isEmpty()) {
        QAction *emptyAction = new QAction(tr("Null"), pluginMenu);
        pluginMenu->addAction(emptyAction);
    } else {
        for (int i = 0; i < dirs.size(); ++i) {
            const PluginInfo &plugin = dirs.at(i);
            QString name = plugin.name();
            QAction *action = new QAction(name, pluginMenu);
            action->setData(i);
            connect(action, &QAction::triggered, this, &MainWindow::handleExecutePlugin);
            pluginMenu->addAction(action);
        }
    }

    pluginMenu->addSeparator();

    QAction *openAction = new QAction(tr("Open plugin directory(&O)"), pluginMenu);
    pluginMenu->addAction(openAction);
    connect(openAction, &QAction::triggered, this, &MainWindow::handleOpenPluginDir);
}

void MainWindow::reloadThemes() {
}

void MainWindow::reloadLanguages() {
}
