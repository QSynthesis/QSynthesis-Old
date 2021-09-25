#include "WaveformScrollArea.h"
#include "mainwindow.h"

#include <QApplication>
#include <QEvent>
#include <QWheelEvent>

WaveformScrollArea::WaveformScrollArea(QWidget *parent)
    : GraphicsLinearView(Qt::Horizontal, parent) {
    setAlignment(Qt::AlignLeft);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    verticalScrollBar()->installEventFilter(this);
    horizontalScrollBar()->installEventFilter(this);

    sample.offsetLine = Qt::lightGray;
    sample.constantLine = (QColorConstants::Svg::pink);
    sample.blankLine = (QColorConstants::Svg::lightblue);
    sample.preUttrLine = (Qt::red);
    sample.overlapLine = (Qt::green);

    sample.waveform = QColor(0, 110, 0);
    sample.frqCurves = Qt::blue;

    int alpha = 96;
    sample.offsetBack = (QColor(sample.offsetLine.red(), sample.offsetLine.green(),
                                sample.offsetLine.blue(), alpha));
    sample.constantBack = (QColor(sample.constantLine.red(), sample.constantLine.green(),
                                  sample.constantLine.blue(), alpha));
    sample.blankBack =
        (QColor(sample.blankLine.red(), sample.blankLine.green(), sample.blankLine.blue(), alpha));
}

WaveformScrollArea::~WaveformScrollArea() {
}

QRectF WaveformScrollArea::viewportRect() const {
    QRect viewport_rect(0, 0, viewport()->width(), viewport()->height());
    QRectF visible_scene_rect = mapToScene(viewport_rect).boundingRect();
    return visible_scene_rect;
}

void WaveformScrollArea::wheelEvent(QWheelEvent *event) {
    Qt::KeyboardModifiers c = event->modifiers();
    QPoint delta = event->angleDelta();
    if (c & Qt::AltModifier) {
        return;
    }
    if (c == qConfig->wave.moveVertically) {
        event->setModifiers(Qt::NoModifier);
        QApplication::sendEvent(verticalScrollBar(), event);
    } else if (c == qConfig->wave.moveHorizontally) {
        event->setModifiers(Qt::NoModifier);
        QApplication::sendEvent(horizontalScrollBar(), event);
    } else if (c == qConfig->wave.zoomHorizontally) {
        emit horizontalZoomRequested(qAbs(delta.x()) > qAbs(delta.y()) ? delta.x() : delta.y());
    }
}

QColor WaveformScrollArea::sampleOffsetLine() const {
    return sample.offsetLine;
}
QColor WaveformScrollArea::sampleConstantLine() const {
    return sample.constantLine;
}
QColor WaveformScrollArea::sampleBlankLine() const {
    return sample.blankLine;
}
QColor WaveformScrollArea::samplePreUttrLine() const {
    return sample.preUttrLine;
}
QColor WaveformScrollArea::sampleOverlapLine() const {
    return sample.overlapLine;
}
QColor WaveformScrollArea::sampleOffsetBack() const {
    return sample.offsetBack;
}
QColor WaveformScrollArea::sampleConstantBack() const {
    return sample.constantBack;
}
QColor WaveformScrollArea::sampleBlankBack() const {
    return sample.blankBack;
}
QColor WaveformScrollArea::sampleWaveform() const {
    return sample.waveform;
}
QColor WaveformScrollArea::sampleFrqCurves() const {
    return sample.frqCurves;
}

void WaveformScrollArea::setSampleOffsetLine(const QColor &color) {
    sample.offsetLine = color;
    emit sampleThemeUpdated();
}
void WaveformScrollArea::setSampleConstantLine(const QColor &color) {
    sample.constantLine = color;
    emit sampleThemeUpdated();
}
void WaveformScrollArea::setSampleBlankLine(const QColor &color) {
    sample.blankLine = color;
    emit sampleThemeUpdated();
}
void WaveformScrollArea::setSamplePreUttrLine(const QColor &color) {
    sample.preUttrLine = color;
    emit sampleThemeUpdated();
}
void WaveformScrollArea::setSampleOverlapLine(const QColor &color) {
    sample.overlapLine = color;
    emit sampleThemeUpdated();
}
void WaveformScrollArea::setSampleOffsetBack(const QColor &color) {
    sample.offsetBack = color;
    emit sampleThemeUpdated();
}
void WaveformScrollArea::setSampleConstantBack(const QColor &color) {
    sample.constantBack = color;
    emit sampleThemeUpdated();
}
void WaveformScrollArea::setSampleBlankBack(const QColor &color) {
    sample.blankBack = color;
    emit sampleThemeUpdated();
}
void WaveformScrollArea::setSampleWaveform(const QColor &color) {
    sample.waveform = color;
    emit sampleThemeUpdated();
}
void WaveformScrollArea::setSampleFrqCurves(const QColor &color) {
    sample.frqCurves = color;
    emit sampleThemeUpdated();
}
