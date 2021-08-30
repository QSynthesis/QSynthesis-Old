#include "../GraphicsLifter.h"

QColor GraphicsLifter::inactiveColor() const {
    return m_inactiveColor;
}

void GraphicsLifter::setInactiveColor(const QColor &inactiveColor) {
    m_inactiveColor = inactiveColor;
}

QColor GraphicsLifter::activeColor() const {
    return m_activeColor;
}

void GraphicsLifter::setActiveColor(const QColor &activeColor) {
    m_activeColor = activeColor;
}

QColor GraphicsLifter::inactiveHColor() const {
    return m_inactiveHColor;
}

void GraphicsLifter::setInactiveHColor(const QColor &inactiveHColor) {
    m_inactiveHColor = inactiveHColor;
}

QColor GraphicsLifter::activeHColor() const {
    return m_activeHColor;
}

void GraphicsLifter::setActiveHColor(const QColor &activeHColor) {
    m_activeHColor = activeHColor;
}

GraphicsLifter::Props GraphicsLifter::prop() const {
    return m_prop;
}

void GraphicsLifter::setProp(const Props &prop) {
    m_prop = prop;
    adjustHandle();
}

bool GraphicsLifter::active() const {
    return m_active;
}

void GraphicsLifter::setActive(bool active) {
    m_active = active;
    update();
}

bool GraphicsLifter::highlighted() const {
    return m_highlighted;
}

void GraphicsLifter::setHighlighted(bool highlighted) {
    m_highlighted = highlighted;
    update();
}
