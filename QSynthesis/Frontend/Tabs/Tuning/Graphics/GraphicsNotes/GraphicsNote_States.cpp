#include "../GraphicsNote.h"

bool GraphicsNote::movable() const {
    return m_movable;
}

void GraphicsNote::setMovable(bool movable) {
    m_movable = movable;
}

bool GraphicsNote::display() const {
    return m_display;
}

void GraphicsNote::setDisplay(bool display) {
    m_display = display;
    m_screen->update();
}

bool GraphicsNote::block() const {
    return m_block;
}

void GraphicsNote::setBlock(bool block) {
    m_block = block;
    update();
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

bool GraphicsNote::highlighted() const {
    return m_highlighted;
}

void GraphicsNote::setHighlighted(bool highlighted) {
    bool old = m_highlighted;
    m_highlighted = highlighted;
    if (old != m_highlighted) {
        m_screen->update();
    }
}
