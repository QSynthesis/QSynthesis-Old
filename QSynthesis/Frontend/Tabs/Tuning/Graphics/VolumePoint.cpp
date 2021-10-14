#include "VolumePoint.h"
#include "../Graphics/GraphicsNote.h"
#include "../Controllers/EnvelopeHandler.h"

VolumePoint::VolumePoint(EnvelopeHandler *scope, NotesArea *editor, QGraphicsItem *parent)
    : GraphicsPoint(scope, editor, parent) {
}

VolumePoint::~VolumePoint() {
}

void VolumePoint::init() {
}

MorePoint VolumePoint::limitArea(MorePoint origin) {
    Qt::KeyboardModifiers c = QApplication::keyboardModifiers();

    bool cs = c == (Qt::ShiftModifier | Qt::ControlModifier);
    bool c1 = c == Qt::ControlModifier;
    bool s1 = c == Qt::ShiftModifier;

    if (!m_scope) {
        return origin;
    }

    if (m_move && (cs || s1)) {
        GraphicsPoint *np = m_scope->getNearestPoint(this, origin.x());

        double voiceOverlapPlus = m_scope->note()->inOverlapPoint();
        double voiceOverlapEnd = m_scope->note()->outOverlapPoint();

        double overlapX = m_scope->convertValueToPosX(voiceOverlapPlus) - m_radius;
        double noteX = m_scope->note()->staticPos().x() - m_radius;
        double endX = m_scope->convertValueToPosX(voiceOverlapEnd) - m_radius;

        if (np && qAbs(origin.x() - np->x()) < qAbs(origin.x() - overlapX) &&
            qAbs(origin.x() - np->x()) < qAbs(origin.x() - noteX) &&
            qAbs(origin.x() - np->x()) < qAbs(origin.x() - endX)) {
            origin.setX(np->x());
        } else if (qAbs(origin.x() - overlapX) < qAbs(origin.x() - noteX) &&
                   qAbs(origin.x() - overlapX) < qAbs(origin.x() - endX)) {
            origin.setX(overlapX);
        } else if (qAbs(origin.x() - endX) < qAbs(origin.x() - noteX)) {
            origin.setX(endX);
        } else {
            origin.setX(noteX);
        }
    }
    // Default limit x
    if (origin.x() < m_scope->activeScope().left()) {
        origin.setX(m_scope->activeScope().left());
    } else if (origin.x() > m_scope->activeScope().right()) {
        origin.setX(m_scope->activeScope().right());
    }

    if (m_move && (cs || c1)) {
        origin.setY(m_windowPoint.y());
    }

    // Default limit y
    if (origin.y() < m_scope->activeScope().top()) {
        origin.setY(m_scope->activeScope().top());
    } else if (origin.y() > m_scope->activeScope().bottom()) {
        origin.setY(m_scope->activeScope().bottom());
    }

    return origin;
}

MorePoint VolumePoint::limitAreaT(MorePoint origin) {
    return limitArea(origin);
}
