#include "../../Areas/Editor/NotesArea.h"
#include "../../Handlers/Mode2Handler.h"
#include "../../TuningGroup.h"
#include "../GraphicsPoint.h"

QPointF GraphicsPoint::limitArea(QPointF origin) {
    Qt::KeyboardModifiers c = QApplication::keyboardModifiers();

    bool cs = c == (Qt::ShiftModifier | Qt::ControlModifier);
    bool c1 = c == Qt::ControlModifier;
    bool s1 = c == Qt::ShiftModifier;

    int h = m_editor->ptrs()->currentHeight;
    double h1 = double(h) / 2;

    double unit_y = int(origin.y() / h1 + 0.5) * h1 - h1 + double(h) / 2;

    if (m_move && (cs || s1)) {
        GraphicsPoint *np = m_scope->getNearestPoint(this, origin.x());
        if (np) {
            origin.setX(np->x());
        }
    }
    // Default limit x
    QRectF activeScope = m_scope->activeScope();
    if (origin.x() < activeScope.left()) {
        origin.setX(activeScope.left());
    } else if (origin.x() > activeScope.right()) {
        origin.setX(activeScope.right());
    }

    if (m_specialPos == Qs::Middle) {
        // Free if middle or prev note is rest
        if (m_move && (cs || c1)) {
            origin.setY(unit_y);
        }
    } else if (m_specialPos == Qs::Leftmost && m_scope->prevNote()) {
        if (m_scope->prevNote()->isRest()) {
            if (m_move && (cs || c1)) {
                origin.setY(unit_y);
            }
        } else {
            origin.setY(m_scope->prevNote()->headPos().y());
        }
    } else {
        origin.setY(m_scope->note()->headPos().y());
    }

    // Default limit y
    if (origin.y() < activeScope.top()) {
        origin.setY(activeScope.top());
    } else if (origin.y() > activeScope.bottom()) {
        origin.setY(activeScope.bottom());
    }

    return origin;
}

QPointF GraphicsPoint::limitAreaT(QPointF origin) {
    return limitArea(origin);
}

void GraphicsPoint::involvePress(QPointF pos) {
    m_windowSpecialPos = m_specialPos;
    GraphicsDragger::involvePress(pos);
}

void GraphicsPoint::linkPress(QPointF pos) {
    m_windowSpecialPos = m_specialPos;
    GraphicsDragger::linkPress(pos);
}
