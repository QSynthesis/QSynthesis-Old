#include "QSActions.h"
#include "QSTabs.h"
#include "SettingIniFile.h"
#include "Utils/Templates.h"
#include "application.h"
#include "mainwindow.h"

void MainWindow::handleOpenRecentFile() {
    QAction *action = qobject_cast<QAction *>(sender());
    QString filename = action->data().toString();
    if (isDirExist(filename)) {
        addVoiceBankTab(filename);
    } else {
        addTuningTab(filename);
    }
}

void MainWindow::handleMoreRecentFile() {
    QStringList projects = qSetting->projects.valid();

    int index =
        tabs->useSelector(batchReplace(projects, QDir::toNativeSeparators), tr("Select file"), -1);
    if (index >= 0) {
        addTuningTab(projects.at(index));
    }
}

void MainWindow::handleMoreRecentFolder() {
    QStringList folders = qSetting->folders.valid();

    int index =
        tabs->useSelector(batchReplace(folders, QDir::toNativeSeparators), tr("Select folder"), -1);
    if (index >= 0) {
        addTuningTab(folders.at(index));
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
