#include "Document/SettingIniFile.h"
#include "QSActions.h"
#include "mainwindow.h"

void MainWindow::clearRecentMenu() {
    QMenu *recentMenu = welcomeActions->recentMenu;
    recentMenu->clear();

    CentralTab *tab = currentTab();
    if (tab && tab->tabType() == Qs::Welcome) {
        tab->enter();
    }
}

void MainWindow::reloadRecentMenu() {
    QMenu *recentMenu = welcomeActions->recentMenu;

    QStringList projects = qSetting->projects.valid();
    QStringList folders = qSetting->folders.valid();

    // Remove all Actions
    clearRecentMenu();

    QVector<QAction *> ustFiles;
    QVector<QAction *> voiceBanks;

    int fileActions = 0;
    for (auto it = projects.begin(); it != projects.end(); ++it) {
        if (fileActions == 10) {
            break;
        }
        QString name = *it;
        QAction *action = new QAction(name, recentMenu);
        action->setData(name);
        connect(action, &QAction::triggered, this, &MainWindow::handleOpenRecentFile);
        ustFiles.append(action);
        fileActions++;
    }

    int folderActions = 0;
    for (auto it = folders.begin(); it != folders.end(); ++it) {
        if (folderActions == 10) {
            break;
        }
        QString name = *it;
        QAction *action = new QAction(name, recentMenu);
        action->setData(name);
        connect(action, &QAction::triggered, this, &MainWindow::handleOpenRecentFile);
        voiceBanks.append(action);
        folderActions++;
    }

    // ust
    int i;
    for (i = 0; i < ustFiles.size(); ++i) {
        QAction *action = ustFiles[i];
        recentMenu->addAction(action);
    }
    if (i > 0) {
        recentMenu->addSeparator();
    }

    // voice
    for (i = 0; i < voiceBanks.size(); ++i) {
        QAction *action = voiceBanks[i];
        recentMenu->addAction(action);
    }
    if (i > 0) {
        recentMenu->addSeparator();
    }

    if (ustFiles.isEmpty() && voiceBanks.isEmpty()) {
        QAction *emptyAction = new QAction(tr("Null"), recentMenu);
        recentMenu->addAction(emptyAction);
    } else {
        bool more = false;
        if (fileActions < projects.size()) {
            QAction *moreAction = new QAction(tr("More files..."), recentMenu);
            recentMenu->addAction(moreAction);
            connect(moreAction, &QAction::triggered, this, &MainWindow::handleMoreRecentFile);
            more = true;
        }
        if (folderActions < folders.size()) {
            QAction *moreAction = new QAction(tr("More directories..."), recentMenu);
            recentMenu->addAction(moreAction);
            connect(moreAction, &QAction::triggered, this, &MainWindow::handleMoreRecentFolder);
            more = true;
        }
        if (more) {
            recentMenu->addSeparator();
        }
        QAction *clearRecentAction = new QAction(tr("Clear Recent List"), recentMenu);
        recentMenu->addAction(clearRecentAction);
        connect(clearRecentAction, &QAction::triggered, this, &MainWindow::handleClearRecentMenu);
    }
}
