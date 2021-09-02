#include "../../Areas/Editor/NotesArea.h"
#include "../../Handlers/Mode2Handler.h"
#include "../../TuningGroup.h"
#include "../GraphicsPoint.h"
#include "mainwindow.h"

void GraphicsPoint::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDragIn.filter(m_element); // Deselect all draggers other than point

    afterPress();
    if (event->button() == Qt::RightButton) {
        if (!m_editor->isPlaying() && !(m_move || m_drawing)) {
            m_editor->changePointFromCursor(this);
        }
    }
}

void GraphicsPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (m_editor->isPlaying()) {
        return;
    }
    // First Move
    if (event->buttons() & Qt::LeftButton) {
        afterMove(event->scenePos());
    }
}

void GraphicsPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_editor->isPlaying()) {
        return;
    }
    if (event->button() == Qt::LeftButton) {
        afterRelease();
    }
}

void GraphicsPoint::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (m_editor->isPlaying()) {
        return;
    }
    if (event->button() == Qt::LeftButton) {
        qDragIn.removeAll();
        m_editor->removePointFromCursor(this);
    } else if (event->button() == Qt::RightButton) {
        mousePressEvent(event);
    }
}

void GraphicsPoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setHovered(true);
}

void GraphicsPoint::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
}

void GraphicsPoint::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    setHovered(false);

    if (m_move || m_drawing) {
        afterRelease();
    }
}

void GraphicsPoint::afterPress() {
    Qt::KeyboardModifiers c = QApplication::keyboardModifiers();
    bool selected = isSelected();

    // Shift
    if (c == MainWindow::config.notes.continuousSelect) {
        qDragIn.addOne(this);
        m_scope->selectContinuously();
        return;
    }

    // Ctrl
    if (c == MainWindow::config.notes.reserveSelect) {
        // Add or Remove
        if (selected) {
            qDragIn.removeOne(this);
        } else {
            qDragIn.addOne(this);
        }
    } else {
        if (!selected) {
            qDragIn.removeAll();
            qDragIn.addOne(this);
        }
    }
}

void GraphicsPoint::afterMove(QPointF pos) {
    if (!m_move) {
        if (!isSelected()) {
            qDragIn.addOne(this);
        }
        m_editor->prepareMove(this);

        qDragIn.startDrag(this, pos);
        qDragIn.startInvolve(this, pos);
    }

    if (m_move) {
        qDragIn.duringDrag(this, pos);
        qDragIn.duringInvolve(this, pos);

        m_editor->refreshMove(this, pos);
    }
}

void GraphicsPoint::afterRelease() {
    if (m_move || m_drawing) {
        // Release the mouse
        if (m_drawing) {
            // Born
            qDebug() << "Release mouse from SimplePoint";
            this->ungrabMouse();
            setDrawing(false);
            m_editor->afterDraw(this);
        } else {
            // Move
            m_editor->endMove(this);
        }

        qDragIn.stopDrag(this);
        qDragIn.endInvolve(this);
        qDragIn.removeAllT(); // Remove all involved notes
    } else {
        m_editor->statusCall();
    }
}

void GraphicsPoint::autoRelease() {
    if (m_move || m_drawing) {
        // Release the mouse
        if (m_drawing) {
            // Born
            qDebug() << "Release mouse from SimplePoint";
            this->ungrabMouse();
            setDrawing(false);
            m_editor->afterDraw(this);
        } else {
            // Move
            m_editor->endMove(this);
        }

        qDragIn.stopDrag(this);
        qDragIn.endInvolve(this);
        qDragIn.removeAllT(); // Remove all involved notes
    }
}
