#include "VoiceActionList.h"

VoiceActionList::VoiceActionList(QObject *parent) : BaseActionList(parent) {
}

VoiceActionList::~VoiceActionList() {
}

void VoiceActionList::setNaturalStatus() {
    setCommonActionsEnabled(true);
    setActionsEnabled(true);

    saveAsFile->setEnabled(false);
}

void VoiceActionList::updateStrings() {
    // File
    exportCurrent->setText(tr("Export current settings..."));

    QString fileType = tr("File");
    textToName(exportCurrent, fileType);

    // Edit
    moveUp->setText(tr("Move up"));
    moveDown->setText(tr("Move down"));
    moveTop->setText(tr("Move to top"));
    moveBottom->setText(tr("Move to bottom"));
    duplicate->setText(tr("Duplicate"));
    remove->setText(tr("Remove"));

    QString editType = tr("Edit");
    textToName(moveUp, editType);
    textToName(moveDown, editType);
    textToName(moveTop, editType);
    textToName(moveBottom, editType);
    textToName(duplicate, editType);
    textToName(remove, editType);

    // Modify
    generateFrq->setText(tr("Generate frequency map"));
    modifyAlias->setText(tr("Modify alias"));
    removeInvalid->setText(tr("Remove invalid samples"));
    setOffset->setText(tr("Set Offset"));
    setConstant->setText(tr("Set Consonant"));
    setBlank->setText(tr("Set Blank"));
    setPreUttr->setText(tr("Set Pre-Utterance"));
    setOverlap->setText(tr("Set Voice Overlap"));

    QString modifyType = tr("Modify");
    textToName(generateFrq, modifyType);
    textToName(modifyAlias, modifyType);
    textToName(removeInvalid, modifyType);
    textToName(setOffset, modifyType);
    textToName(setConstant, modifyType);
    textToName(setBlank, modifyType);
    textToName(setPreUttr, modifyType);
    textToName(setBlank, modifyType);

    // Preview

    // Tools
    buildInMenu->setTitle(tr("Build-in Tools"));

    // Help
}

void VoiceActionList::makeDefaultShortcuts() {
    duplicate->setShortcut(QKeySequence("Ctrl+D"));
    remove->setShortcut(QKeySequence("Del"));

    setOffset->setShortcut(QKeySequence("F1"));
    setOverlap->setShortcut(QKeySequence("F2"));
    setPreUttr->setShortcut(QKeySequence("F3"));
    setConstant->setShortcut(QKeySequence("F4"));
    setBlank->setShortcut(QKeySequence("F5"));
}

QList<QAction *> VoiceActionList::actions() const {
    return {
        exportCurrent, moveUp,     moveDown,    moveTop,     moveBottom,
        duplicate,     remove,     generateFrq, modifyAlias, removeInvalid,
        setOffset,     setOverlap, setPreUttr,  setConstant, setBlank,
    };
}
