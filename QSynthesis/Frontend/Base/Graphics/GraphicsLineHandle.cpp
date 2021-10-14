#include "GraphicsLineHandle.h"

GraphicsLineHandle::GraphicsLineHandle(Qt::Orientation orient, QGraphicsItem *parent)
    : GraphicsHandle(parent), m_orient(orient) {
    init();
}

GraphicsLineHandle::~GraphicsLineHandle() {
}

void GraphicsLineHandle::init() {
}

Qt::Orientation GraphicsLineHandle::orient() const {
    return m_orient;
}

double GraphicsLineHandle::value() const {
    double result;

    if (m_orient == Qt::Horizontal) {
        result = (x() - m_region.left()) / (m_region.right() - m_region.left());
    } else {
        result = (y() - m_region.top()) / (m_region.bottom() - m_region.top());
    }

    return result;
}

void GraphicsLineHandle::setValue(double value) {
    double toW = 0;

    if (m_orient == Qt::Horizontal) {
        toW = value * (m_region.right() - m_region.left()) + m_region.left();
        setLocation(limitArea(MorePoint(toW, y())));
    } else {
        toW = value * (m_region.bottom() - m_region.top()) + m_region.top();
        setLocation(limitArea(MorePoint(x(), toW)));
    }
}

double GraphicsLineHandle::position() const {
    if (m_orient == Qt::Horizontal) {
        return x();
    } else {
        return y();
    }
}

void GraphicsLineHandle::setPosition(double position) {
    if (m_orient == Qt::Horizontal) {
        setLocation(limitArea(MorePoint(position, y())));
    } else {
        setLocation(limitArea(MorePoint(x(), position)));
    }
}
