#include "WelcomeActionList.h"

WelcomeActionList::WelcomeActionList(QObject *parent) : BaseActionList(parent) {
}

WelcomeActionList::~WelcomeActionList() {
}

void WelcomeActionList::setNaturalStatus() {
    setCommonActionsEnabled(true);

    saveFile->setEnabled(false);
    saveAsFile->setEnabled(false);
    restoreFile->setEnabled(false);

    undo->setEnabled(false);
    redo->setEnabled(false);
    selectAll->setEnabled(false);
    deselect->setEnabled(false);

    reset->setEnabled(false);
    playPause->setEnabled(false);
    replay->setEnabled(false);
    stop->setEnabled(false);
}
