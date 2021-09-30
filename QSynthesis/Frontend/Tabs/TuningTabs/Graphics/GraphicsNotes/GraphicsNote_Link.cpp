#include "../../Areas/Editor/NotesArea.h"
#include "../../TuningGroup.h"
#include "../GraphicsNote.h"

#include <cmath>

MorePoint GraphicsNote::limitArea(MorePoint p) {
    // Adsorb to standard pitch
    int h = m_editor->ptrs()->currentHeight;

    p.setY(int(p.y() / h + 0.5) * h);
    if (p.y() < 0) {
        p.setY(0);
    } else if (p.y() > 83.5 * h) {
        p.setY(83 * h);
    }

    // <pve
    if (this == qDragIn.leftmost()) {
        double adsorbX = qDragIn.getPossiblePos(staticPos().x(), p.x(), qDragIn.totalWidth());
        p.setX(adsorbX);
    } else {
        p.setX(m_prev->x() + m_prev->width());
    }

    return p;
}

MorePoint GraphicsNote::limitAreaT(MorePoint p) {
    if (qDragIn.stretching) {
        if (m_prev) {
            p.setX(m_prev->x() + m_prev->width());
        }
    } else {
        if (p.x() < qDragIn.leftmost()->staticPos().x()) {
            if (p.x() >= qDragIn.leftmost()->x()) {
                if (m_prev && m_prev->staticPos().x() != m_prev->x()) {
                    p.setX(m_prev->x() + m_prev->width());
                } else {
                    p.setX(qDragIn.leftmost()->x() + qDragIn.totalWidth());
                }
            }
        } else {
            if (p.x() < qDragIn.leftmost()->x() + qDragIn.totalWidth()) {
                if (!m_prev->isSelected() && m_prev->staticPos().x() != m_prev->x()) {
                    p.setX(m_prev->x() + m_prev->width());
                } else {
                    GraphicsNote *leftmost = static_cast<GraphicsNote *>(qDragIn.leftmost());
                    p.setX(leftmost->m_prev ? (leftmost->m_prev->x() + leftmost->m_prev->width())
                                            : m_editor->zeroLine());
                }
            }
        }
    }
    return p;
}

MoreSize GraphicsNote::limitSize(MoreSize s) {
    int curWidth = m_editor->ptrs()->currentWidth;
    int curAdsorb = m_editor->ptrs()->currentAdsorb;

    double minimum = double(curWidth) / 32;
    int minimunTick = 15;

    s.setHeight(height());

    if (curAdsorb == 0) {
        curAdsorb = 480;
    }

    double width32 = double(curWidth) / curAdsorb;
    int ratio = round(s.width() / width32);

    if (ratio < 1) {
        ratio = 1;
    }

    double toW = width32 * ratio;
    int toL = 480 / curAdsorb * ratio;

    s.setWidth(toW);
    s.setLength(toL);

    if (s.width() < minimum) {
        s.setWidth(minimum);
        s.setLength(minimunTick);
    }

    // Prevent to cover the next of next note
    if (qDragIn.stretching == Qs::RelativeStretch && m_next) {
        if (s.width() + x() > m_next->width() + m_next->x()) {
            s.setWidth(m_next->width() + m_next->x() - x());
            s.setLength(Note.length + m_next->Note.length);
        }
    }

    return s;
}

void GraphicsNote::linkStretch(QPointF pos) {
    QPointF global_pos = pos;
    QPointF relative_pos = global_pos - m_startPoint;

    m_moving = true;

    MoreSize s = limitSize(MoreSize(m_windowSize.width() + relative_pos.x(),
                                    m_windowSize.height() + relative_pos.y(), Note.length));
    setSize(s);
    m_lengthRef = s.length();

    m_sizeChanged = false;
    if (size() != m_prevSize) {
        handleSizeChange();
        m_prevSize = size();
        m_sizeChanged = true;
    }
}

void GraphicsNote::linkMove(QPointF pos) {
    if (m_stretch) {
        linkStretch(pos);
    } else {
        GraphicsDragger::linkMove(pos);
    }
}

void GraphicsNote::involveMove(QPointF pos) {
    if (qDragIn.stretching == Qs::RelativeStretch) {
        QPointF toPos = limitAreaT(m_windowPoint);
        int toX = m_windowPoint.x() - toPos.x() + m_windowSize.width();

        // Resize and move
        if (toX > 0) {
            setVisible(true);
            setGeometry(QRectF(0, 0, toX, rect().height()));
            setLocation(toPos);
        } else {
            setVisible(false);
        }
    } else {
        GraphicsDragger::involveMove(pos);
    }

    m_posChanged = false;
    if (this->pos() != m_prevPoint) {
        handlePosChange();
        m_prevPoint = this->pos();
        m_posChanged = true;
    }

    m_sizeChanged = false;
    if (size() != m_prevSize) {
        handleSizeChange();
        m_prevSize = size();
        m_sizeChanged = true;
    }
}

void GraphicsNote::handlePosChange() {
}

void GraphicsNote::handleSizeChange() {
}
