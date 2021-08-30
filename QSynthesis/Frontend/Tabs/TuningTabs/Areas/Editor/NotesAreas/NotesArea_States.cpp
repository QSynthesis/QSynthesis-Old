#include "../../../Graphics/GraphicsNote.h"
#include "../../../Handlers/EnvelopeHandler.h"
#include "../../../Handlers/Mode2Handler.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

bool NotesArea::isMoving() const {
    return m_moving;
}

void NotesArea::setNotesEnabled(bool enabled) {
    m_notesEnabled = enabled;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->setMovable(enabled);
    }
}

void NotesArea::setPitchesEnabled(bool enabled) {
    m_pitchesEnabled = enabled;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->curves()->setSolid(enabled);
    }
}

void NotesArea::setEnvelopesEnabled(bool enabled) {
    m_envelopesEnabled = enabled;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->envelope()->setSolid(enabled);
    }
}
