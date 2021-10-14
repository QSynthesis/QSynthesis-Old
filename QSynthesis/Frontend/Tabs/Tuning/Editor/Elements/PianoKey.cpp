#include "PianoKey.h"

#include <QStyle>

PianoKey::PianoKey(Qs::PianoKeyColor color,QWidget *parent) : QToolButton(parent) {
    setColor(color);
}

PianoKey::~PianoKey() {
}

Qs::PianoKeyColor PianoKey::color() const {
    return m_color;
}

void PianoKey::setColor(const Qs::PianoKeyColor &color) {
    m_color = color;

    setProperty("color", m_color == Qs::Black ? "black" : "white");
    style()->polish(this);
}

int PianoKey::posFactor() const {
    return m_posFactor;
}

void PianoKey::setPosFactor(int posFactor) {
    m_posFactor = posFactor;
}

int PianoKey::heightFactor() const {
    return m_heightFactor;
}

void PianoKey::setHeightFactor(int heightFactor) {
    m_heightFactor = heightFactor;
}
