#include "../../Editor/Areas/NotesArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Scrolls/NotesScrollArea.h"
#include "../../TuningGroup.h"

void GraphicsNote::openContextMenu() {
    QStringList list{
        tr("Portamento"),
        tr("Vibrato"),
        tr("Vibrato Editor"),
        "",
        tr("Tempo..."),
        tr("Remove Tempo"),
        "",
        tr("Note Properties..."),
        tr("Voice Bank Manage"),
    };

    TemporaryMenu *menu = new TemporaryMenu(list, m_editor->view());

    menu->setCheckedAt(0, !m_curves->Points.isEmpty());
    menu->setCheckedAt(1, !m_curves->Vibrato.isEmpty());
    menu->setCheckedAt(2, m_curves->hasVBREditor());
    menu->setEnabledAt(2, !m_curves->Vibrato.isEmpty() && m_curves->solid());
    menu->setEnabledAt(4, tempoEdited());

    int index = menu->start();
    menu->deleteLater();

    switch (index) {
    case 0:
        switchPortamento();
        break;
    case 1:
        switchVibrato();
        break;
    case 2:
        reverseVibratoEditor();
        break;
    case 3:
        openTempoEdit();
        break;
    case 4:
        removeTempo();
        break;
    case 5:
        openProperty();
        break;
    case 6:
        configueLyric();
        break;
    default:
        break;
    }
}

void GraphicsNote::switchPortamento() {
    Mode2Handler *curves = m_curves;
    if (curves->Points.isEmpty()) {
        m_editor->addPortamento(this);
    } else {
        m_editor->removePortamento(this);
    }
}

void GraphicsNote::switchVibrato() {
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

void GraphicsNote::reverseVibratoEditor() {
    if (m_curves->Vibrato.isEmpty()) {
        return;
    }
    if (m_curves->hasVBREditor()) {
        m_curves->removeVibrtoEditor();
    } else {
        m_curves->initVibratoEditor();
    }
}

void GraphicsNote::openProperty() {
    m_editor->ptrs()->tab->showNoteProperty();
}

void GraphicsNote::configueLyric() {
    m_editor->ptrs()->tab->configueLyric();
}

void GraphicsNote::openTempoEdit() {
    qDragIn.removeAll();
    qDragIn.addOne(this);
    qTabIn->showTempoEdit();
}

void GraphicsNote::removeTempo() {
    qDragIn.removeAll();
    qDragIn.addOne(this);
    qTabIn->showTempoEdit(true);
}
