#include "../../Params/Areas/LiftersArea.h"
#include "../../TuningGroup.h"
#include "../GraphicsLifter.h"
#include "../GraphicsNote.h"

void GraphicsLifter::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        afterPress();
    }
}

void GraphicsLifter::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_editor->isPlaying()) {
        return;
    }
    if (event->buttons() & Qt::LeftButton) {
        afterMove(event->scenePos());
    }
}

void GraphicsLifter::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_editor->isPlaying()) {
        return;
    }
    if (event->button() == Qt::LeftButton) {
        afterRelease();
    }
}

void GraphicsLifter::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
}

void GraphicsLifter::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    GraphicsLineHandle::hoverLeaveEvent(event);
    if (m_move) {
        afterRelease();
    }
}

void GraphicsLifter::afterPress() {
    m_note->afterPress();
}

void GraphicsLifter::afterMove(QPointF pos) {
    if (!m_move) {
        m_editor->prepareMove(this);

        qDragIn.startDrag(this, pos);
        qDragIn.startInvolve(this, pos);
    }

    if (m_move) {
        qDragIn.duringDrag(this, pos);
        qDragIn.duringInvolve(this, pos);

        m_editor->refreshMove(this);
    }
}

void GraphicsLifter::afterRelease() {
    if (m_move) {
        m_editor->endMove(this);

        qDragIn.stopDrag(this);
        qDragIn.endInvolve(this);
        qDragIn.removeAllT();
    }
}
