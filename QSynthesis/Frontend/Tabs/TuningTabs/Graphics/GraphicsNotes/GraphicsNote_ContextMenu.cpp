#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Modules/Scrolls/NotesScrollArea.h"
#include "../../TuningGroup.h"

void GraphicsNote::openContextMenu() {
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

    connect(portamentoAction, &QAction::triggered, this, &GraphicsNote::handlePortamentoTriggered);
    connect(vibratoAction, &QAction::triggered, this, &GraphicsNote::handleVibratoTriggered);
    connect(vibratoEditorAction, &QAction::triggered, this,
            &GraphicsNote::handleVibratoEditorTriggered);
    connect(propertyAction, &QAction::triggered, this, &GraphicsNote::handlePropertyTriggered);
    connect(voiceBankAction, &QAction::triggered, this, &GraphicsNote::handleLyricConfigTriggered);

    connect(tempoAction, &QAction::triggered, this, &GraphicsNote::handleTempoTriggered);
    connect(removeTempoAction, &QAction::triggered, this,
            &GraphicsNote::handleRemoveTempoTriggered);

    portamentoAction->setChecked(!m_curves->Points.isEmpty());
    vibratoAction->setChecked(!m_curves->Vibrato.isEmpty());
    vibratoEditorAction->setChecked(m_curves->hasVBREditor());
    vibratoEditorAction->setEnabled(!m_curves->Vibrato.isEmpty() &&
                                    m_curves->solid());
    removeTempoAction->setEnabled(tempoEdited());

    menu->exec(QCursor::pos());
    menu->clear();
}

void GraphicsNote::handlePortamentoTriggered(bool checked) {
    Mode2Handler *curves = m_curves;
    if (curves->Points.isEmpty()) {
        m_editor->addPortamento(this);
    } else {
        m_editor->removePortamento(this);
    }
}

void GraphicsNote::handleVibratoTriggered(bool checked) {
    Mode2Handler *curves = m_curves;
    if (curves->Vibrato.isEmpty()) {
        m_editor->addVibrato(this);
        if (curves->solid()) {
            m_curves->initVibratoEditor();
        }
    } else {
        m_editor->removeVibrato(this);
    }
}

void GraphicsNote::handleVibratoEditorTriggered(bool checked) {
    if (m_curves->Vibrato.isEmpty()) {
        return;
    }
    if (m_curves->hasVBREditor()) {
        m_curves->removeVibrtoEditor();
    } else {
        m_curves->initVibratoEditor();
    }
}

void GraphicsNote::handlePropertyTriggered() {
    m_editor->ptrs()->tab->showNoteProperty();
}

void GraphicsNote::handleLyricConfigTriggered() {
    m_editor->ptrs()->tab->configueLyric();
}

void GraphicsNote::handleTempoTriggered() {
    qDragIn.removeAll();
    qDragIn.addOne(this);
    qTabIn->showTempoEdit();
}

void GraphicsNote::handleRemoveTempoTriggered() {
    qDragIn.removeAll();
    qDragIn.addOne(this);
    qTabIn->showTempoEdit(true);
}
