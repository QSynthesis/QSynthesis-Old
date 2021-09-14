#include "GraphicsPlaneHandle.h"

GraphicsPlaneHandle::GraphicsPlaneHandle(QGraphicsItem *parent) : GraphicsHandle(parent) {
}

GraphicsPlaneHandle::~GraphicsPlaneHandle() {
}

void GraphicsPlaneHandle::init() {
}

void GraphicsPlaneHandle::setValue(QPointF values) {
    setValueX(values.x());
    setValueY(values.y());
}

void GraphicsPlaneHandle::setValueX(double value) {
    double toX = 0;
    toX = value * (m_region.right() - m_region.left()) + m_region.left();
    setLocation(limitArea(MorePoint(toX, y())));
}

void GraphicsPlaneHandle::setValueY(double value) {
    double toY = 0;
    toY = value * (m_region.bottom() - m_region.top()) + m_region.top();
    setLocation(limitArea(MorePoint(x(), toY)));
}

QPointF GraphicsPlaneHandle::value() const {
    return QPointF(valueX(), valueY());
}

double GraphicsPlaneHandle::valueX() const {
    return (x() - m_region.left()) / (m_region.right() - m_region.left());
}

double GraphicsPlaneHandle::valueY() const {
    return (y() - m_region.top()) / (m_region.bottom() - m_region.top());
}
