#include "../../Editor/Areas/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../ScopeHandler.h"

QRectF ScopeHandler::activeScope() const {
    return m_activeScope;
}

QRectF ScopeHandler::visionScope() const {
    return m_geometry;
}

GraphicsPoint *ScopeHandler::getNearestPoint(GraphicsPoint *p, int limitedPos) const {
    if (Points.empty()) {
        return nullptr;
    }
    double min = qAbs(Points[0]->x() - limitedPos);
    int minIndex = 0;

    for (int i = 1; i < Points.size(); ++i) {
        if (Points[i] && Points[i] != p) {
            double cur = qAbs(Points[i]->x() - limitedPos);
            if (cur < min) {
                min = cur;
                minIndex = i;
            }
        }
    }
    return Points[minIndex];
}

double ScopeHandler::convertPosToValueX(double x) const {
    return x;
}

double ScopeHandler::convertPosToValueY(double y) const {
    return y;
}

double ScopeHandler::convertValueToPosX(double x) const {
    return x;
}

double ScopeHandler::convertValueToPosY(double y) const {
    return y;
}

QPoint ScopeHandler::continuousSelection() const {
    int min, max;
    int i;

    bool findPoint = false;

    min = 0;
    max = Points.size() - 1;

    for (i = 0; i < Points.size(); ++i) {
        if (Points[i]->isSelected()) {
            findPoint = true;
            min = i;
            break;
        }
    }
    for (i = Points.size() - 1; i >= 0; --i) {
        if (Points[i]->isSelected()) {
            max = i;
            break;
        }
    }

    if (findPoint) {
        return QPoint(min, max);
    } else {
        return QPoint(-1, -1);
    }
}

void ScopeHandler::drawPoint(QPainter *painter, GraphicsPoint *p) {
}
