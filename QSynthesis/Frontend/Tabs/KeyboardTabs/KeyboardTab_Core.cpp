#include "../KeyboardTab.h"
#include "Actions/TuningActionList.h"
#include "Actions/VoiceActionList.h"
#include "Actions/WelcomeActionList.h"
#include "TabWidget.h"

void KeyboardTab::loadCore() {
    BaseActionList *actionList = WelcomeActionList::instance();
    const QList<QAction *> &actions = actionList->commonActions();
    commonKeyTab->removeAllData();
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        commonKeyTab->addShortcutData(*it);
    }

    actionList = TuningActionList::instance();
    const QList<QAction *> &actions2 = actionList->actions();
    projectKeyTab->removeAllData();
    for (auto it = actions2.begin(); it != actions2.end(); ++it) {
        projectKeyTab->addShortcutData(*it);
    }

    actionList = VoiceActionList::instance();
    const QList<QAction *> &actions3 = actionList->actions();
    voiceKeyTab->removeAllData();
    for (auto it = actions3.begin(); it != actions3.end(); ++it) {
        voiceKeyTab->addShortcutData(*it);
    }
}

void KeyboardTab::saveCore() {
    keys.commonShortcuts = commonKeyTab->currentShortcuts();
    keys.projectShortcuts = projectKeyTab->currentShortcuts();
    keys.voiceShortcuts = voiceKeyTab->currentShortcuts();
}

bool KeyboardTab::checkNoConflict() {
    ShortcutsData data;
    data.commonShortcuts = commonKeyTab->currentShortcuts();
    data.projectShortcuts = projectKeyTab->currentShortcuts();
    data.voiceShortcuts = voiceKeyTab->currentShortcuts();

    QPair<int, int> first, second;
    bool res = ShortcutsData::checkNoConflict(data, &first, &second);

    if (res) {
        return true;
    }

    if (first.first == 0 && second.first == 0) {
        QMessageBox::warning(
            this, MainTitle,
            tr("There's a conflict between item %1 and item %2 in general key bind!")
                .arg(first.second)
                .arg(second.second));
    } else if (first.first == 0 && second.first == 1) {
        QMessageBox::warning(this, MainTitle,
                             tr("There's a conflict between item %1 in general key bind and item "
                                "%2 in project key bind!")
                                 .arg(first.second)
                                 .arg(second.second));
    } else if (first.first == 1 && second.first == 1) {
        QMessageBox::warning(
            this, MainTitle,
            tr("There's a conflict between item %1 and item %2 in project key bind!")
                .arg(first.second)
                .arg(second.second));
    } else if (first.first == 0 && second.first == 2) {
        QMessageBox::warning(this, MainTitle,
                             tr("There's a conflict between item %1 in general key bind and item "
                                "%2 in voice manage key bind!")
                                 .arg(first.second)
                                 .arg(second.second));
    } else if (first.first == 2 && second.first == 2) {
        QMessageBox::warning(
            this, MainTitle,
            tr("There's a conflict between item %1 and item %2 in voice manage key bind!")
                .arg(first.second)
                .arg(second.second));
    }
    return false;
}
