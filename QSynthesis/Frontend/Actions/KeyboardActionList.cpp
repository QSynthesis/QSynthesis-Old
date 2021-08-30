#include "KeyboardActionList.h"

KeyboardActionList::KeyboardActionList(QObject *parent) : BaseActionList(parent) {
}

KeyboardActionList::~KeyboardActionList() {
}

void KeyboardActionList::setNaturalStatus() {
    setCommonActionsEnabled(true);

    saveAsFile->setEnabled(false);

    playPause->setEnabled(false);
    replay->setEnabled(false);
    stop->setEnabled(false);
}
