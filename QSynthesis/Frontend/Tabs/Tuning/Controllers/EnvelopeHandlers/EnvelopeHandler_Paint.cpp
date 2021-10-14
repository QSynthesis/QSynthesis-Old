#include "../../Editor/Areas/NotesArea.h"
#include "../../Graphics/GraphicsLines.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../EnvelopeHandler.h"

void EnvelopeHandler::drawEnvelope(QPainter *painter) {
    QPointF prev, curr;
    QControlPoint prevT, currT;

    QPainterPath path;

    double thickness = m_solid ? 1.5 : 1.5;
    QColor solidLineColor = m_solid ? m_envSolidLineEnabledColor : m_envSolidLineDisabledColor;
    QColor dashLineCOlor = m_solid ? m_envDashLineEnabledColor : m_envDashLineDisabledColor;

    QPen solidPen(solidLineColor, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dashPen(dashLineCOlor, thickness, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);

    QPointF veryStart(m_activeScope.bottomLeft() - screen()->pos());
    QPointF veryEnd(m_activeScope.bottomRight() - screen()->pos());

    if (!Points.isEmpty()) {
        prev = veryStart;
        prevT = QControlPoint(m_note->inPoint(), 0);
    } else {
        return;
    }

    int prevPenState = -1;
    int curPenState;

    // 画边框
    painter->setBrush(Qt::NoBrush);
    for (int i = 0; i <= Points.size(); ++i) {
        if (i < Points.size()) {
            curr = QPointF(Points[i]->pos() - screen()->pos());
            currT = Points[i]->TPoint;
        } else {
            curr = veryEnd;
            currT = QControlPoint(m_note->outPoint(), 0);
        }

        double curTick = m_note->convertTimeToTick(currT.mX);
        double prevTick = m_note->convertTimeToTick(prevT.mX);

        bool tooShort = qAbs(curTick - prevTick) < 2; // 小于 2 tick

        // 开始描线
        curPenState = !tooShort;
        if (curPenState != prevPenState) {
            if (!path.isEmpty()) {
                painter->drawPath(path);
            }
            path.clear();
            path.moveTo(prev);
        }

        painter->setPen(tooShort ? dashPen : solidPen);
        path.lineTo(curr);

        if (i == Points.size()) {
            if (!path.isEmpty()) {
                painter->drawPath(path);
            }
        }
        // 结束描线

        prev = curr;
        prevT = currT;
        prevPenState = curPenState;
    }
}

void EnvelopeHandler::drawPoint(QPainter *painter, GraphicsPoint *p) {
    // Draw core
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_pointColor);
    painter->drawEllipse(QPointF(0, 0), m_pointRadius, m_pointRadius);

    if (p->isSelected() || p->hovered()) {
        // Draw ring
        painter->setPen(QPen(m_ringColor, m_ringWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(Qt::NoBrush);
        painter->drawEllipse(QPointF(0, 0), p->radius(), p->radius());
    }
}
