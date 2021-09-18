#include "WelcomeActionList.h"

Q_SINGLETON_DECLARE(WelcomeActionList)

WelcomeActionList::WelcomeActionList(QObject *parent) : BaseActionList(parent) {
    createCasePrivate();
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
