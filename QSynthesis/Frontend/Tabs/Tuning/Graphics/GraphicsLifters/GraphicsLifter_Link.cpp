#include "../../Params/Areas/LiftersArea.h"
#include "../../TuningGroup.h"
#include "../GraphicsLifter.h"
#include "../GraphicsNote.h"

MorePoint GraphicsLifter::limitArea(MorePoint origin) {
    double h = m_region.height() / 2;
    double h1 = h / 2;
    double unit_y =
        int((origin.y() - m_region.top()) / h1 + 0.5) * h1 - h1 + double(h) / 2 + m_region.top();

    Qt::KeyboardModifiers c = QApplication::keyboardModifiers();
    bool c1 = c == Qt::ControlModifier;

    if (c1 && m_move) {
        origin.setY(unit_y);
    }

    if (origin.y() < m_region.top()) {
        origin.setY(m_region.top());
    } else if (origin.y() > m_region.bottom()) {
        origin.setY(m_region.bottom());
    }
    origin.setX(m_region.left());

    return origin;
}

MorePoint GraphicsLifter::limitAreaT(MorePoint origin) {
    return limitArea(origin);
}

void GraphicsLifter::linkMove(QPointF pos) {
    if (!m_active) {
        setActive(true);
    }
    GraphicsLineHandle::linkMove(pos);
}
