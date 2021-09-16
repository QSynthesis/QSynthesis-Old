#include "NotesArea.h"
#include "../../Interfaces/EditorInterface.h"
#include "../../Modules/Scrolls/NotesScrollArea.h"
#include "../../TuningGroup.h"
#include "mainwindow.h"

#include <QScrollBar>

NotesArea::NotesArea(EditorInterface *editor, NotesScrollArea *parent)
    : GraphicsArea(parent), m_view(parent) {
    m_ptrs = editor->ptrs();

    m_globalTempo = DEFAULT_VALUE_TEMPO;

    m_notesEnabled = true;
    m_pitchesEnabled = false;
    m_envelopesEnabled = false;

    m_moving = false;
    m_drawingItem = nullptr;

    initLyricModules();
    initSelectModules();
    initPlayModules();

    installEventFilter(this);

    connect(this, &QGraphicsScene::sceneRectChanged, this, &NotesArea::handleSceneRectChanged);

    updateColorTheme();
    connect(qTheme, &ColorTheme::updated, this, &NotesArea::updateColorTheme);
}

NotesArea::~NotesArea() {
}

void NotesArea::updateColorTheme() {
    m_timeLineColor = qTheme->editor_timeLine;
    m_quarterLineColor = qTheme->editor_quarterLine;
    m_sectionLineColor = qTheme->editor_sectionLine;
    m_pitchLineColor = qTheme->editor_pitchLine;
    m_levelLineColor = qTheme->editor_levelLine;
    m_backDarkColor = qTheme->editor_backDark;
    m_backLightColor = qTheme->editor_backLight;
    playHead->setBrush(qTheme->editor_playHead);

    updateBackground();
}

NotesScrollArea *NotesArea::view() const {
    return m_view;
}

void NotesArea::adjustSize() {
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

void NotesArea::centralizeVision(GraphicsNote *p) {
    centralizeVisionCore(p->y());
}

void NotesArea::centralizeVision(int index) {
    if (index >= NotesList.size() || index < 0) {
        centralizeVisionCore(46 * m_ptrs->currentHeight); // Centralize C4
        return;
    }
    centralizeVision(NotesList.at(index));
}

void NotesArea::showOnStage(QGraphicsRectItem *w, bool right) {
    QScrollBar *bar = m_view->horizontalScrollBar();
    QPoint q = m_view->mapFromScene(w->pos());

    if (q.x() < 0) {
        bar->setValue(w->x());
    } else if (q.x() + w->rect().width() > m_view->viewport()->width()) {
        if (right) {
            bar->setValue(w->x() + w->rect().width() - m_view->viewport()->width());
        } else {
            bar->setValue(w->x());
        }
    }
}

void NotesArea::showOnCenter(QGraphicsRectItem *w) {
    QScrollBar *bar = m_view->horizontalScrollBar();

    int vw = m_view->viewport()->width();
    bar->setValue(w->x() + w->rect().width() / 2 - vw / 2);
}

void NotesArea::selectNote(GraphicsNote *p) {
    qDragOut.removeAll();
    qDragOut.addOne(p);
    showOnStage(p, true);
}

void NotesArea::moveToStart() {
    if (NotesList.isEmpty()) {
        return;
    }
    showOnStage(NotesList.front());
}

void NotesArea::moveToEnd() {
    if (NotesList.isEmpty()) {
        return;
    }
    showOnStage(NotesList.back(), true);
}
