#include "LiftersScrollArea.h"

#include <QDebug>
#include <QEvent>
#include <QScrollBar>

LiftersScrollArea::LiftersScrollArea(QWidget *parent) : GraphicsLinearView(Qt::Horizontal, parent) {
    setRenderHint(QPainter::Antialiasing);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    horizontalScrollBar()->setEnabled(false);

    installEventFilter(this);
}

LiftersScrollArea::~LiftersScrollArea() {
}

QRectF LiftersScrollArea::viewportRect() const {
    QRect viewport_rect(0, 0, viewport()->width(), viewport()->height());
    QRectF visible_scene_rect = mapToScene(viewport_rect).boundingRect();
    return visible_scene_rect;
}

bool LiftersScrollArea::eventFilter(QObject *obj, QEvent *event) {
    if (obj == this && event->type() == QEvent::KeyPress) {
        return true;
    }
    return QGraphicsView::eventFilter(obj, event);
}
