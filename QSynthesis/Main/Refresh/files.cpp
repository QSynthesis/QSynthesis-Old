#include "mainwindow.h"

void MainWindow::reloadConfig() {
}

void MainWindow::reloadVoice() {
}

void MainWindow::reloadPlugins() {
    QMenu *pluginMenu = tuningActions->pluginMenu;

    pluginMenu->clear();
    QList<PluginInfo *> dirs = plugins->dirs();

    if (dirs.isEmpty()) {
        QAction *emptyAction = new QAction(tr("Null"), pluginMenu);
        pluginMenu->addAction(emptyAction);
    } else {
        for (int i = 0; i < dirs.size(); ++i) {
            PluginInfo *plugin = dirs.at(i);
            QString name = plugin->name();
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
