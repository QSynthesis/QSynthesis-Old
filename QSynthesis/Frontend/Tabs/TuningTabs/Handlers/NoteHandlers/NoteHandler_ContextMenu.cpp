#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Modules/Scrolls/NotesScrollArea.h"
#include "../../TuningGroup.h"
#include "../NoteHandler.h"

void NoteHandler::openContextMenu() {
    QMenu *menu = m_editor->view()->viewMenu;

    QAction *portamentoAction = new QAction(tr("Portamento"), menu);
    QAction *vibratoAction = new QAction(tr("Vibrato"), menu);
    QAction *vibratoEditorAction = new QAction(tr("Vibrato Editor"), menu);
    QAction *propertyAction = new QAction(tr("Note Properties..."), menu);
    QAction *voiceBankAction = new QAction(tr("Voice Bank Configue"), menu);

    QAction *tempoAction = new QAction(tr("Tempo..."), menu);
    QAction *removeTempoAction = new QAction(tr("Remove Tempo"), menu);

    menu->addAction(portamentoAction);
    menu->addAction(vibratoAction);
    menu->addAction(vibratoEditorAction);
    menu->addSeparator();
    menu->addAction(tempoAction);
    menu->addAction(removeTempoAction);
    menu->addSeparator();
    menu->addAction(propertyAction);
    menu->addAction(voiceBankAction);

    portamentoAction->setCheckable(true);
    vibratoAction->setCheckable(true);
    vibratoEditorAction->setCheckable(true);

    connect(portamentoAction, &QAction::triggered, this, &NoteHandler::handlePortamentoTriggered);
    connect(vibratoAction, &QAction::triggered, this, &NoteHandler::handleVibratoTriggered);
    connect(vibratoEditorAction, &QAction::triggered, this,
            &NoteHandler::handleVibratoEditorTriggered);
    connect(propertyAction, &QAction::triggered, this, &NoteHandler::handlePropertyTriggered);
    connect(voiceBankAction, &QAction::triggered, this, &NoteHandler::handleLyricConfigTriggered);

    connect(tempoAction, &QAction::triggered, this, &NoteHandler::handleTempoTriggered);
    connect(removeTempoAction, &QAction::triggered, this, &NoteHandler::handleRemoveTempoTriggered);

    portamentoAction->setChecked(!m_note->curves()->Points.isEmpty());
    vibratoAction->setChecked(!m_note->curves()->Vibrato.isEmpty());
    vibratoEditorAction->setChecked(m_note->curves()->hasVBREditor());
    vibratoEditorAction->setEnabled(!m_note->curves()->Vibrato.isEmpty() &&
                                    m_note->curves()->solid());
    removeTempoAction->setEnabled(m_note->tempoEdited());

    menu->exec(QCursor::pos());
    menu->clear();
}

void NoteHandler::handlePortamentoTriggered(bool checked) {
    Mode2Handler *curves = m_note->curves();
    if (curves->Points.isEmpty()) {
        m_editor->addPortamento(m_note);
    } else {
        m_editor->removePortamento(m_note);
    }
}

void NoteHandler::handleVibratoTriggered(bool checked) {
    Mode2Handler *curves = m_note->curves();
    if (curves->Vibrato.isEmpty()) {
        m_editor->addVibrato(m_note);
        if (curves->solid()) {
            m_note->curves()->initVibratoEditor();
        }
    } else {
        m_editor->removeVibrato(m_note);
    }
}

void NoteHandler::handleVibratoEditorTriggered(bool checked) {
    Mode2Handler *curves = m_note->curves();
    if (curves->Vibrato.isEmpty()) {
        return;
    }

    if (curves->hasVBREditor()) {
        curves->removeVibrtoEditor();
    } else {
        curves->initVibratoEditor();
    }
}

void NoteHandler::handlePropertyTriggered() {
    m_editor->ptrs()->tab->showNoteProperty();
}

void NoteHandler::handleLyricConfigTriggered() {
    m_editor->ptrs()->tab->configueLyric();
}

void NoteHandler::handleTempoTriggered() {
    qDragIn.removeAll();
    qDragIn.addOne(m_note);

    m_editor->ptrs()->tab->showTempoEdit();
}

void NoteHandler::handleRemoveTempoTriggered() {
    qDragIn.removeAll();
    qDragIn.addOne(m_note);

    m_editor->ptrs()->tab->showTempoEdit(true);
}
