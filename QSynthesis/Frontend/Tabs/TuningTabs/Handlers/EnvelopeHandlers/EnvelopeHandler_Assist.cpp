#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../EnvelopeHandler.h"

QRectF EnvelopeHandler::visionScope() const {
    return m_geometry;
}

double EnvelopeHandler::convertPosToValueX(double x) const {
    double noteX = m_note->x();
    double tick = double(x - noteX) * 480 / m_editor->ptrs()->currentWidth;
    double time = m_note->convertTickToTime(tick);
    return time;
}

double EnvelopeHandler::convertPosToValueY(double y) const {
    double noteY = m_note->y();
    double cent = -1 * double(y - noteY) * 100 / m_editor->ptrs()->currentHeight + 100;
    return cent;
}

double EnvelopeHandler::convertValueToPosX(double x) const {
    int noteX = m_note->x();
    double tick = m_note->convertTimeToTick(x);
    int toX = noteX + tick / 480 * m_editor->ptrs()->currentWidth;
    return toX;
}

double EnvelopeHandler::convertValueToPosY(double y) const {
    int noteY = m_note->y();
    int toY = noteY - (y - 100) / 100 * m_editor->ptrs()->currentHeight;
    return toY;
}

QList<QControlPoint> EnvelopeHandler::fromCorrectPoints(const QList<QControlPoint> &arr) {
    int p3 = (arr.size() >= 4) ? (arr.size() - 2) : arr.size();

    int i;
    double interval, prev;
    QList<QControlPoint> points2, points3, result;

    prev = m_note->inPoint();
    for (i = 0; i < p3; ++i) {
        interval = arr[i].mX - prev;
        prev = arr[i].mX;
        points2.append(QControlPoint(interval, arr[i].mY));
    }
    prev = m_note->outPoint();

    for (i = arr.size() - 1; i >= p3; --i) {
        interval = prev - arr[i].mX;
        prev = arr[i].mX;
        points3.append(QControlPoint(interval, arr[i].mY));
    }

    for (i = 0; i < points2.size(); ++i) {
        result.append(points2[i]);
    }
    for (i = points3.size() - 1; i >= 0; --i) {
        result.append(points3[i]);
    }

    return result;
}

QList<QControlPoint> EnvelopeHandler::toCorrectPoints(const QList<QControlPoint> &arr) {
    int p3 = (arr.size() >= 4) ? (arr.size() - 2) : arr.size();

    int i;
    double pos;
    QList<QControlPoint> points2, points3, result;

    pos = m_note->inPoint();
    for (i = 0; i < p3; ++i) {
        pos += arr[i].mX;
        points2.push_back(QControlPoint(pos, arr[i].mY));
    }
    pos = m_note->outPoint();

    for (i = arr.size() - 1; i >= p3; --i) {
        pos -= arr[i].mX;
        points3.push_back(QControlPoint(pos, arr[i].mY));
    }

    for (i = 0; i < points2.size(); ++i) {
        result.push_back(points2[i]);
    }
    for (i = points3.size() - 1; i >= 0; --i) {
        result.push_back(points3[i]);
    }

    qSort(result);
    return result;
}
