#include "../../Editor/Areas/NotesArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Graphics/VibratoHandles/VibratoLineHandle.h"
#include "../../Graphics/VibratoHandles/VibratoPlaneHandle.h"
#include "../../TuningGroup.h"
#include "../Mode2Handler.h"

#include <cmath>

#define PI 3.1415926

void Mode2Handler::drawVibrato(QPainter *painter) {
    if (Vibrato.size() < 8) {
        return;
    }

    QColor solidLineColor = m_solid ? m_vibratoEnabledColor : m_vibratoDisabledColor;
    QPen solidPen(solidLineColor, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    int currentWidth = m_editor->ptrs()->currentWidth;

    double amplitude = m_note->height() * Vibrato[2] / 100.0; // 振幅

    double pixel_len = m_note->width() * Vibrato[0] / 100.0; // 颤音像素长度
    QPointF pixel_org(m_note->tailPos().x() - pixel_len, m_note->tailPos().y());

    double period = Vibrato[1]; // 周期

    if (period < minPeriod) {
        period = minPeriod;
    }
    if (period > maxPeriod) {
        period = maxPeriod;
    }

    double tick_time = m_note->convertTimeToTick(period); // ticks 周期
    double pixel_time = tick_time / 480 * currentWidth;   // 一个周期的像素长度

    double phase = Vibrato[5];

    QPainterPath path;

    double i;
    double j, k, p, y;

    double a, b;
    double c = pixel_org.y();

    k = 1 / pixel_time * 2 * PI;
    p = phase / 100.0 * 2 * PI;

    double step = pixel_time / 32;

    double start = pixel_org.x();
    double end = m_note->tailPos().x();
    double easeIn = Vibrato[3] / 100.0 * pixel_len;
    double easeOut = (1 - Vibrato[4] / 100.0) * pixel_len;

    double offset = Vibrato[6] / 100.0;

    while (step < 0.2) {
        step *= 2.0;
    }
    while (step > 5.0) {
        step /= 2.0;
    }

    i = start;

    path.moveTo(QPointF(i, c) - screen()->pos());

    while (i <= end) {
        j = i - start;
        y = amplitude * sin(k * j - p);

        a = 1;
        b = offset;

        // 套上偏移
        y += b * amplitude;

        if (j < easeIn) {
            a *= j / easeIn;
        }
        if (j > easeOut) {
            a *= 1 - (j - easeOut) / (pixel_len - easeOut);
        }

        // 套上包络
        y = a * y;

        path.lineTo(QPointF(i, c - y) - screen()->pos());
        i += step;
    }

    // 画最后一个点
    if (i != end) {
        i = end;

        j = i - start;
        y = amplitude * sin(k * j - p);

        a = 1;
        b = offset;

        // 套上偏移
        y += b * amplitude;

        if (j < easeIn) {
            a *= j / easeIn;
        }
        if (j > easeOut) {
            a *= 1 - (j - easeOut) / (pixel_len - easeOut);
        }

        // 套上包络
        y = a * y;

        path.lineTo(QPointF(i, c - y) - screen()->pos());
    }
    path.lineTo(QPointF(i, c) - screen()->pos());

    painter->setBrush(Qt::NoBrush);
    painter->setPen(solidPen);
    painter->drawPath(path);
}

void Mode2Handler::drawVibratoEditor(QPainter *painter) {
    if (!hasVBREditor()) {
        return;
    }

    QColor vbrLineColor = m_vibratoEditorLinesColor;

    QPen vbrPen(vbrLineColor, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPainterPath path;

    painter->setBrush(Qt::NoBrush);
    painter->setPen(vbrPen);

    // Top
    path.moveTo(pVibratoStandardStart() - screen()->pos());
    path.lineTo(pVibratoEaseInTop() - screen()->pos());
    path.lineTo(pVibratoEaseOutTop() - screen()->pos());
    path.lineTo(pVibratoStandardEnd() - screen()->pos());
    painter->drawPath(path);

    // Center
    path.moveTo(pVibratoStandardStart() - screen()->pos());
    path.lineTo(pVibratoEaseInCenter() - screen()->pos());
    path.lineTo(pVibratoEaseOutCenter() - screen()->pos());
    path.lineTo(pVibratoStandardEnd() - screen()->pos());
    painter->drawPath(path);

    // Bottom
    path.moveTo(pVibratoStandardStart() - screen()->pos());
    path.lineTo(pVibratoEaseInBottom() - screen()->pos());
    path.lineTo(pVibratoEaseOutBottom() - screen()->pos());
    path.lineTo(pVibratoStandardEnd() - screen()->pos());
    painter->drawPath(path);

    // Left
    path.moveTo(pVibratoEaseInTop() - screen()->pos());
    path.lineTo(pVibratoEaseInBottom() - screen()->pos());
    painter->drawPath(path);

    // Right
    path.moveTo(pVibratoEaseOutTop() - screen()->pos());
    path.lineTo(pVibratoEaseOutBottom() - screen()->pos());
    painter->drawPath(path);
}
