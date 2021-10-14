#include "GraphicsArea.h"
#include "Graphics/GraphicsBaseView.h"
#include "mainwindow.h"

GraphicsArea::GraphicsArea(GraphicsBaseView *view) : QGraphicsScene(view), m_view(view) {
    // setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);
}

GraphicsArea::~GraphicsArea() {
}

GraphicsBaseView *GraphicsArea::view() const {
    return m_view;
}

QPointF GraphicsArea::mousePos() const {
    QGraphicsView *view = this->view();
    return view->mapToScene(view->mapFromGlobal(QCursor::pos()));
}

void GraphicsArea::setVisionFitToItem(QGraphicsItem *item, Qt::AnchorPoint side, bool tween) {
    QRectF rect = item->boundingRect();

    double x1 = item->x() + rect.x();
    double x2 = x1 + rect.width() / 2;
    double x3 = x1 + rect.width();
    double y1 = item->y() + rect.y();
    double y2 = y1 + rect.height() / 2;
    double y3 = y1 + rect.height();

    double pos;
    switch (side) {
    case Qt::AnchorLeft:
        pos = x1;
        break;
    case Qt::AnchorHorizontalCenter:
        pos = x2;
        break;
    case Qt::AnchorRight:
        pos = x3;
        break;
    case Qt::AnchorTop:
        pos = y1;
        break;
    case Qt::AnchorVerticalCenter:
        pos = y2;
        break;
    default:
        pos = y3;
        break;
    }
    setVisionFitToPos(pos, side, tween);
}

void GraphicsArea::setVisionFitToItem(QGraphicsItem *item, Qt::Orientations orients, bool tween) {
    GraphicsBaseView *view = this->view();
    if (!view) {
        return;
    }
    QRectF viewportRect = view->viewportRect();

    QRectF rect = item->boundingRect();

    double x1 = item->x() + rect.x();
    double x3 = x1 + rect.width();
    double y1 = item->y() + rect.y();
    double y3 = y1 + rect.height();

    if (orients & Qt::Horizontal) {
        if (x1 < viewportRect.left()) {
            setVisionFitToPos(x1, Qt::AnchorLeft, tween);
        } else if (x3 > viewportRect.right()) {
            setVisionFitToPos(x3, Qt::AnchorRight, tween);
        }
    }
    if (orients & Qt::Vertical) {
        if (y1 < viewportRect.top()) {
            setVisionFitToPos(y1, Qt::AnchorTop, tween);
        } else if (y3 > viewportRect.bottom()) {
            setVisionFitToPos(y3, Qt::AnchorBottom, tween);
        }
    }
}

void GraphicsArea::setVisionFitToPos(double pos, Qt::AnchorPoint side, bool tween) {
    GraphicsBaseView *view = this->view();
    if (!view) {
        return;
    }
    QRectF viewportRect = view->viewportRect();

    int toValue = 0;
    Qt::Orientation orient = Qt::Horizontal;

    switch (side) {
    case Qt::AnchorLeft:
        toValue = pos;
        break;
    case Qt::AnchorHorizontalCenter:
        toValue = pos - viewportRect.width() / 2;
        break;
    case Qt::AnchorRight:
        toValue = pos - viewportRect.width();
        break;
    case Qt::AnchorTop:
        orient = Qt::Vertical;
        toValue = pos;
        break;
    case Qt::AnchorVerticalCenter:
        orient = Qt::Vertical;
        toValue = pos - viewportRect.height() / 2;
        break;
    default:
        orient = Qt::Vertical;
        toValue = pos - viewportRect.height();
        break;
    }
    if (tween) {
        (orient == Qt::Horizontal) ? view->horizontalTween(toValue) : view->verticalTween(toValue);
    } else {
        (orient == Qt::Horizontal) ? view->horizontalScrollBar()->setValue(toValue)
                                   : view->verticalScrollBar()->setValue(toValue);
    }
}

bool GraphicsArea::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::GraphicsSceneMove:
        moveEvent(static_cast<QGraphicsSceneMoveEvent *>(event));
        return true;
        break;
    case QEvent::GraphicsSceneResize:
        resizeEvent(static_cast<QGraphicsSceneResizeEvent *>(event));
        return true;
        break;

    case QEvent::Enter:
        enterEvent(static_cast<QEnterEvent *>(event));
        return true;
        break;
    case QEvent::Leave:
        leaveEvent(event);
        return true;
        break;
    default:
        break;
    }
    return QGraphicsScene::event(event);
}

void GraphicsArea::moveEvent(QGraphicsSceneMoveEvent *event) {
    Q_UNUSED(event)
}

void GraphicsArea::resizeEvent(QGraphicsSceneResizeEvent *event) {
    Q_UNUSED(event)
}

void GraphicsArea::enterEvent(QEnterEvent *event) {
    Q_UNUSED(event)
}

void GraphicsArea::leaveEvent(QEvent *event) {
    Q_UNUSED(event)
}

void GraphicsArea::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    QDragEnterEvent e(event->pos().toPoint(), event->possibleActions(), event->mimeData(),
                      event->buttons(), event->modifiers());
    QApplication::sendEvent(qRoot, &e);
}

void GraphicsArea::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    QDragMoveEvent e(event->pos().toPoint(), event->possibleActions(), event->mimeData(),
                     event->buttons(), event->modifiers());
    QApplication::sendEvent(qRoot, &e);
}

void GraphicsArea::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    QDragLeaveEvent e;
    QApplication::sendEvent(qRoot, &e);
}

void GraphicsArea::dropEvent(QGraphicsSceneDragDropEvent *event) {
    QDropEvent e(event->pos().toPoint(), event->possibleActions(), event->mimeData(),
                 event->buttons(), event->modifiers());
    QApplication::sendEvent(qRoot, &e);
}
