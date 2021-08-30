#include "../../Areas/Editor/NotesArea.h"
#include "../GraphicsLifter.h"
#include "../GraphicsNote.h"

void GraphicsNote::setGeometry(QRectF geometry) {
    setLocation(geometry.topLeft());
    setSize(geometry.size());
    update();
}

void GraphicsNote::setGeometry(double x, double y, double w, double h) {
    setGeometry(QRectF(x, y, w, h));
}

QRectF GraphicsNote::geometry() const {
    return QRectF(pos().x(), pos().y(), width(), height());
}

void GraphicsNote::setLocation(QPointF pos) {
    GraphicsDragger::setLocation(pos);
    m_screen->updateLocation();
}

void GraphicsNote::setSize(QSizeF size) {
    GraphicsDragger::setSize(size);
    m_screen->updateSize();
}

void GraphicsNote::adjustSize(bool involve) {
    // Update Note
    QRectF geometry = m_editor->convertValueToGeometry(m_tick, Note.noteNum, Note.length);
    setGeometry(geometry);

    // Update Curves And Envelope
    if (involve) {
        adjustComponents();
    }

    update();
}

void GraphicsNote::adjustComponents() {
    adjustCurves();
    adjustEnvelope();
    adjustLifter();
}

void GraphicsNote::adjustCurves() {
    m_curves->adjustGeometry();
    m_curves->adjustPoints();
}

void GraphicsNote::adjustEnvelope() {
    m_envelope->adjustGeometry();
    m_envelope->adjustPoints();
}

void GraphicsNote::adjustLifter() {
    m_lifter->adjustSize();
}
