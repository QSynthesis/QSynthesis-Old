#include "SettingActionList.h"

Q_SINGLETON_DECLARE(SettingActionList)

SettingActionList::SettingActionList(QObject *parent) : BaseActionList(parent) {
    createCasePrivate();
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
