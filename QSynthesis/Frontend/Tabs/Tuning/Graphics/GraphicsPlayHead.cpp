#include "GraphicsPlayHead.h"

GraphicsPlayHead::GraphicsPlayHead(QGraphicsItem *parent) : QGraphicsRectItem(parent) {
    m_playing = false;
    m_alwaysShow = false;
}

GraphicsPlayHead::~GraphicsPlayHead() {
}

double GraphicsPlayHead::left() const {
    return x() + rect().x();
}

double GraphicsPlayHead::right() const {
    QRectF rect = this->rect();
    return x() + rect.x() + rect.width();
}

QPainterPath GraphicsPlayHead::shape() const {
    return QPainterPath();
}

bool GraphicsPlayHead::alwaysShow() const {
    return m_alwaysShow;
}

void GraphicsPlayHead::setAlwaysShow(bool alwaysShow) {
    m_alwaysShow = alwaysShow;
    if (!m_alwaysShow) {
        setVisible(m_playing);
    } else if (!isVisible()) {
        setVisible(true);
    }
}

bool GraphicsPlayHead::playing() const {
    return m_playing;
}

void GraphicsPlayHead::setPlaying(bool playing) {
    m_playing = playing;
    if (!m_alwaysShow) {
        setVisible(m_playing);
    } else if (!isVisible()) {
        setVisible(true);
    }
}
