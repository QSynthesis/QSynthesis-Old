#include "../../Editor/Areas/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../Mode2Handler.h"

QRectF Mode2Handler::visionScope() const {
    return m_geometry;
}

double Mode2Handler::convertPosToValueX(double x) const {
    double noteX = m_note->x();
    double tick = double(x - noteX) * 480 / m_editor->ptrs()->currentWidth;
    double time = m_note->convertTickToTime(tick);
    return time;
}

double Mode2Handler::convertPosToValueY(double y) const {
    double noteY = m_note->headPos().y();
    double cent = -1 * double(y - noteY) * 10 / m_editor->ptrs()->currentHeight;
    return cent;
}

double Mode2Handler::convertValueToPosX(double x) const {
    double noteX = m_note->x();
    double tick = m_note->convertTimeToTick(x);
    double toX = noteX + tick / 480 * m_editor->ptrs()->currentWidth;
    return toX;
}

double Mode2Handler::convertValueToPosY(double y) const {
    double noteY = m_note->headPos().y();
    double toY = noteY - y / 10 * m_editor->ptrs()->currentHeight;
    return toY;
}
