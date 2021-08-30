#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../ScopeHandler.h"

void ScopeHandler::fromNotePoints() {
}

void ScopeHandler::toNotePoints() {
}

void ScopeHandler::removeAllPoints() {
    GraphicsPoint *p;
    for (int i = 0; i < Points.size(); ++i) {
        p = Points[i];
        removePointCore(p);
    }
    Points.clear();
}

GraphicsPoint *ScopeHandler::insertPoint(QPointF pos) {
    GraphicsPoint *p, *q;

    if (Points.isEmpty()) {
        return nullptr;
    }

    // new point
    p = createPointCore();
    p->setLocation(pos);

    p->TPoint.mX = convertPosToValueX(p->x());
    p->TPoint.mY = convertPosToValueY(p->y());

    // Insert to last but second postion
    q = Points.back();
    Points.pop_back();
    Points.push_back(p);
    Points.push_back(q);

    updateXRank();
    update();

    return p;
}

void ScopeHandler::replacePoints(const QList<QControlPoint> &arr) {
    GraphicsPoint *p;

    int i;

    // If GUI points is more than arr holds
    while (Points.size() > arr.size()) {
        p = Points.back();
        removePointCore(p);
        Points.pop_back();
    }

    // Replace
    for (i = 0; i < Points.size(); ++i) {
        p = Points[i];
        p->TPoint = arr[i];

        // Set deselected
        if (p->isSelected()) {
            qDragIn.removeOne(p);
        }
    }

    // If GUI points is less than arr holds
    i = Points.size();
    while (i < arr.size()) {
        p = createPointCore(); // 将控制点的父窗口设为编辑区域

        p->TPoint = arr[i];
        Points.push_back(p);
        ++i;
    }

    adjustPoints();
    updateXRank();
}

bool ScopeHandler::removePoints(const QList<GraphicsPoint *> &points) {
    GraphicsPoint *p;

    if (points.isEmpty()) {
        return false;
    }

    for (int i = 0; i < points.size(); ++i) {
        p = points[i];
        Points.removeOne(p);
        removePointCore(p);
    }

    updateXRank();
    update();

    return true;
}

void ScopeHandler::clearPoints() {
}

void ScopeHandler::makeDefaultPoints() {
}
