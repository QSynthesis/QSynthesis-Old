#include "GraphicsHandle.h"

#include <QCursor>

GraphicsHandle::GraphicsHandle(QGraphicsItem *parent) : GraphicsDragger(parent) {
    init();
}

GraphicsHandle::~GraphicsHandle() {
}

void GraphicsHandle::init() {
    m_element = GraphicsDragger::Specific;
}

QRectF GraphicsHandle::region() const {
    return m_region;
}

void GraphicsHandle::setRegion(const QRectF &region) {
    m_region = region;
}

void GraphicsHandle::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setCursor(QCursor(Qt::PointingHandCursor));
}

void GraphicsHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setCursor(QCursor(Qt::ArrowCursor));
}
