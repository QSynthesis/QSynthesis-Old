#include "GraphicsPlayHead.h"

GraphicsPlayHead::GraphicsPlayHead(QGraphicsItem *parent) : QGraphicsRectItem(parent) {
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
