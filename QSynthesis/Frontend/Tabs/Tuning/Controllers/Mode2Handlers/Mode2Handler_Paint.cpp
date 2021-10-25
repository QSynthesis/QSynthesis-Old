#include "../../Editor/Areas/NotesArea.h"
#include "../../Graphics/GraphicsLines.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../Mode2Handler.h"
#include "Methods.h"

using namespace Utau;

#include <QPainterPath>

void Mode2Handler::drawMode1(QPainter *painter) {
}

void Mode2Handler::drawMode2(QPainter *painter) {
    QPointF prev, curr;
    QControlPoint prevT, currT;

    QPainterPath path;
    PointType type;

    double thickness = m_solid ? 1.5 : 1.5;

    QColor solidLineColor = m_solid ? m_mode2SolidLineEnabledColor : m_mode2SolidLineDisabledColor;
    QColor dashLineCOlor = m_solid ? m_mode2DashLineEnabledColor : m_mode2DashLineDisabledColor;
    QColor invalidLineColor =
        m_solid ? m_mode2InvalidLineEnabledColor : m_mode2InvalidLineDisabledColor;

    QPen solidPen(solidLineColor, thickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen dashPen(dashLineCOlor, thickness, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    QPen invalidPen(invalidLineColor, thickness, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);

    painter->setBrush(Qt::NoBrush);

    if (Points.size() > 0) {
        prev = Points.front()->pos() - screen()->pos();
        prevT = Points.front()->TPoint;
    } else {
        // 起始点设在音符开头
        prev = m_note->headPos() - screen()->pos();
        prevT = QControlPoint(0, 0);
    }

    int prevPenState = -1;
    int curPenState;

    for (int i = 1; i < Points.size(); ++i) {

        type = Points[i]->TPoint.mP;

        curr = Points[i]->pos() - screen()->pos();
        currT = Points[i]->TPoint;

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

        if (type == sJoin) { // S型
            pathCosineTo(path, prev, curr);
        } else if (type == rJoin) { // R型
            pathCosineRTo(path, prev, curr);
        } else if (type == jJoin) { // J型
            pathCosineJTo(path, prev, curr);
        } else {
            path.lineTo(curr);
        }
        if (i == Points.size() - 1) {
            if (!path.isEmpty()) {
                painter->drawPath(path);
            }
        }
        // 结束描线

        prev = curr;
        prevT = currT;
        prevPenState = curPenState;
    }

    // 尝试寻找后继
    GraphicsNote *nextNote = m_note->MNext();
    QPainterPath path2;

    painter->setPen(dashPen);

    // 后继点默认设为音符尾部
    curr = m_note->tailPos() - screen()->pos();

    // 不存在后继音符
    if (!nextNote) {
        path2.moveTo(prev);
        pathCosineTo(path2, prev, curr);
        painter->drawPath(path2);

        return;
    }

    Mode2Handler *nextCurve = nextNote->curves();
    GraphicsPoint *nextFirstPoint = nullptr;

    // 后继音符没有音高线或者获取第一个点失败
    if (!nextCurve || nextCurve->Points.isEmpty() || !(nextFirstPoint = nextCurve->firstPoint())) {
        path2.moveTo(prev);
        pathCosineTo(path2, prev, curr);

        prev = curr;

        // 后继点移动到下一个音符开头
        curr = nextNote->headPos() - screen()->pos();

        path2.moveTo(prev);
        pathCosineTo(path2, prev, curr);
        painter->drawPath(path2);

        return;
    }

    curr = nextFirstPoint->pos() - screen()->pos();

    path2.moveTo(prev);
    pathCosineTo(path2, prev, curr);

    if (prev.x() > curr.x()) {
        painter->setPen(invalidPen);
    }
    painter->drawPath(path2);
}

void Mode2Handler::drawPoint(QPainter *painter, GraphicsPoint *p) {
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
