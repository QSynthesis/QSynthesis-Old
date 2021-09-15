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

QColor GraphicsNote::lyricColor() const {
    return m_lyricColor;
}

void GraphicsNote::setLyricColor(const QColor &lyricColor) {
    m_lyricColor = lyricColor;
    update();
}

QColor GraphicsNote::unlistedLineColor() const {
    return m_unlistedLineColor;
}

void GraphicsNote::setUnlistedLineColor(const QColor &unlistedLineColor) {
    m_unlistedLineColor = unlistedLineColor;
}

QColor GraphicsNote::unlistedFillColor() const {
    return m_unlistedFillColor;
}

void GraphicsNote::setUnlistedFillColor(const QColor &unlistedFillColor) {
    m_unlistedFillColor = unlistedFillColor;
}

QColor GraphicsNote::listedLineColor() const {
    return m_listedLineColor;
}

void GraphicsNote::setListedLineColor(const QColor &listedLineColor) {
    m_listedLineColor = listedLineColor;
}

QColor GraphicsNote::listedFillColor() const {
    return m_listedFillColor;
}

void GraphicsNote::setListedFillColor(const QColor &listedFillColor) {
    m_listedFillColor = listedFillColor;
}

QColor GraphicsNote::restLineColor() const {
    return m_restLineColor;
}

void GraphicsNote::setRestLineColor(const QColor &restLineColor) {
    m_restLineColor = restLineColor;
}

QColor GraphicsNote::restFillColor() const {
    return m_restFillColor;
}

void GraphicsNote::setRestFillColor(const QColor &restFillColor) {
    m_restFillColor = restFillColor;
}
