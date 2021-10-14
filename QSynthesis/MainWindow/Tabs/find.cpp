#include "QSTabs.h"
#include "mainwindow.h"

int MainWindow::findTuningTab(const QString &filename) {
    int i;
    int j = -1;

    for (i = 0; i < tabs->count(); ++i) {
        TuningTab *tab = qobject_cast<TuningTab *>(tabAt(i));
        if (!tab || tab->isDeleted() || tab->isUntitled()) {
            continue;
        }
        if (isSameFile(tab->filename(), filename)) {
            j = i;
            break;
        }
    }

    return j;
}

int MainWindow::findVoiceBankTab(const QString &dirname, Qs::DirRelation *relation) {
    int i;
    int j = -1;

    for (i = 0; i < tabs->count(); ++i) {
        VoiceBankTab *tab = qobject_cast<VoiceBankTab *>(tabAt(i));
        if (tab) {
            if (isSameFile(tab->filename(), dirname)) {
                *relation = Qs::SameDir;
                j = i;
                break;
            } else if (isSubDir(tab->filename(), dirname)) {
                *relation = Qs::ParentDir;
                j = i;
                break;
            } else if (isSubDir(dirname, tab->filename())) {
                *relation = Qs::SubDir;
                j = i;
                break;
            }
        }
    }

    return j;
}

int MainWindow::findSpecialTab(CentralTab::TabType type) {
    int i;
    int j = -1;
    for (i = 0; i < tabs->count(); ++i) {
        CentralTab *tab = tabAt(i);
        if (tab && tab->tabType() == type) {
            j = i;
            break;
        }
    }
    return j;
}

WelcomeTab *MainWindow::createWelcomeTab() {
    WelcomeTab *tab = new WelcomeTab(tabs);
    tab->tabActions = welcomeActions;

    tabs->addTab(tab, "");
    tab->setFixedname(tr("Welcome"));

    return tab;
}

SettingTab *MainWindow::createSettingTab() {
    SettingTab *tab = new SettingTab(tabs);
    tab->tabActions = settingActions;

    tabs->addTab(tab, "");
    tab->setFixedname(tr("Settings"));

    return tab;
}

KeyboardTab *MainWindow::createKeyboardTab() {
    KeyboardTab *tab = new KeyboardTab(tabs);
    tab->tabActions = keyboardActions;

    tabs->addTab(tab, "");
    tab->setFixedname(tr("Keyboard"));

    return tab;
}

VoiceBankTab *MainWindow::createVoiceBankTab(const QString &filename) {
    VoiceBankTab *tab = new VoiceBankTab(tabs);
    tab->tabActions = voiceActions;

    tabs->addTab(tab, "");
    tab->setFilename(filename);

    return tab;
}

TuningTab *MainWindow::createTuningTab(const QString &filename) {
    TuningTab *tab = new TuningTab(tabs);
    tab->tabActions = tuningActions;

    tabs->addTab(tab, "");
    tab->setFilename(filename);
    return tab;
}
