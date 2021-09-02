#include "DraggerHandler.h"
#include "../Graphics/GraphicsLifter.h"
#include "../Graphics/GraphicsNote.h"
#include "../Graphics/GraphicsPoint.h"

DraggerHandler::DraggerHandler() {
    stretching = Qs::NoStretch;
}

DraggerHandler::~DraggerHandler() {
}

void DraggerHandler::addOne(GraphicsDragger *obj) {
    switch (obj->element()) {
    case GraphicsDragger::Note: {
        selectedNotes.insertAuto(static_cast<GraphicsNote *>(obj));
        obj->setSelected(true);
        break;
    }
    case GraphicsDragger::Point: {
        selectedPoints.insertAuto(static_cast<GraphicsPoint *>(obj));
        obj->setSelected(true);
        break;
    }
    case GraphicsDragger::Lifter: {
        selectedHandles.insertAuto(static_cast<GraphicsLifter *>(obj));
        obj->setSelected(true);
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::removeOne(GraphicsDragger *obj) {
    switch (obj->element()) {
    case GraphicsDragger::Note: {
        selectedNotes.removeAuto(static_cast<GraphicsNote *>(obj));
        obj->setSelected(false);
        break;
    }
    case GraphicsDragger::Point: {
        selectedPoints.removeAuto(static_cast<GraphicsPoint *>(obj));
        obj->setSelected(false);
        break;
    }
    case GraphicsDragger::Lifter: {
        selectedHandles.removeAuto(static_cast<GraphicsLifter *>(obj));
        obj->setSelected(false);
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::removeAll(GraphicsDragger::Element element) {
    switch (element) {
    case GraphicsDragger::Note: {
        for (auto it = selectedNotes.begin(); it != selectedNotes.end(); ++it) {
            (*it)->setSelected(false);
        }
        selectedNotes.clear();
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = selectedPoints.begin(); it != selectedPoints.end(); ++it) {
            (*it)->setSelected(false);
        }
        selectedPoints.clear();
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = selectedHandles.begin(); it != selectedHandles.end(); ++it) {
            (*it)->setSelected(false);
        }
        selectedHandles.clear();
        break;
    }
    default: {
        removeAll(GraphicsDragger::Note);
        removeAll(GraphicsDragger::Point);
        removeAll(GraphicsDragger::Lifter);
        break;
    }
    }
}

void DraggerHandler::addOneT(GraphicsDragger *obj) {
    switch (obj->element()) {
    case GraphicsDragger::Note: {
        involvedNotes.insertAuto(static_cast<GraphicsNote *>(obj));
        obj->setInvolved(true);
        break;
    }
    case GraphicsDragger::Point: {
        involvedPoints.insertAuto(static_cast<GraphicsPoint *>(obj));
        obj->setInvolved(true);
        break;
    }
    case GraphicsDragger::Lifter: {
        involvedHandles.insertAuto(static_cast<GraphicsLifter *>(obj));
        obj->setInvolved(true);
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::removeOneT(GraphicsDragger *obj) {
    switch (obj->element()) {
    case GraphicsDragger::Note: {
        involvedNotes.removeAuto(static_cast<GraphicsNote *>(obj));
        obj->setInvolved(false);
        break;
    }
    case GraphicsDragger::Point: {
        involvedPoints.removeAuto(static_cast<GraphicsPoint *>(obj));
        obj->setInvolved(false);
        break;
    }
    case GraphicsDragger::Lifter: {
        involvedHandles.removeAuto(static_cast<GraphicsLifter *>(obj));
        obj->setInvolved(false);
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::removeAllT(GraphicsDragger::Element element) {
    switch (element) {
    case GraphicsDragger::Note: {
        for (auto it = involvedNotes.begin(); it != involvedNotes.end(); ++it) {
            (*it)->setInvolved(false);
        }
        involvedNotes.clear();
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = involvedPoints.begin(); it != involvedPoints.end(); ++it) {
            (*it)->setInvolved(false);
        }
        involvedPoints.clear();
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = involvedHandles.begin(); it != involvedHandles.end(); ++it) {
            (*it)->setInvolved(false);
        }
        involvedHandles.clear();
        break;
    }
    default: {
        removeAllT(GraphicsDragger::Note);
        removeAllT(GraphicsDragger::Point);
        removeAllT(GraphicsDragger::Lifter);
        break;
    }
    }
}

void DraggerHandler::startDrag(GraphicsDragger *obj, QPointF pos) {
    dragging = true;
    center = obj;

    switch (obj->element()) {
    case GraphicsDragger::Note: {
        for (auto it = selectedNotes.begin(); it != selectedNotes.end(); ++it) {
            (*it)->linkPress(pos);
        }
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = selectedPoints.begin(); it != selectedPoints.end(); ++it) {
            (*it)->linkPress(pos);
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = selectedHandles.begin(); it != selectedHandles.end(); ++it) {
            (*it)->linkPress(pos);
        }
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::duringDrag(GraphicsDragger *obj, QPointF pos) {
    switch (obj->element()) {
    case GraphicsDragger::Note: {
        for (auto it = selectedNotes.begin(); it != selectedNotes.end(); ++it) {
            (*it)->linkMove(pos);
        }
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = selectedPoints.begin(); it != selectedPoints.end(); ++it) {
            (*it)->linkMove(pos);
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = selectedHandles.begin(); it != selectedHandles.end(); ++it) {
            (*it)->linkMove(pos);
        }
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::stopDrag(GraphicsDragger *obj) {
    dragging = false;
    center = nullptr;

    switch (obj->element()) {
    case GraphicsDragger::Note: {
        for (auto it = selectedNotes.begin(); it != selectedNotes.end(); ++it) {
            (*it)->linkRelease();
        }
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = selectedPoints.begin(); it != selectedPoints.end(); ++it) {
            (*it)->linkRelease();
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = selectedHandles.begin(); it != selectedHandles.end(); ++it) {
            (*it)->linkRelease();
        }
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::abandonDrag(GraphicsDragger *obj) {
    dragging = false;
    center = nullptr;

    switch (obj->element()) {
    case GraphicsDragger::Note: {
        for (auto it = selectedNotes.begin(); it != selectedNotes.end(); ++it) {
            (*it)->linkAbandon();
        }
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = selectedPoints.begin(); it != selectedPoints.end(); ++it) {
            (*it)->linkAbandon();
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = selectedHandles.begin(); it != selectedHandles.end(); ++it) {
            (*it)->linkAbandon();
        }
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::startInvolve(GraphicsDragger *obj, QPointF pos) {
    switch (obj->element()) {
    case GraphicsDragger::Note: {
        for (auto it = involvedNotes.begin(); it != involvedNotes.end(); ++it) {
            (*it)->involvePress(pos);
        }
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = involvedPoints.begin(); it != involvedPoints.end(); ++it) {
            (*it)->involvePress(pos);
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = involvedHandles.begin(); it != involvedHandles.end(); ++it) {
            (*it)->involvePress(pos);
        }
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::duringInvolve(GraphicsDragger *obj, QPointF pos) {
    switch (obj->element()) {
    case GraphicsDragger::Note: {
        for (auto it = involvedNotes.begin(); it != involvedNotes.end(); ++it) {
            (*it)->involveMove(pos);
        }
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = involvedPoints.begin(); it != involvedPoints.end(); ++it) {
            (*it)->involveMove(pos);
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = involvedHandles.begin(); it != involvedHandles.end(); ++it) {
            (*it)->involveMove(pos);
        }
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::endInvolve(GraphicsDragger *obj) {
    switch (obj->element()) {
    case GraphicsDragger::Note: {
        for (auto it = involvedNotes.begin(); it != involvedNotes.end(); ++it) {
            (*it)->involveRelease();
        }
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = involvedPoints.begin(); it != involvedPoints.end(); ++it) {
            (*it)->involveRelease();
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = involvedHandles.begin(); it != involvedHandles.end(); ++it) {
            (*it)->involveRelease();
        }
        break;
    }
    default:
        break;
    }
}

void DraggerHandler::abandonInvolve(GraphicsDragger *obj) {
    switch (obj->element()) {
    case GraphicsDragger::Note: {
        for (auto it = selectedNotes.begin(); it != selectedNotes.end(); ++it) {
            (*it)->involveAbandon();
        }
        break;
    }
    case GraphicsDragger::Point: {
        for (auto it = selectedPoints.begin(); it != selectedPoints.end(); ++it) {
            (*it)->involveAbandon();
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        for (auto it = selectedHandles.begin(); it != selectedHandles.end(); ++it) {
            (*it)->involveAbandon();
        }
        break;
    }
    default:
        break;
    }
}

GraphicsDragger *DraggerHandler::rightmost(GraphicsDragger::Element element) {
    GraphicsDragger *result = nullptr;

    switch (element) {
    case GraphicsDragger::Note: {
        if (!selectedNotes.isEmpty()) {
            result = selectedNotes.back();
        }
        break;
    }
    case GraphicsDragger::Point: {
        if (!selectedPoints.isEmpty()) {
            result = selectedPoints.back();
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        if (!selectedHandles.isEmpty()) {
            result = selectedHandles.back();
        }
        break;
    }
    default:
        break;
    }
    return result;
}

GraphicsDragger *DraggerHandler::leftmost(GraphicsDragger::Element element) {
    GraphicsDragger *result = nullptr;

    switch (element) {
    case GraphicsDragger::Note: {
        if (!selectedNotes.isEmpty()) {
            result = selectedNotes.front();
        }
        break;
    }
    case GraphicsDragger::Point: {
        if (!selectedPoints.isEmpty()) {
            result = selectedPoints.front();
        }
        break;
    }
    case GraphicsDragger::Lifter: {
        if (!selectedHandles.isEmpty()) {
            result = selectedHandles.front();
        }
        break;
    }
    default:
        break;
    }
    return result;
}

double DraggerHandler::totalWidth(GraphicsDragger::Element element) {
    return rightmost(element)->x() + rightmost(element)->width() - leftmost(element)->x();
}

void DraggerHandler::filter(GraphicsDragger::Element element) {
    QList<GraphicsDragger::Element> list{element};
    filter(list);
}

void DraggerHandler::filter(const QList<GraphicsDragger::Element> &list) {
    if (!list.contains(GraphicsDragger::Note)) {
        removeAll(GraphicsDragger::Note);
    } else if (!list.contains(GraphicsDragger::Point)) {
        removeAll(GraphicsDragger::Point);
    } else if (!list.contains(GraphicsDragger::Lifter)) {
        removeAll(GraphicsDragger::Lifter);
    }
}

double DraggerHandler::getPossiblePos(double staticX, double x, double w) {
    double i = 0;
    double j = possiblePositions.size() - 1;
    int mid, pos;
    double half;
    double toX;

    while (i <= j) {
        mid = i + (j - i) / 2;
        half = mid < (possiblePositions.size() - 1)
                   ? (possiblePositions[mid + 1] - possiblePositions[mid]) / 2
                   : 0;
        if (possiblePositions[mid] + half < x) {
            i = mid + 1;
        } else {
            j = mid - 1;
        }
    }
    pos = i;

    if (pos >= possiblePositions.size()) {
        toX = possiblePositions.back();
    } else {
        toX = possiblePositions[pos];
    }

    return toX;
}

int DraggerHandler::findPossiblePos(double x) {
    int i, j, mid;
    i = 0;
    j = possiblePositions.size() - 1;
    while (i <= j) {
        mid = i + (j - i) / 2;
        if (possiblePositions.at(mid) < x) {
            i = mid + 1;
        } else {
            j = mid - 1;
        }
    }
    if (possiblePositions.at(i) != x) {
        return -1;
    }
    return i;
}
