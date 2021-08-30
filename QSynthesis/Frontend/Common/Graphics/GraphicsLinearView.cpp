#include "GraphicsLinearView.h"

GraphicsLinearView::GraphicsLinearView(Qt::Orientation orient, QWidget *parent)
    : QGraphicsView(parent), m_orient(orient) {
    if (orient == Qt::Horizontal) {
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        verticalScrollBar()->setEnabled(false);
    } else {
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        horizontalScrollBar()->setEnabled(false);
    }
}

GraphicsLinearView::~GraphicsLinearView() {
}

Qt::Orientation GraphicsLinearView::orient() const {
    return m_orient;
}

void GraphicsLinearView::resizeEvent(QResizeEvent *event) {
    QGraphicsScene *s = scene();
    if (!s) {
        return;
    }
    switch (m_orient) {
    case Qt::Horizontal:
        if (s->height() != viewport()->height()) {
            s->setSceneRect(QRectF(0, 0, s->width(), viewport()->height()));
        }
        break;
    case Qt::Vertical:
        if (s->width() != viewport()->width()) {
            s->setSceneRect(QRectF(0, 0, viewport()->width(), s->height()));
        }
    }
    QGraphicsView::resizeEvent(event);
}
