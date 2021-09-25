#include "NotesScrollArea.h"
#include "../Areas/Editor/NotesArea.h"

#include <QEvent>
#include <QScrollBar>

NotesScrollArea::NotesScrollArea(QWidget *parent) : GraphicsBaseView(parent) {
    setRenderHint(QPainter::Antialiasing);

    installEventFilter(this);
    verticalScrollBar()->installEventFilter(this);
    horizontalScrollBar()->installEventFilter(this);

    initLight();

    adjuster = new SpriteAdjustDialog(this);

    connect(adjuster, &SpriteAdjustDialog::visibilityChanged, this,
            &NotesScrollArea::handleVisibilityChanged);
    connect(adjuster, &SpriteAdjustDialog::alphaChanged, this,
            &NotesScrollArea::handleAlphaChanged);
    connect(adjuster, &SpriteAdjustDialog::cornerChanged, this,
            &NotesScrollArea::handleCornerChanged);
    connect(adjuster, &SpriteAdjustDialog::closeRequested, this,
            &NotesScrollArea::handleAdjusterCloseRequested);

    adjuster->hide();
    adjustModules();
}

NotesScrollArea::~NotesScrollArea() {
}

void NotesScrollArea::setAdjusterVisible(bool visible) {
    if (visible) {
        adjuster->setVisibility(scene() ? scene()->spriteVisible() : false);
        adjuster->setAlpha(scene() ? int(scene()->spriteAlpha() * 100) : 0);
        adjuster->setCorner(scene() ? scene()->spritePosition() : Qt::BottomRightCorner);

        adjuster->setEnabled(true);
        adjuster->setFocus();
    } else {
        adjuster->setEnabled(false);
    }
    adjuster->setVisible(visible);
    adjustModules();
}

bool NotesScrollArea::adjusterVisible() const {
    return adjuster->isVisible();
}

NotesArea *NotesScrollArea::scene() const {
    return qobject_cast<NotesArea *>(GraphicsBaseView::scene());
}

void NotesScrollArea::adjustModules() {
    if (adjuster->isVisible()) {
        adjuster->move(20, 0);
    }
}

void NotesScrollArea::handleVisibilityChanged(bool visible) {
    if (scene()) {
        scene()->setSpriteVisible(visible);
    }
}

void NotesScrollArea::handleAlphaChanged(int alpha) {
    if (scene()) {
        scene()->setSpriteAlpha(double(alpha) / 100);
    }
}

void NotesScrollArea::handleCornerChanged(Qt::Corner corner) {
    if (scene()) {
        scene()->setSpritePosition(corner);
    }
}

void NotesScrollArea::handleAdjusterCloseRequested() {
    setAdjusterVisible(false);
}

void NotesScrollArea::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (adjuster->isVisible()) {
            setAdjusterVisible(false);
            return;
        }
    }
    return GraphicsBaseView::keyPressEvent(event);
}

void NotesScrollArea::keyReleaseEvent(QKeyEvent *event) {
    return GraphicsBaseView::keyReleaseEvent(event);
}

void NotesScrollArea::resizeEvent(QResizeEvent *event) {
    if (event->oldSize().width() != event->size().width()) {
        adjustModules();
    }
}

bool NotesScrollArea::eventFilter(QObject *obj, QEvent *event) {
    if (obj == verticalScrollBar() || obj == horizontalScrollBar()) {
        if (event->type() == QEvent::Wheel) {
            return true;
        }
    }
    // pass the event on to the parent class
    return GraphicsBaseView::eventFilter(obj, event);
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
    note.lyricBlock = Qt::white;
    note.params = Qt::darkGray;

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
    note.lyricBlock = Qt::white;
    note.params = Qt::lightGray;

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
