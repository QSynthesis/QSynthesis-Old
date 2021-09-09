#include "GraphicsArea.h"
#include "mainwindow.h"

GraphicsArea::GraphicsArea(QObject *parent) : QGraphicsScene(parent) {
}

GraphicsArea::~GraphicsArea() {
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
