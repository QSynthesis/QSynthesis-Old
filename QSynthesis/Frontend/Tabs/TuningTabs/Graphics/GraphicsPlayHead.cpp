#include "GraphicsPlayHead.h"

GraphicsPlayHead::GraphicsPlayHead(QGraphicsItem *parent) : QGraphicsRectItem(parent) {
}

GraphicsPlayHead::~GraphicsPlayHead() {
}

QPainterPath GraphicsPlayHead::shape() const {
    return QPainterPath();
}
