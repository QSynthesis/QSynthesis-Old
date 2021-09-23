#include "../../Areas/Editor/NotesArea.h"
#include "../../TuningGroup.h"
#include "../EditorForm.h"
#include "Templates/TemporaryMenu.h"
#include "mainwindow.h"

void EditorForm::initMenu() {
    m_menu = new QMenu(this);

    adsorbMenu = new QMenu(tr("Quantization"), m_menu);
    stateMenu = new QMenu(tr("State"), m_menu);

    fullAdsorbAction = new QAction(tr("Quarter"), m_menu);
    halfAdsorbAction = new QAction(tr("1/2 Quarter"), m_menu);
    quarterAdsorbAction = new QAction(tr("1/4 Quarter"), m_menu);
    sixthAdsorbAction = new QAction(tr("1/6 Quarter"), m_menu);
    eighthAdsorbAction = new QAction(tr("1/8 Quarter"), m_menu);
    twelfthAdsorbAction = new QAction(tr("1/12 Quarter"), m_menu);
    sixteenthAdsorbAction = new QAction(tr("1/16 Quarter"), m_menu);
    twentyForthAdsorbAction = new QAction(tr("1/24 Quarter"), m_menu);
    thirtySecondAdsorbAction = new QAction(tr("1/32 Quarter"), m_menu);
    noAdsorbAction = new QAction(tr("None"), m_menu);

    noteVisibleAction = new QAction(tr("Display note block"), m_menu);
    pitchVisibleAction = new QAction(tr("Display pitch curves"), m_menu);
    envelopeVisibleAction = new QAction(tr("Display envelope"), m_menu);
    paramsVisibleAction = new QAction(tr("Display parameters"), m_menu);

    fullAdsorbAction->setCheckable(true);
    halfAdsorbAction->setCheckable(true);
    quarterAdsorbAction->setCheckable(true);
    sixthAdsorbAction->setCheckable(true);
    eighthAdsorbAction->setCheckable(true);
    twelfthAdsorbAction->setCheckable(true);
    sixteenthAdsorbAction->setCheckable(true);
    twentyForthAdsorbAction->setCheckable(true);
    thirtySecondAdsorbAction->setCheckable(true);
    noAdsorbAction->setCheckable(true);

    noteVisibleAction->setCheckable(true);
    pitchVisibleAction->setCheckable(true);
    envelopeVisibleAction->setCheckable(true);
    paramsVisibleAction->setCheckable(true);

    connect(fullAdsorbAction, &QAction::triggered, this, &EditorForm::handleFullAdsorb);
    connect(halfAdsorbAction, &QAction::triggered, this, &EditorForm::handleHalfAdsorb);
    connect(quarterAdsorbAction, &QAction::triggered, this, &EditorForm::handleQuarterAdsorb);
    connect(sixthAdsorbAction, &QAction::triggered, this, &EditorForm::handleSixthAdsorb);
    connect(eighthAdsorbAction, &QAction::triggered, this, &EditorForm::handleEighthAdsorb);
    connect(twelfthAdsorbAction, &QAction::triggered, this, &EditorForm::handleTwelfthAdsorb);
    connect(sixteenthAdsorbAction, &QAction::triggered, this, &EditorForm::handleSixteenthAdsorb);
    connect(twentyForthAdsorbAction, &QAction::triggered, this,
            &EditorForm::handleTwentyForthAdsorb);
    connect(thirtySecondAdsorbAction, &QAction::triggered, this,
            &EditorForm::handleThirtySecondAdsorb);
    connect(noAdsorbAction, &QAction::triggered, this, &EditorForm::handleNoneAdsorb);

    connect(noteVisibleAction, &QAction::triggered, this, &EditorForm::handleSwitchNoteVisibility);
    connect(pitchVisibleAction, &QAction::triggered, this,
            &EditorForm::handleSwitchPitchVisibility);
    connect(envelopeVisibleAction, &QAction::triggered, this,
            &EditorForm::handleSwitchEnvelopeVisibility);
    connect(paramsVisibleAction, &QAction::triggered, this,
            &EditorForm::handleSwitchParamsVisibility);

    adsorbMenu->addAction(fullAdsorbAction);
    adsorbMenu->addAction(halfAdsorbAction);
    adsorbMenu->addAction(quarterAdsorbAction);
    adsorbMenu->addAction(sixthAdsorbAction);
    adsorbMenu->addAction(eighthAdsorbAction);
    adsorbMenu->addAction(twelfthAdsorbAction);
    adsorbMenu->addAction(sixteenthAdsorbAction);
    adsorbMenu->addAction(twentyForthAdsorbAction);
    adsorbMenu->addAction(thirtySecondAdsorbAction);
    adsorbMenu->addSeparator();
    adsorbMenu->addAction(noAdsorbAction);

    stateMenu->addAction(noteVisibleAction);
    stateMenu->addAction(pitchVisibleAction);
    stateMenu->addAction(envelopeVisibleAction);
    stateMenu->addAction(paramsVisibleAction);

    m_menu->addMenu(adsorbMenu);
    m_menu->addMenu(stateMenu);
}

void EditorForm::handleMenuBtnClicked() {
    fullAdsorbAction->setChecked(m_ptrs->currentAdsorb == 1);
    halfAdsorbAction->setChecked(m_ptrs->currentAdsorb == 2);
    quarterAdsorbAction->setChecked(m_ptrs->currentAdsorb == 4);
    sixthAdsorbAction->setChecked(m_ptrs->currentAdsorb == 6);
    eighthAdsorbAction->setChecked(m_ptrs->currentAdsorb == 8);
    twelfthAdsorbAction->setChecked(m_ptrs->currentAdsorb == 12);
    sixteenthAdsorbAction->setChecked(m_ptrs->currentAdsorb == 16);
    twentyForthAdsorbAction->setChecked(m_ptrs->currentAdsorb == 24);
    thirtySecondAdsorbAction->setChecked(m_ptrs->currentAdsorb == 32);
    noAdsorbAction->setChecked(m_ptrs->currentAdsorb == 0);

    noteVisibleAction->setChecked(m_ptrs->notesArea->notesVisible());
    pitchVisibleAction->setChecked(m_ptrs->notesArea->pitchesVisible());
    envelopeVisibleAction->setChecked(m_ptrs->notesArea->envelopesVisible());
    paramsVisibleAction->setChecked(m_ptrs->notesArea->paramsVisible());

    m_menu->exec(QCursor::pos());
}

void EditorForm::handleFullAdsorb() {
    setLengthUnit(1);
}
void EditorForm::handleHalfAdsorb() {
    setLengthUnit(2);
}
void EditorForm::handleQuarterAdsorb() {
    setLengthUnit(4);
}
void EditorForm::handleSixthAdsorb() {
    setLengthUnit(6);
}
void EditorForm::handleEighthAdsorb() {
    setLengthUnit(8);
}
void EditorForm::handleTwelfthAdsorb() {
    setLengthUnit(12);
}
void EditorForm::handleSixteenthAdsorb() {
    setLengthUnit(16);
}
void EditorForm::handleTwentyForthAdsorb() {
    setLengthUnit(24);
}
void EditorForm::handleThirtySecondAdsorb() {
    setLengthUnit(32);
}
void EditorForm::handleNoneAdsorb() {
    setLengthUnit(0);
}

void EditorForm::handleSwitchNoteVisibility() {
    m_ptrs->notesArea->setNotesVisible(!m_ptrs->notesArea->notesVisible());
}

void EditorForm::handleSwitchPitchVisibility() {
    m_ptrs->notesArea->setPitchesVisible(!m_ptrs->notesArea->pitchesVisible());
}

void EditorForm::handleSwitchEnvelopeVisibility() {
    m_ptrs->notesArea->setEnvelopesVisible(!m_ptrs->notesArea->envelopesVisible());
    qDebug() << m_ptrs->notesArea->envelopesVisible();
}

void EditorForm::handleSwitchParamsVisibility() {
    m_ptrs->notesArea->setParamsVisible(!m_ptrs->notesArea->paramsVisible());
}

void EditorForm::setLengthUnit(int n) {
    m_ptrs->currentAdsorb = n;
    m_ptrs->notesArea->updateBackground();

    qSetting->lastQuantize = n;
}
