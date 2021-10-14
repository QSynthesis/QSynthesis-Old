#include "MorePoint.h"

MorePoint::MorePoint() {
}

MorePoint::MorePoint(const QPoint &p) : QPointF(p) {
}

MorePoint::MorePoint(const QPointF &p) : QPointF(p) {
}

MorePoint::MorePoint(qreal xpos, qreal ypos) : QPointF(xpos, ypos) {
}

MorePoint::~MorePoint() {
}
