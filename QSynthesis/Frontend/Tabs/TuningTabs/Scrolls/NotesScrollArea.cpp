#include "NotesScrollArea.h"

#include <QEvent>
#include <QScrollBar>

NotesScrollArea::NotesScrollArea(QWidget *parent) : QGraphicsView(parent) {
    setRenderHint(QPainter::Antialiasing);

    viewMenu = new QMenu(this);

    verticalScrollBar()->installEventFilter(this);
    horizontalScrollBar()->installEventFilter(this);

    initLight();
}

NotesScrollArea::~NotesScrollArea() {
}

QRectF NotesScrollArea::viewportRect() const {
    QRect viewport_rect(0, 0, viewport()->width(), viewport()->height());
    QRectF visible_scene_rect = mapToScene(viewport_rect).boundingRect();
    return visible_scene_rect;
}

bool NotesScrollArea::eventFilter(QObject *obj, QEvent *event) {
    if (obj == verticalScrollBar() || obj == horizontalScrollBar()) {
        if (event->type() == QEvent::Wheel) {
            return true;
        }
    }
    // pass the event on to the parent class
    return QGraphicsView::eventFilter(obj, event);
}

void NotesScrollArea::initLight() {
    // NotesArea
    editor.quarterLine = QColor(0xD4D4D4);
    editor.timeLine = QColor(0xE2E2E2);
    editor.sectionLine = QColor(0xBFBFBF);
    editor.pitchLine = QColor(0xE6E6E6);
    editor.levelLine = QColor(0xCCCCCC);
    editor.backDark = QColor(0xF2F2F2);
    editor.backLight = QColor(0xFFFFFF);
    editor.playHead = Qt::black;

    // GraphicsNote
    note.lyric = Qt::black;
    note.restLine = QColor(0xCCCCCC);
    note.restFill = QColor(0xEEEEEE);
    note.listedLine = QColor(0x0099FF);
    note.listedFill = QColor(0x40D9FF);
    note.unlistedLine = QColor(0x105685);
    note.unlistedFill = QColor(0x1881C7);
    note.select = QColor(0, 0, 0, 48);

    // GraphicsRubber
    rubber.frame = Qt::black;
    rubber.fill = QColor(0, 0, 0, 120);

    // Mode2Handler
    mode1.solidLineEnabled = Qt::red;
    mode2.solidLineEnabled = Qt::red;

    mode1.dashLineEnabled = QColor(0xFF, 0, 0, 192);
    mode2.dashLineEnabled = QColor(0xFF, 0, 0, 192);

    mode1.solidLineDisabled = QColor(0xFF, 0x80, 0x80, 192);
    mode2.solidLineDisabled = QColor(0xFF, 0x80, 0x80, 192);

    mode1.dashLineDisabled = QColor(0xFF, 0x80, 0x80, 192);
    mode2.dashLineDisabled = QColor(0xFF, 0x80, 0x80, 192);

    mode2.invalidLineEnabled = QColor(0xFF, 0, 0, 72);
    mode2.invalidLineDisabled = QColor(0xFF, 0, 0, 30);

    vbr.curvesEnabled = mode2.solidLineEnabled;
    vbr.curvesDisabled = mode2.solidLineDisabled;

    vbr.editorLines = QColor(0x232323);

    mode2.pointCore = mode2.solidLineEnabled;
    mode2.pointRing = mode2.solidLineEnabled;

    // EnvelopeHandler
    env.solidLineEnabled = Qt::blue;
    env.dashLineEnabled = QColor(0, 0, 0xFF, 192);

    env.solidLineDisabled = QColor(0x80, 0x80, 0xFF, 192);
    env.dashLineDisabled = QColor(0x80, 0x80, 0xFF, 192);

    env.invalidLineEnabled = QColor(0, 0, 0xFF, 72);
    env.invalidLineDisabled = QColor(0, 0, 0xFF, 30);

    env.pointCore = Qt::blue;
    env.pointRing = Qt::blue;
}

void NotesScrollArea::initDark() {
    // NotesArea
    editor.quarterLine = QColor(0x161616);
    editor.timeLine = QColor(0x1C1C1C);
    editor.sectionLine = QColor(0x101010);
    editor.pitchLine = QColor(0x101010);
    editor.levelLine = QColor(0x191919);
    editor.backDark = QColor(0x232323);
    editor.backLight = QColor(0x2D2D2D);
    editor.playHead = Qt::white;

    // GraphicsNote
    note.lyric = Qt::white;
    note.restLine = QColor(0xCCCCCC);
    note.restFill = QColor(0xEEEEEE);
    note.listedLine = QColor(0x0099FF);
    note.listedFill = QColor(0x40D9FF);
    note.unlistedLine = QColor(0x105685);
    note.unlistedFill = QColor(0x1881C7);
    note.select = QColor(255, 255, 255, 48);

    // GraphicsRubber
    rubber.frame = QColor(255, 255, 255, 96);
    rubber.fill = QColor(255, 255, 255, 48);

    // Mode2Handler
    mode1.solidLineEnabled = QColor(255, 77, 77);
    mode2.solidLineEnabled = QColor(255, 77, 77);

    mode1.dashLineEnabled = QColor(255, 77, 77, 192);
    mode2.dashLineEnabled = QColor(255, 77, 77, 192);

    mode1.solidLineDisabled = QColor(255, 128, 128, 192);
    mode2.solidLineDisabled = QColor(255, 128, 128, 192);

    mode1.dashLineDisabled = QColor(255, 128, 128, 128);
    mode2.dashLineDisabled = QColor(255, 128, 128, 128);

    mode2.invalidLineEnabled = QColor(255, 77, 77, 72);
    mode2.invalidLineDisabled = QColor(255, 77, 77, 36);

    vbr.curvesEnabled = mode2.solidLineEnabled;
    vbr.curvesDisabled = mode2.solidLineDisabled;

    vbr.editorLines = Qt::yellow;

    mode2.pointCore = mode2.solidLineEnabled;
    mode2.pointRing = mode2.solidLineEnabled;

    // EnvelopeHandler
    env.solidLineEnabled = QColor(150, 216, 216);
    env.solidLineDisabled = QColor(150, 216, 216, 128);

    env.dashLineEnabled = QColor(150, 216, 216, 192);
    env.dashLineDisabled = QColor(150, 216, 216, 96);

    env.invalidLineEnabled = QColor(150, 216, 216, 72);
    env.invalidLineDisabled = QColor(150, 216, 216, 36);

    env.pointCore = env.solidLineEnabled;
    env.pointRing = env.solidLineEnabled;
}

QColor NotesScrollArea::editorQuarterLine() const {
    return editor.quarterLine;
}
QColor NotesScrollArea::editorTimeLine() const {
    return editor.timeLine;
}
QColor NotesScrollArea::editorSectionLine() const {
    return editor.sectionLine;
}
QColor NotesScrollArea::editorPitchLine() const {
    return editor.pitchLine;
}
QColor NotesScrollArea::editorLevelLine() const {
    return editor.levelLine;
}
QColor NotesScrollArea::editorBackDark() const {
    return editor.backDark;
}
QColor NotesScrollArea::editorBackLight() const {
    return editor.backLight;
}
QColor NotesScrollArea::editorPlayHead() const {
    return editor.playHead;
}
QColor NotesScrollArea::mode1SolidLineEnabled() const {
    return mode1.solidLineEnabled;
}
QColor NotesScrollArea::mode1SolidLineDisabled() const {
    return mode1.solidLineDisabled;
}
QColor NotesScrollArea::mode1DashLineEnabled() const {
    return mode1.dashLineEnabled;
}
QColor NotesScrollArea::mode1DashLineDisabled() const {
    return mode1.dashLineDisabled;
}
QColor NotesScrollArea::mode2SolidLineEnabled() const {
    return mode2.solidLineEnabled;
}
QColor NotesScrollArea::mode2SolidLineDisabled() const {
    return mode2.solidLineDisabled;
}
QColor NotesScrollArea::mode2DashLineEnabled() const {
    return mode2.dashLineEnabled;
}
QColor NotesScrollArea::mode2DashLineDisabled() const {
    return mode2.dashLineDisabled;
}
QColor NotesScrollArea::mode2InvalidLineEnabled() const {
    return mode2.invalidLineEnabled;
}
QColor NotesScrollArea::mode2InvalidLineDisabled() const {
    return mode2.invalidLineDisabled;
}
QColor NotesScrollArea::mode2PointCore() const {
    return mode2.pointCore;
}
QColor NotesScrollArea::mode2PointRing() const {
    return mode2.pointRing;
}
QColor NotesScrollArea::vbrCurvesEnabled() const {
    return vbr.curvesEnabled;
}
QColor NotesScrollArea::vbrCurvesDisabled() const {
    return vbr.curvesDisabled;
}
QColor NotesScrollArea::vbrEditorLines() const {
    return vbr.editorLines;
}
QColor NotesScrollArea::vbrPlaneHandleBorder() const {
    return vbr.planeHandleBorder;
}
QColor NotesScrollArea::vbrPlaneHandleFill() const {
    return vbr.planeHandleFill;
}
QColor NotesScrollArea::vbrPlaneHandleText() const {
    return vbr.planeHandleText;
}
QColor NotesScrollArea::envSolidLineEnabled() const {
    return env.solidLineEnabled;
}
QColor NotesScrollArea::envSolidLineDisabled() const {
    return env.solidLineDisabled;
}
QColor NotesScrollArea::envDashLineEnabled() const {
    return env.dashLineEnabled;
}
QColor NotesScrollArea::envDashLineDisabled() const {
    return env.dashLineDisabled;
}
QColor NotesScrollArea::envInvalidLineEnabled() const {
    return env.invalidLineEnabled;
}
QColor NotesScrollArea::envInvalidLineDisabled() const {
    return env.invalidLineDisabled;
}
QColor NotesScrollArea::envPointCore() const {
    return env.pointCore;
}
QColor NotesScrollArea::envPointRing() const {
    return env.pointRing;
}
QColor NotesScrollArea::noteLyric() const {
    return note.lyric;
}
QColor NotesScrollArea::noteRestFill() const {
    return note.restFill;
}
QColor NotesScrollArea::noteRestLine() const {
    return note.restLine;
}
QColor NotesScrollArea::noteListedFill() const {
    return note.listedFill;
}
QColor NotesScrollArea::noteListedLine() const {
    return note.listedLine;
}
QColor NotesScrollArea::noteUnlistedFill() const {
    return note.unlistedFill;
}
QColor NotesScrollArea::noteUnlistedLine() const {
    return note.unlistedLine;
}
QColor NotesScrollArea::noteSelect() const {
    return note.select;
}
QColor NotesScrollArea::rubberFrame() const {
    return rubber.frame;
}
QColor NotesScrollArea::rubberFill() const {
    return rubber.fill;
}

void NotesScrollArea::setEditorQuarterLine(const QColor &color) {
    editor.quarterLine = color;
    emit themeUpdated();
}
void NotesScrollArea::setEditorTimeLine(const QColor &color) {
    editor.timeLine = color;
    emit themeUpdated();
}
void NotesScrollArea::setEditorSectionLine(const QColor &color) {
    editor.sectionLine = color;
    emit themeUpdated();
}
void NotesScrollArea::setEditorPitchLine(const QColor &color) {
    editor.pitchLine = color;
    emit themeUpdated();
}
void NotesScrollArea::setEditorLevelLine(const QColor &color) {
    editor.levelLine = color;
    emit themeUpdated();
}
void NotesScrollArea::setEditorBackDark(const QColor &color) {
    editor.backDark = color;
    emit themeUpdated();
}
void NotesScrollArea::setEditorBackLight(const QColor &color) {
    editor.backLight = color;
    emit themeUpdated();
}
void NotesScrollArea::setEditorPlayHead(const QColor &color) {
    editor.playHead = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode1SolidLineEnabled(const QColor &color) {
    mode1.solidLineEnabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode1SolidLineDisabled(const QColor &color) {
    mode1.solidLineDisabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode1DashLineEnabled(const QColor &color) {
    mode1.dashLineEnabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode1DashLineDisabled(const QColor &color) {
    mode1.dashLineDisabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode2SolidLineEnabled(const QColor &color) {
    mode2.solidLineEnabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode2SolidLineDisabled(const QColor &color) {
    mode2.solidLineDisabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode2DashLineEnabled(const QColor &color) {
    mode2.dashLineEnabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode2DashLineDisabled(const QColor &color) {
    mode2.dashLineDisabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode2InvalidLineEnabled(const QColor &color) {
    mode2.invalidLineEnabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode2InvalidLineDisabled(const QColor &color) {
    mode2.invalidLineDisabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode2PointCore(const QColor &color) {
    mode2.pointCore = color;
    emit themeUpdated();
}
void NotesScrollArea::setMode2PointRing(const QColor &color) {
    mode2.pointRing = color;
    emit themeUpdated();
}
void NotesScrollArea::setVbrCurvesEnabled(const QColor &color) {
    vbr.curvesEnabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setVbrCurvesDisabled(const QColor &color) {
    vbr.curvesDisabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setVbrEditorLines(const QColor &color) {
    vbr.editorLines = color;
    emit themeUpdated();
}
void NotesScrollArea::setVbrPlaneHandleBorder(const QColor &color) {
    vbr.planeHandleBorder = color;
    emit themeUpdated();
}
void NotesScrollArea::setVbrPlaneHandleFill(const QColor &color) {
    vbr.planeHandleFill = color;
    emit themeUpdated();
}
void NotesScrollArea::setVbrPlaneHandleText(const QColor &color) {
    vbr.planeHandleText = color;
    emit themeUpdated();
}
void NotesScrollArea::setEnvSolidLineEnabled(const QColor &color) {
    env.solidLineEnabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setEnvSolidLineDisabled(const QColor &color) {
    env.solidLineDisabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setEnvDashLineEnabled(const QColor &color) {
    env.dashLineEnabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setEnvDashLineDisabled(const QColor &color) {
    env.dashLineDisabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setEnvInvalidLineEnabled(const QColor &color) {
    env.invalidLineEnabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setEnvInvalidLineDisabled(const QColor &color) {
    env.invalidLineDisabled = color;
    emit themeUpdated();
}
void NotesScrollArea::setEnvPointCore(const QColor &color) {
    env.pointCore = color;
    emit themeUpdated();
}
void NotesScrollArea::setEnvPointRing(const QColor &color) {
    env.pointRing = color;
    emit themeUpdated();
}
void NotesScrollArea::setNoteLyric(const QColor &color) {
    note.lyric = color;
    emit themeUpdated();
}
void NotesScrollArea::setNoteRestFill(const QColor &color) {
    note.restFill = color;
    emit themeUpdated();
}
void NotesScrollArea::setNoteRestLine(const QColor &color) {
    note.restLine = color;
    emit themeUpdated();
}
void NotesScrollArea::setNoteListedFill(const QColor &color) {
    note.listedFill = color;
    emit themeUpdated();
}
void NotesScrollArea::setNoteListedLine(const QColor &color) {
    note.listedLine = color;
    emit themeUpdated();
}
void NotesScrollArea::setNoteUnlistedFill(const QColor &color) {
    note.unlistedFill = color;
    emit themeUpdated();
}
void NotesScrollArea::setNoteUnlistedLine(const QColor &color) {
    note.unlistedLine = color;
    emit themeUpdated();
}
void NotesScrollArea::setNoteSelect(const QColor &color) {
    note.select = color;
    emit themeUpdated();
}
void NotesScrollArea::setRubberFrame(const QColor &color) {
    rubber.frame = color;
    emit themeUpdated();
}
void NotesScrollArea::setRubberFill(const QColor &color) {
    rubber.fill = color;
    emit themeUpdated();
}
