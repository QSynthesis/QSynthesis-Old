#include "../KeyboardTab.h"
#include "Actions/TuningActionList.h"
#include "Actions/VoiceActionList.h"
#include "Actions/WelcomeActionList.h"
#include "TabWidget.h"

void KeyboardTab::loadCore() {
    BaseActionList *actionList = WelcomeActionList::instance();
    const QList<QAction *> &actions = actionList->commonActions();
    for (auto it = actions.begin(); it != actions.end(); ++it) {
        commonKeyTab->addActionData(*it);
    }

    actionList = TuningActionList::instance();
    const QList<QAction *> &actions2 = actionList->actions();
    for (auto it = actions2.begin(); it != actions2.end(); ++it) {
        projectKeyTab->addActionData(*it);
    }

    actionList = VoiceActionList::instance();
    const QList<QAction *> &actions3 = actionList->actions();
    for (auto it = actions3.begin(); it != actions3.end(); ++it) {
        voiceKeyTab->addActionData(*it);
    }
}

void KeyboardTab::saveCore() {
}
