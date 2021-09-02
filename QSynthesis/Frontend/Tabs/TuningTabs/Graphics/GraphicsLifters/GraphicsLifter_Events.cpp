#include "../../Areas/Params/LiftersArea.h"
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
    if (event->buttons() == Qt::LeftButton) {
        afterMove(event->scenePos());
    }
}

void GraphicsLifter::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_editor->isPlaying()) {
        return;
    }
    afterRelease(event->scenePos());
}

void GraphicsLifter::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
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

void GraphicsLifter::afterRelease(QPointF pos) {
    if (m_move) {
        m_editor->endMove(this);

        qDragIn.stopDrag(this);
        qDragIn.endInvolve(this);
        qDragIn.removeAllT();
    }
}
