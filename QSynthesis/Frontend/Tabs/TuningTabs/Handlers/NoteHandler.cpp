#include "NoteHandler.h"
#include "../Areas/Editor/NotesArea.h"
#include "../Graphics/GraphicsNote.h"
#include "../TuningGroup.h"

NoteHandler::NoteHandler() {
    init();
}

NoteHandler::NoteHandler(GraphicsNote *note, NotesArea *editor)
    : QObject(editor), m_note(note), m_editor(editor) {
    init();
}

NoteHandler::~NoteHandler() {
}

void NoteHandler::init() {
    m_lyricColor = Qt::black;
    m_restLineColor = QColor(0xCCCCCC);
    m_restFillColor = QColor(0xEEEEEE);
    m_listedLineColor = QColor(0x0099FF);
    m_listedFillColor = QColor(0x40D9FF);
    m_unlistedLineColor = QColor(0x105685);
    m_unlistedFillColor = QColor(0x1881C7);
}

GraphicsNote *NoteHandler::note() const {
    return m_note;
}

void NoteHandler::setNote(GraphicsNote *note) {
    m_note = note;
}

NotesArea *NoteHandler::editor() const {
    return m_editor;
}

void NoteHandler::setEditor(NotesArea *editor) {
    m_editor = editor;
    setParent(editor);
}

void NoteHandler::update() {
    m_note->update();
}
