#include "../GraphicsNote.h"

GraphicsNote *GraphicsNote::prev() const {
    return m_prev;
}

void GraphicsNote::setPrev(GraphicsNote *prev) {
    m_prev = prev;
    m_MPrev = prev;
}

GraphicsNote *GraphicsNote::next() const {
    return m_next;
}

void GraphicsNote::setNext(GraphicsNote *next) {
    m_next = next;
    m_MNext = next;
}

GraphicsNote *GraphicsNote::MNext() const {
    return m_MNext;
}

void GraphicsNote::setMNext(GraphicsNote *MNext) {
    m_MNext = MNext;
}

GraphicsNote *GraphicsNote::MPrev() const {
    return m_MPrev;
}

void GraphicsNote::setMPrev(GraphicsNote *MPrev) {
    m_MPrev = MPrev;
}

Mode2Handler *GraphicsNote::curves() {
    return m_curves;
}

EnvelopeHandler *GraphicsNote::envelope() {
    return m_envelope;
}

GraphicsLifter *GraphicsNote::lifter() {
    return m_lifter;
}

GraphicsLines *GraphicsNote::screen() const {
    return m_screen;
}
