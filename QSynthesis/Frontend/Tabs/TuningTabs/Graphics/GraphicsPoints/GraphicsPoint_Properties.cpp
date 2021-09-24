#include "../../Areas/Editor/NotesArea.h"
#include "../../Handlers/Mode2Handler.h"
#include "../../TuningGroup.h"
#include "../GraphicsPoint.h"

Qs::SpecialPos GraphicsPoint::specialPos() const {
    return m_specialPos;
}

bool GraphicsPoint::setSpecialPos(Qs::SpecialPos specialPos) {
    Qs::SpecialPos org = m_specialPos;
    m_specialPos = specialPos;

    if (m_specialPos != org) {
        return true;
    }
    return false;
}

double GraphicsPoint::generalX() const {
    if (m_moving) {
        return m_scope->convertPosToValueX(x());
    } else {
        return TPoint.mX;
    }
}

double GraphicsPoint::generalY() const {
    if (m_moving) {
        return m_scope->convertPosToValueY(y());
    } else {
        return TPoint.mY;
    }
}

double GraphicsPoint::absoulteY() const {
    double result = 0;
    switch (m_specialPos) {
    case Qs::Middle:
        result = TPoint.mY;
        break;
    case Qs::Leftmost:
        if (m_scope->prevNote()) {
            result = (m_scope->prevNote()->Note.noteNum - m_scope->note()->Note.noteNum) * 10;
        }
        break;
    default:
        break;
    }
    return result;
}

ScopeHandler *GraphicsPoint::scope() const {
    return m_scope;
}

GraphicsNote *GraphicsPoint::note() const {
    return m_scope->note();
}

void GraphicsPoint::setHovered(bool hovered) {
    m_hovered = hovered;
    update();
    m_scope->update();
}

bool GraphicsPoint::hovered() const {
    return m_hovered;
}

double GraphicsPoint::radius() const {
    return m_radius;
}

bool GraphicsPoint::drawing() const {
    return m_drawing;
}

void GraphicsPoint::setDrawing(bool drawing) {
    m_drawing = drawing;
}

Qs::SpecialPos GraphicsPoint::staticSpecialPos() const {
    return m_windowSpecialPos;
}
