#include "GraphicsArea.h"
#include "mainwindow.h"

GraphicsArea::GraphicsArea(QObject *parent) : QGraphicsScene(parent) {
    // setItemIndexMethod(QGraphicsScene::ItemIndexMethod::NoIndex);
}

GraphicsArea::~GraphicsArea() {
}

QPointF GraphicsArea::mousePos(int index) const {
    const QList<QGraphicsView *> views = this->views();
    if (index >= views.size()) {
        return QPointF();
    }
    QGraphicsView *view = views.at(index);
    return view->mapToScene(view->mapFromGlobal(QCursor::pos()));
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
}

void GraphicsArea::resizeEvent(QGraphicsSceneResizeEvent *event) {
}

void GraphicsArea::enterEvent(QEnterEvent *event) {
}

void GraphicsArea::leaveEvent(QEvent *event) {
}

void GraphicsArea::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
    qRoot->handleGraphicsSceneEvents(event);
}

void GraphicsArea::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
    qRoot->handleGraphicsSceneEvents(event);
}

void GraphicsArea::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {
    qRoot->handleGraphicsSceneEvents(event);
}

void GraphicsArea::dropEvent(QGraphicsSceneDragDropEvent *event) {
    qRoot->handleGraphicsSceneEvents(event);
}
