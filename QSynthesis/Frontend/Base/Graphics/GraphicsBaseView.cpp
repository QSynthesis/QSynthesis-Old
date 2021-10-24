#include "GraphicsBaseView.h"
#include "GraphicsArea.h"

#include <QApplication>
#include <QGraphicsSceneMoveEvent>
#include <QGraphicsSceneResizeEvent>
#include <QScrollBar>

GraphicsBaseView::GraphicsBaseView(QWidget *parent) : QGraphicsView(parent) {
    init();
}

GraphicsBaseView::GraphicsBaseView(QGraphicsScene *scene,QWidget *parent)
    : QGraphicsView(scene, parent) {
    init();
}

GraphicsBaseView::~GraphicsBaseView() {
}

void GraphicsBaseView::init() {
    m_horizontalAnimation = new QPropertyAnimation(this);
    m_horizontalAnimation->setTargetObject(horizontalScrollBar());
    m_horizontalAnimation->setPropertyName("value");
    m_horizontalAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_horizontalAnimation->setDuration(125);

    m_verticalAnimation = new QPropertyAnimation(this);
    m_verticalAnimation->setTargetObject(verticalScrollBar());
    m_verticalAnimation->setPropertyName("value");
    m_horizontalAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_verticalAnimation->setDuration(125);

    setAcceptDrops(false);
}

QRectF GraphicsBaseView::GraphicsBaseView::viewportRect() const {
    QRect viewport_rect(0, 0, viewport()->width(), viewport()->height());
    QRectF visible_scene_rect = mapToScene(viewport_rect).boundingRect();
    return visible_scene_rect;
}

GraphicsArea *GraphicsBaseView::scene() const {
    return qobject_cast<GraphicsArea *>(QGraphicsView::scene());
}

void GraphicsBaseView::horizontalTween(int value) {
    if (value == m_horizontalAnimation->endValue() &&
        m_horizontalAnimation->state() == QPropertyAnimation::Running) {
        return;
    }
    m_horizontalAnimation->stop();
    m_horizontalAnimation->setStartValue(horizontalScrollBar()->value());
    m_horizontalAnimation->setEndValue(value);
    m_horizontalAnimation->start();
}

void GraphicsBaseView::verticalTween(int value) {
    if (value == m_verticalAnimation->endValue() &&
        m_verticalAnimation->state() == QPropertyAnimation::Running) {
        return;
    }
    m_verticalAnimation->stop();
    m_verticalAnimation->setStartValue(verticalScrollBar()->value());
    m_verticalAnimation->setEndValue(value);
    m_verticalAnimation->start();
}

void GraphicsBaseView::keyPressEvent(QKeyEvent *event) {
    return QGraphicsView::keyPressEvent(event);
}

void GraphicsBaseView::keyReleaseEvent(QKeyEvent *event) {
    return QGraphicsView::keyReleaseEvent(event);
}

void GraphicsBaseView::stopTween() {
    m_horizontalAnimation->stop();
    m_verticalAnimation->stop();
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
