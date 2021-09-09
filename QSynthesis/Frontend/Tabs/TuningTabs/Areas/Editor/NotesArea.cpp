#include "NotesArea.h"
#include "../../Interfaces/EditorInterface.h"
#include "../../Modules/Scrolls/NotesScrollArea.h"
#include "../../TuningGroup.h"

#include <QScrollBar>

NotesArea::NotesArea(EditorInterface *editor, NotesScrollArea *parent)
    : QGraphicsScene(parent), m_view(parent) {
    m_ptrs = editor->ptrs();

    m_notesEnabled = true;
    m_pitchesEnabled = false;
    m_envelopesEnabled = false;

    m_moving = false;
    m_drawingItem = nullptr;

    // Colors
    m_timeLineColor = QColor(0xD4D4D4);
    m_sectionLineColor = QColor(0xBFBFBF);
    m_pitchLineColor = QColor(0xE6E6E6);
    m_levelLineColor = QColor(0xCCCCCC);
    m_backDarkColor = QColor(0xF2F2F2);
    m_backLightColor = QColor(0xFFFFFF);

    initLyricModules();
    initSelectModules();
    initPlayModules();

    installEventFilter(this);

    connect(this, &QGraphicsScene::sceneRectChanged, this, &NotesArea::handleSceneRectChanged);
}

NotesArea::~NotesArea() {
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

    double w = totalWidth / curAdsorb;
    while (w < 6) {
        curAdsorb--;
        w = totalWidth / curAdsorb;
    }
    for (int i = 1; i < curAdsorb; ++i) {
        painter.setBrush(m_timeLineColor);
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
