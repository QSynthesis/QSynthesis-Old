#include "../GraphicsLifter.h"

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
