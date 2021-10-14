#include "NotesArea.h"
#include "../../Scrolls/NotesScrollArea.h"
#include "../../TuningGroup.h"
#include "../EditorInterface.h"
#include "SettingIniFile.h"
#include "application.h"

#include <QScrollBar>

NotesArea::NotesArea(EditorInterface *editor, NotesScrollArea *view) : GraphicsArea(view) {
    m_ptrs = editor->ptrs();

    m_globalTempo = DEFAULT_VALUE_TEMPO;

    m_notesEnabled = true;
    m_pitchesEnabled = false;
    m_envelopesEnabled = false;

    m_notesVisible = qSetting->noteVisibility;
    m_pitchesVisible = qSetting->pitchVisibility;
    m_envelopesVisible = qSetting->envelopeVisibility;
    m_paramsVisible = qSetting->paramsVisibility;

    m_playHeadOnCenter = qSetting->playHeadCenter;

    m_spriteVisible = qSetting->spriteVisibility;
    m_spritePosition = qSetting->spritePosition;

    m_finding = false;

    m_moving = false;
    m_selecting = false;
    m_drawingItem = nullptr;

    initLyricModules();
    initSelectModules();
    initPlayModules();

    connect(this, &QGraphicsScene::sceneRectChanged, this, &NotesArea::handleSceneRectChanged);

    updateColorTheme();
    connect(view, &NotesScrollArea::editorThemeUpdated, this, &NotesArea::updateColorTheme);

    initSpriteModules();
    setSpriteAlpha(qSetting->spriteOpacity);
}

NotesArea::~NotesArea() {
}

NotesScrollArea *NotesArea::view() const {
    return qobject_cast<NotesScrollArea *>(m_view);
}

void NotesArea::updateColorTheme() {
    m_timeLineColor = view()->editorTimeLine();
    m_quarterLineColor = view()->editorQuarterLine();
    m_sectionLineColor = view()->editorSectionLine();
    m_pitchLineColor = view()->editorPitchLine();
    m_levelLineColor = view()->editorLevelLine();
    m_backDarkColor = view()->editorBackDark();
    m_backLightColor = view()->editorBackLight();
    playHead->setBrush(view()->editorPlayHead());

    updateBackground();
}

void NotesArea::adjustSize() {
    m_view->stopTween();
    setSceneRect(QRectF(0, 0, m_ptrs->currentWidth * 4 * (m_ptrs->currentSections + 1),
                        m_ptrs->currentHeight * 84));
    adjustNotes();
    adjustPlayHead();
}

void NotesArea::updateBackground() {
    int curWidth = m_ptrs->currentWidth;
    int curHeight = m_ptrs->currentHeight;
    int curAdsorb = m_ptrs->currentAdsorb * 4;

    double lineWidth = 1;

    const QSet<short> deep{1, 3, 5, 8, 10};

    // Draw Background Unit
    double totalWidth = curWidth * 4;
    double totalHeight = curHeight * 12;

    if (totalWidth == 0 || totalHeight == 0) {
        return;
    }

    QPixmap pixmap(totalWidth, totalHeight);

    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.translate(0, 0);

    for (int i = 0; i < 12; ++i) {
        painter.setBrush((deep.contains(i % 12)) ? m_backDarkColor : m_backLightColor);
        painter.drawRect(QRectF(0, i * curHeight, totalWidth, curHeight));
    }

    double w = (curAdsorb == 0) ? Q_INFINITY : (totalWidth / curAdsorb);
    while (w < 6 && curAdsorb > 1) {
        curAdsorb--;
        while (curAdsorb % 4 != 0 && curAdsorb > 1) {
            curAdsorb--;
        }
        w = totalWidth / curAdsorb;
    }
    for (int i = 1; i < curAdsorb; ++i) {
        if ((i * 4) % curAdsorb == 0) {
            painter.setBrush(m_quarterLineColor);
        } else {
            painter.setBrush(m_timeLineColor);
        }
        painter.drawRect(QRectF(w * i - lineWidth / 2, 0, lineWidth, totalHeight));
    }

    painter.setBrush(m_sectionLineColor);
    painter.drawRect(QRectF(0, 0, lineWidth / 2, totalHeight));
    painter.drawRect(QRectF(totalWidth - lineWidth / 2, 0, lineWidth / 2, totalHeight));

    painter.setBrush(m_levelLineColor);
    painter.drawRect(QRectF(0, 0, totalWidth, lineWidth / 2));
    painter.drawRect(QRectF(0, totalHeight - lineWidth / 2, totalWidth, lineWidth / 2));

    painter.setBrush(m_pitchLineColor);
    painter.drawRect(QRectF(0, curHeight * 7 - lineWidth / 2, totalWidth, lineWidth));

    setBackgroundBrush(pixmap);
}

void NotesArea::handleSceneRectChanged(const QRectF &rect) {
    updateBackground();
}

void NotesArea::centralizeVision(GraphicsNote *p, bool animate) {
    setVisionFitToPos(p->y(), Qt::AnchorVerticalCenter, animate);
}

void NotesArea::centralizeVision(int index, bool animate) {
    if (index >= NotesList.size() || index < 0) {
        // Centralize C4
        setVisionFitToPos(46 * m_ptrs->currentHeight, Qt::AnchorVerticalCenter, animate);
        return;
    }
    centralizeVision(NotesList.at(index), animate);
}

void NotesArea::selectNote(GraphicsNote *p, bool single) {
    if (single) {
        qDragOut.removeAll();
        qDragOut.addOne(p);
    }
    QRectF vp = viewportRect();
    if (p->width() < vp.width()) {
        setVisionFitToItem(p, Qt::Horizontal | Qt::Vertical, true);
    } else if (p->x() < vp.left() || p->x() > vp.right()) {
        setVisionFitToItem(p, Qt::AnchorLeft, true);
        setVisionFitToItem(p, Qt::Vertical, true);
    }
}

void NotesArea::moveToStart() {
    if (NotesList.isEmpty()) {
        return;
    }
    GraphicsNote *p = NotesList.front();
    setVisionFitToItem(p, Qt::AnchorLeft, true);
    setVisionFitToItem(p, Qt::Vertical, true);
}

void NotesArea::moveToEnd() {
    if (NotesList.isEmpty()) {
        return;
    }
    GraphicsNote *p = NotesList.back();
    setVisionFitToItem(p, Qt::AnchorRight, true);
    setVisionFitToItem(p, Qt::Vertical, true);
}
