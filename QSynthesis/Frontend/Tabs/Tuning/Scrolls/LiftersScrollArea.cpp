#include "LiftersScrollArea.h"

#include <QDebug>
#include <QEvent>
#include <QScrollBar>

LiftersScrollArea::LiftersScrollArea(QWidget *parent) : GraphicsLinearView(Qt::Horizontal, parent) {
    setRenderHint(QPainter::Antialiasing);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    horizontalScrollBar()->setEnabled(false);

    installEventFilter(this);

    initLight();
}

LiftersScrollArea::~LiftersScrollArea() {
}

void LiftersScrollArea::wheelEvent(QWheelEvent *event) {
}

void LiftersScrollArea::initLight() {
    // LiftersArea
    editor.timeLine = QColor(0xD4D4D4);
    editor.sectionLine = QColor(0xBFBFBF);
    editor.back = QColor(0xFFFFFF);

    // GraphicsLifter
    lifter.active = QColor(0x79BBEE);
    lifter.inactive = Qt::gray;
    lifter.activeH = QColor(QColorConstants::Svg::pink);
    lifter.inactiveH = Qt::lightGray;
}

void LiftersScrollArea::initDark() {
    // LiftersArea
    editor.timeLine = QColor(0x1C1C1C);
    editor.sectionLine = QColor(0x101010);
    editor.back = QColor(0x2D2D2D);

    // GraphicsLifter
    lifter.active = QColor(0x79BBEE);
    lifter.inactive = Qt::gray;
    lifter.activeH = QColor(QColorConstants::Svg::pink);
    lifter.inactiveH = Qt::lightGray;
}

QColor LiftersScrollArea::editorTimeLine() const {
    return editor.timeLine;
}
QColor LiftersScrollArea::editorSectionLine() const {
    return editor.sectionLine;
}
QColor LiftersScrollArea::editorBack() const {
    return editor.back;
}
QColor LiftersScrollArea::lifterActive() const {
    return lifter.active;
}
QColor LiftersScrollArea::lifterInactive() const {
    return lifter.inactive;
}
QColor LiftersScrollArea::lifterActiveH() const {
    return lifter.activeH;
}
QColor LiftersScrollArea::lifterInactiveH() const {
    return lifter.inactiveH;
}

void LiftersScrollArea::setEditorTimeLine(const QColor &color) {
    editor.timeLine = color;
    emit editorThemeUpdated();
}
void LiftersScrollArea::setEditorSectionLine(const QColor &color) {
    editor.sectionLine = color;
    emit editorThemeUpdated();
}
void LiftersScrollArea::setEditorBack(const QColor &color) {
    editor.back = color;
    emit editorThemeUpdated();
}
void LiftersScrollArea::setLifterActive(const QColor &color) {
    lifter.active = color;
    emit lifterThemeUpdated();
}
void LiftersScrollArea::setLifterInactive(const QColor &color) {
    lifter.inactive = color;
    emit lifterThemeUpdated();
}
void LiftersScrollArea::setLifterActiveH(const QColor &color) {
    lifter.activeH = color;
    emit lifterThemeUpdated();
}
void LiftersScrollArea::setLifterInactiveH(const QColor &color) {
    lifter.inactiveH = color;
    emit lifterThemeUpdated();
}
