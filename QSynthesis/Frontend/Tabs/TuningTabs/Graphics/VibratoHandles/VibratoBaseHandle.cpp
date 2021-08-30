#include "VibratoBaseHandle.h"

VibratoObject::VibratoObject(NotesArea *editor, Mode2Handler *scope)
    : m_editor(editor), m_scope(scope) {
}

VibratoObject::~VibratoObject() {
}
