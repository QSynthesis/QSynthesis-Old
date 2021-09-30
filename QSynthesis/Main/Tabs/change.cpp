#include "Document/SettingIniFile.h"
#include "QSTabs.h"
#include "mainwindow.h"

TuningTab *MainWindow::addEmptyTab(const SectionNotes &oNotes) {
    TuningTab *tab = createTuningTab();
    makeUntitled(tab, oNotes.trackName());
    tab->newFile(oNotes);

    tabs->setCurrentWidget(tab);
    return tab;
}

VoiceBankTab *MainWindow::addVoiceBankTab(const QString &filename, bool notify) {
    Qs::DirRelation relation;
    int j = findVoiceBankTab(filename, &relation);

    // Find double opened tab
    if (j >= 0) {
        tabs->setCurrentIndex(j);

        VoiceBankTab *tab1 = qobject_cast<VoiceBankTab *>(currentTab());
        if (notify) {
            if (relation == Qs::ParentDir) {
                QString caption =
                    tr("You have opened the upper directory of this folder, please close first.");
                QMessageBox::warning(this, MainTitle, caption);
            } else if (relation == Qs::SubDir) {
                QString caption =
                    tr("You have opened the lower directory of this folder, please close first.");
                QMessageBox::warning(this, MainTitle, caption);
            }
        }

        return tab1;
    }

    // No double opened tab
    VoiceBankTab *tab = createVoiceBankTab(filename);
    tabs->setCurrentWidget(tab);
    bool loadSuccess = tab->load(); // Load File (setting.json)

    if (!loadSuccess) {
        removeTab(tab);
        // Remove from history
        if (qSetting->folders.remove(filename)) {
            // saveSettingIni();
            reloadRecentMenu();
        }
        return nullptr;
    } else {
        // Add to history
        qSetting->folders.advance(filename);
        // saveSettingIni();
        reloadRecentMenu();
    }

    return tab;
}

WelcomeTab *MainWindow::addWelcomeTab() {
    int j = findSpecialTab(Qs::Welcome);

    // Find double opened tab
    if (j >= 0) {
        tabs->setCurrentIndex(j);
        return qobject_cast<WelcomeTab *>(currentTab());
    }

    WelcomeTab *tab = createWelcomeTab();
    tabs->setCurrentWidget(tab);
    return tab;
}

KeyboardTab *MainWindow::addKeyboardTab() {
    int j = findSpecialTab(Qs::Keyboard);

    // Find double opened tab
    if (j >= 0) {
        tabs->setCurrentIndex(j);
        return qobject_cast<KeyboardTab *>(currentTab());
    }

    QString filename = keyboardConfigPath();
    KeyboardTab *tab = createKeyboardTab();

    tabs->setCurrentWidget(tab);

    tab->setFilename(filename);
    bool loadSuccess = tab->load(); // Load File (setting.json)
    if (!loadSuccess) {
        removeTab(tab);
        return nullptr;
    }

    return tab;
}

SettingTab *MainWindow::addSettingTab() {
    int j = findSpecialTab(Qs::Setting);

    // Find double opened tab
    if (j >= 0) {
        tabs->setCurrentIndex(j);
        return qobject_cast<SettingTab *>(currentTab());
    }

    QString filename = settingConifgPath();
    SettingTab *tab = createSettingTab();
    tabs->setCurrentWidget(tab);

    tab->setFilename(filename);
    bool loadSuccess = tab->load(); // Load File (setting.json)
    if (!loadSuccess) {
        removeTab(tab);
        return nullptr;
    }

    return tab;
}

TuningTab *MainWindow::addTuningTab(const QString &filename, bool noCloseIfInvalid) {
    int j = findTuningTab(filename);

    // Find double opened tab
    if (j >= 0) {
        tabs->setCurrentIndex(j);
        return qobject_cast<TuningTab *>(currentTab());
    }

    TuningTab *tab = createTuningTab(filename);
    tabs->setCurrentWidget(tab);

    bool loadSuccess = tab->load(); // Load File (setting.json)
    if (!loadSuccess) {
        if (noCloseIfInvalid) {
            qDebug() << "No close if invalid.";
            // Make unnamed
            makeUntitled(tab);
        } else {
            // Otherwise close
            removeTab(tab);
        }
        // Remove from history
        if (qSetting->projects.remove(filename)) {
            // saveSettingIni();
            reloadRecentMenu();
        }
        return nullptr;
    } else {
        // Add to history
        qSetting->projects.advance(filename);
        // saveSettingIni();
        reloadRecentMenu();
    }

    return tab;
}

bool MainWindow::addMultipleTabs(const QStringList &filenames, bool noCloseIfInvalid) {
    bool flag = false;

    for (auto it = filenames.begin(); it != filenames.end(); ++it) {
        QString filename = *it;
        if (isDirExist(filename)) {
            flag |= !!addVoiceBankTab(filename, false);
        } else {
            flag |= !!addTuningTab(filename, noCloseIfInvalid ? (tabs->count() == 0) : false);
        }
    }
    return flag;
}

void MainWindow::removeTab(CentralTab *tab) {
    removeTab(tabs->indexOf(tab));
}

void MainWindow::removeTab(int index) {
    CentralTab *tab = tabAt(index);

    if (!tab || (tab->tabType() == Qs::Welcome && tabs->count() == 1)) {
        return;
    }

    tabs->removeTab(index);
    delete tab;

    // If all tabs are closed, then add a welcoming tab
    if (tabs->count() == 0) {
        addWelcomeTab();
    } else {
        welcomeActions->switchFile->setEnabled(previousTab());
    }
}
