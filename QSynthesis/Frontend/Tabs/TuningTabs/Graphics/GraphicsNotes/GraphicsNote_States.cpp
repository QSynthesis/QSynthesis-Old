#include "../GraphicsNote.h"

bool GraphicsNote::movable() const {
    return m_movable;
}

void GraphicsNote::setMovable(bool movable) {
    m_movable = movable;
}

bool GraphicsNote::stretch() const {
    return m_stretch;
}

void GraphicsNote::setStretch(bool stretch) {
    m_stretch = stretch;
    if (stretch) {
        setCursor(Qt::SizeHorCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }
}

bool GraphicsNote::drawing() const {
    return m_drawing;
}

void GraphicsNote::setDrawing(bool drawing) {
    m_drawing = drawing;
}
