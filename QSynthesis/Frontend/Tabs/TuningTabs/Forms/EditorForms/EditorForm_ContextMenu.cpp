#include "../../Areas/Editor/NotesArea.h"
#include "../../TuningGroup.h"
#include "../EditorForm.h"
#include "Actions/TuningActionList.h"
#include "Templates/TemporaryMenu.h"
#include "mainwindow.h"

void EditorForm::handleMenuBtnClicked() {
    m_ptrs->tab->tabActions->fullAdsorb->setChecked(m_ptrs->currentAdsorb == 1);
    m_ptrs->tab->tabActions->halfAdsorb->setChecked(m_ptrs->currentAdsorb == 2);
    m_ptrs->tab->tabActions->quarterAdsorb->setChecked(m_ptrs->currentAdsorb == 4);
    m_ptrs->tab->tabActions->sixthAdsorb->setChecked(m_ptrs->currentAdsorb == 6);
    m_ptrs->tab->tabActions->eighthAdsorb->setChecked(m_ptrs->currentAdsorb == 8);
    m_ptrs->tab->tabActions->twelfthAdsorb->setChecked(m_ptrs->currentAdsorb == 12);
    m_ptrs->tab->tabActions->sixteenthAdsorb->setChecked(m_ptrs->currentAdsorb == 16);
    m_ptrs->tab->tabActions->twentyForthAdsorb->setChecked(m_ptrs->currentAdsorb == 24);
    m_ptrs->tab->tabActions->thirtySecondAdsorb->setChecked(m_ptrs->currentAdsorb == 32);
    m_ptrs->tab->tabActions->noAdsorb->setChecked(m_ptrs->currentAdsorb == 0);

    m_ptrs->tab->tabActions->switchNoteState->setChecked(m_ptrs->notesArea->notesVisible());
    m_ptrs->tab->tabActions->switchPitchState->setChecked(m_ptrs->notesArea->pitchesVisible());
    m_ptrs->tab->tabActions->switchEnvelopeState->setChecked(
        m_ptrs->notesArea->envelopesVisible());
    m_ptrs->tab->tabActions->switchParamsState->setChecked(m_ptrs->notesArea->paramsVisible());

    m_ptrs->tab->tabActions->editorMenu->exec(QCursor::pos());
}

void EditorForm::setLengthUnit(int n) {
    m_ptrs->currentAdsorb = n;
    m_ptrs->notesArea->updateBackground();

    qSetting->lastQuantize = n;
}
