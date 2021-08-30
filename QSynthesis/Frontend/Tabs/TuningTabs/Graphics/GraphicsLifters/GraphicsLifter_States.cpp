#include "../../Areas/Params/LiftersArea.h"
#include "../GraphicsLifter.h"
#include "../GraphicsNote.h"

void GraphicsLifter::adjustSize() {
    m_geometry.setRect(-Radius, -Radius, m_note->width() + 2 * Radius, m_editor->standardHeight());
    setSize(m_note->width(), 2 * Radius);

    adjustHandle();
}

void GraphicsLifter::adjustHandle() {
    setXLocation(m_note->x());
    setRegion(QRectF(x(), Radius, width(), m_editor->standardHeight() - 2 * Radius));
    setValue(1 - convertPropToRatio(m_prop, m_values[m_prop]));

    update();
}
