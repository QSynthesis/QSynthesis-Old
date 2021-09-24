#include "GraphicsBaseView.h"
#include "GraphicsArea.h"

#include <QApplication>
#include <QGraphicsSceneMoveEvent>
#include <QGraphicsSceneResizeEvent>

GraphicsBaseView::GraphicsBaseView(QWidget *parent) : QGraphicsView(parent) {
}

GraphicsBaseView::GraphicsBaseView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {
}

GraphicsBaseView::~GraphicsBaseView() {
}

QRectF GraphicsBaseView::GraphicsBaseView::viewportRect() const {
    QRect viewport_rect(0, 0, viewport()->width(), viewport()->height());
    QRectF visible_scene_rect = mapToScene(viewport_rect).boundingRect();
    return visible_scene_rect;
}

GraphicsArea *GraphicsBaseView::scene() const {
    return qobject_cast<GraphicsArea *>(QGraphicsView::scene());
}

bool GraphicsBaseView::viewportEvent(QEvent *event) {
    QRectF rect = viewportRect();
    GraphicsArea *scene = this->scene();

    if (m_orgViewportRect.topLeft() != rect.topLeft()) {
        QGraphicsSceneMoveEvent event;
        event.setOldPos(m_orgViewportRect.topLeft());
        event.setNewPos(rect.topLeft());
        event.setWidget(this);
        if (scene) {
            QApplication::sendEvent(scene, &event);
        }
    }
    if (m_orgViewportRect.size() != rect.size()) {
        QGraphicsSceneResizeEvent event;
        event.setOldSize(m_orgViewportRect.size());
        event.setNewSize(rect.size());
        event.setWidget(this);
        if (scene) {
            QApplication::sendEvent(scene, &event);
        }
    }
    m_orgViewportRect = rect;
    return QGraphicsView::viewportEvent(event);
}
