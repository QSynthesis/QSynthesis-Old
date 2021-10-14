#include "GraphicsLinearView.h"
#include "GraphicsArea.h"

GraphicsLinearView::GraphicsLinearView(Qt::Orientation orient,QWidget *parent)
    : GraphicsBaseView(parent), m_orient(orient) {
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
    GraphicsArea *s = scene();
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
    GraphicsBaseView::resizeEvent(event);
}
