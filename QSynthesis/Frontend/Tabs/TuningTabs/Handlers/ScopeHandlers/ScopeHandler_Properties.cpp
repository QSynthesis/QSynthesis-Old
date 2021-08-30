#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../ScopeHandler.h"

Qs::Scope ScopeHandler::type() const {
    return m_type;
}

bool ScopeHandler::operator<(const ScopeHandler &another) const {
    return m_note->x() < another.note()->x();
}

GraphicsNote *ScopeHandler::note() const {
    return m_note;
}

void ScopeHandler::setNote(GraphicsNote *note) {
    m_note = note;
}

NotesArea *ScopeHandler::editor() const {
    return m_editor;
}

void ScopeHandler::setEditor(NotesArea *editor) {
    m_editor = editor;
    setParent(editor);
}

GraphicsLines *ScopeHandler::screen() const {
    return m_note->screen();
}

GraphicsNote *ScopeHandler::prevNote() const {
    return m_note->MPrev();
}

GraphicsNote *ScopeHandler::nextNote() const {
    return m_note->MNext();
}

GraphicsPoint *ScopeHandler::firstPoint() const {
    if (Points.isEmpty()) {
        return nullptr;
    }
    return Points.front();
}

GraphicsPoint *ScopeHandler::lastPoint() const {
    if (Points.isEmpty()) {
        return nullptr;
    }
    return Points.back();
}

bool ScopeHandler::solid() const {
    return m_solid;
}
