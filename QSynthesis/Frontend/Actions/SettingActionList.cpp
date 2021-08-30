#include "SettingActionList.h"

SettingActionList::SettingActionList(QObject *parent) : BaseActionList(parent) {
}

SettingActionList::~SettingActionList() {
}

void SettingActionList::setNaturalStatus() {
    setCommonActionsEnabled(true);

    saveAsFile->setEnabled(false);

    selectAll->setEnabled(false);
    deselect->setEnabled(false);

    playPause->setEnabled(false);
    replay->setEnabled(false);
    stop->setEnabled(false);
}
