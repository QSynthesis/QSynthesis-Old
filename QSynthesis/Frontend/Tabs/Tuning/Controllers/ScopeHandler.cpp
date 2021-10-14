#include "ScopeHandler.h"
#include "../Editor/Areas/NotesArea.h"
#include "../Graphics/GraphicsPoint.h"

ScopeHandler::ScopeHandler() : m_note(nullptr), m_editor(nullptr) {
    init();
}

ScopeHandler::ScopeHandler(GraphicsNote *note, NotesArea *editor)
    : QObject(editor), m_note(note), m_editor(editor) {
    init();
}

ScopeHandler::~ScopeHandler() {
}

void ScopeHandler::init() {
    m_solid = true;
    m_visible = true;
    m_moving = false;
}

void ScopeHandler::insertSort() {
    int i, j;
    GraphicsPoint *key;

    for (j = 1; j < Points.size(); ++j) {
        key = Points[j];
        i = j - 1;

        if (m_moving) {
            while (i >= 0 && Points[i]->x() > key->x()) {
                Points[i + 1] = Points[i];
                i = i - 1;
            }
        } else {
            while (i >= 0 && Points[i]->TPoint.mX > key->TPoint.mX) {
                Points[i + 1] = Points[i];
                i = i - 1;
            }
        }
        Points[i + 1] = key;
    }
}
