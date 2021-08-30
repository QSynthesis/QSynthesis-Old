#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../ScopeHandler.h"

void ScopeHandler::update() {
    m_note->update();
    screen()->update();
}

void ScopeHandler::setPointsVisible(bool value) {
    for (int i = 0; i < Points.size(); ++i) {
        Points.at(i)->setVisible(value);
    }
}

QPoint ScopeHandler::selectContinuously(bool selectAll) {
    int min, max;

    if (!selectAll) {
        QPoint region = continuousSelection();
        min = region.x();
        max = region.y();
    } else {
        min = 0;
        max = Points.size() - 1;
    }
    if (min >= 0) {
        for (int i = min; i <= max; ++i) {
            if (!Points[i]->isSelected()) {
                qDragIn.addOne(Points[i]);
            }
        }
    }

    return QPoint(min, max);
}

void ScopeHandler::setSolid(bool solid) {
    m_solid = solid;
    setPointsVisible(solid);
    update();
}

void ScopeHandler::adjustGeometry() {
    update();
}

void ScopeHandler::adjustPoints() {
    GraphicsPoint *p;
    int i;

    for (i = 0; i < Points.size(); ++i) {
        p = Points[i];

        QControlPoint tp = p->TPoint;
        double posX = convertValueToPosX(tp.mX);
        double posY = convertValueToPosY(tp.mY);

        p->setLocation(posX, posY);
    }

    // Limit leftmost and rightmost
    limitAllPoints();
}

void ScopeHandler::limitAllPoints() {
    int i;
    for (i = 0; i < Points.size(); ++i) {
        Points[i]->externLimitArea();
    }
}

bool ScopeHandler::updateXRank() {
    if (Points.size() < 2) {
        return false;
    }

    insertSort();

    bool flag = Points.front()->setSpecialPos(Qs::Leftmost); // Leftmost Point
    flag |= Points.back()->setSpecialPos(Qs::Rightmost);     // Rightmost Point
    for (int j = 1; j < Points.size() - 1; ++j) {
        flag |= Points[j]->setSpecialPos(Qs::Middle); // Middle Point
    }

    return flag;
}
