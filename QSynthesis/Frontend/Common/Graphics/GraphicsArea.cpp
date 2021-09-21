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
