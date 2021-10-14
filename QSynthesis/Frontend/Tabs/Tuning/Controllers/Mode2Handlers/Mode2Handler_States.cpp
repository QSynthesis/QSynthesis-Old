#include "../../Editor/Areas/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../Mode2Handler.h"

void Mode2Handler::setSolid(bool solid) {
    if (!solid && hasVBREditor()) {
        removeVibrtoEditor();
    }
    ScopeHandler::setSolid(solid);
}

void Mode2Handler::adjustGeometry() {
    double startX = m_note->MPrev() ? m_note->MPrev()->x() : m_note->x();
    double prevWidth = m_note->MPrev() ? m_note->MPrev()->width() : 0;
    double nextWidth = m_note->MNext() ? m_note->MNext()->width() : 0;

    m_geometry =
        QRectF(startX, 0, prevWidth + m_note->width() + nextWidth, m_editor->sceneRect().height());

    QRectF rect = m_geometry;
    rect.setWidth((prevNote() ? prevNote()->width() : 0) + note()->width());
    m_activeScope = rect;

    update();
}

void Mode2Handler::adjustPoints() {
    ScopeHandler::adjustPoints();
    adjustVibrato();
}
