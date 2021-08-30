#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../ScopeHandler.h"

void ScopeHandler::prepareMove(GraphicsPoint *p) {
    m_moving = true;

    // Put all notes to involved list
    for (int i = 0; i < Points.size(); ++i) {
        if (!Points.at(i)->isSelected()) {
            qDragIn.addOneT(Points.at(i));
        }
    }
}

void ScopeHandler::refreshMove(GraphicsPoint *p) {
    // updateYRank();
}

void ScopeHandler::endMove(GraphicsPoint *p) {
    GraphicsPoint *c;

    for (int i = 0; i < Points.size(); ++i) {
        c = Points[i];
        if (!c) {
            continue;
        }

        // Skip saving if position doesn't change
        if (c->staticPos() == c->pos() && c->staticSpecialPos() == c->specialPos()) {
            continue;
        }

        double tx = convertPosToValueX(c->x());
        double ty = convertPosToValueY(c->y());

        // Correct the potential error
        // Rule: a point's tx must be between the tx of its left and right
        if (i > 0 && tx < Points[i - 1]->generalX()) {
            tx = Points[i - 1]->generalX();
        } else if (i < Points.size() - 1 && tx > Points[i + 1]->generalX()) {
            tx = Points[i + 1]->generalX();
        }

        if (c->isMoving()) {
            c->TPoint.mX = tx;
            c->TPoint.mY = ty;
        } else if (c->staticSpecialPos() != c->specialPos()) {
            c->TPoint.mY = ty;
        }
    }

    m_moving = false;
}
