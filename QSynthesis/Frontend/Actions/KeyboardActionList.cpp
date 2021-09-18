#include "KeyboardActionList.h"

Q_SINGLETON_DECLARE(KeyboardActionList)

KeyboardActionList::KeyboardActionList(QObject *parent) : BaseActionList(parent) {
    createCasePrivate();
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
