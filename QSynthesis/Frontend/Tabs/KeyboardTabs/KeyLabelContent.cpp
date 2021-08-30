#include "KeyLabelContent.h"

KeyLabelContent::KeyLabelContent(QString content, QWidget *parent) : QLabel(content, parent) {
    init();
}

KeyLabelContent::KeyLabelContent(QWidget *parent) : QLabel(parent) {
    init();
}

void KeyLabelContent::setHovered(bool value) {
    m_hovered = value;
    emit hoveredChanged();
}

bool KeyLabelContent::hovered() const {
    return m_hovered;
}

void KeyLabelContent::init() {
    m_hovered = false;
}
