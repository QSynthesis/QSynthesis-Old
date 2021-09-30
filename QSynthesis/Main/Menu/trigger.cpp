#include "Document/SettingIniFile.h"
#include "Managers/PluginManager.h"
#include "QSActions.h"
#include "QSTabs.h"
#include "mainwindow.h"

void MainWindow::handleOpenRecentFile() {
    QAction *action = qobject_cast<QAction *>(sender());
    QString fileName = action->data().toString();
    if (isDirExist(fileName)) {
        addVoiceBankTab(fileName);
    } else {
        addTuningTab(fileName, false);
    }
}

void MainWindow::handleClearRecentMenu() {
    qSetting->projects.clear();
    qSetting->folders.clear();
    // saveSettingIni();
    reloadRecentMenu();
}

void MainWindow::handleExecutePlugin() {
    const QList<PluginInfo> &dirs = qPlugins->plugins();
    QAction *action = qobject_cast<QAction *>(sender());
    int index = action->data().toInt();
    const PluginInfo &plugin = dirs.at(index);

    qDebug() << "[Action]"
             << "Run plugin at" << index;

    CentralTab *tab = currentTab();
    if (tab->tabType() == Qs::Tuning) {
        TuningTab *tab1 = qobject_cast<TuningTab *>(tab);
        tab1->handleRunPlugin(plugin);
    }
}

void MainWindow::handleOpenPluginDir() {
    RevealFile(AppPath + Slash + DIR_NAME_PLUGIN);
}
