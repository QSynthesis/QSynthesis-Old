#include "SectionsArea.h"
#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Interfaces/EditorInterface.h"
#include "../../TuningGroup.h"

SectionsArea::SectionsArea(EditorInterface *editor, QWidget *parent) : QWidget(parent) {
    m_ptrs = editor->ptrs();

    setBeat(4, 4);

    m_lineColor = Qt::lightGray;
    m_numColor = Qt::black;
    m_beatColor = Qt::black;

    m_noteTempoColor = Qt::red;
    m_globalTempoColor = Qt::black;

    m_menu = new QMenu(this);
    currentNote = nullptr;
}

SectionsArea::~SectionsArea() {
}

TuningGroup *SectionsArea::ptrs() const {
    return m_ptrs;
}

QPoint SectionsArea::beat() const {
    return m_beat;
}

void SectionsArea::setBeat(const QPoint &beat) {
    m_beat = beat;
    update();
}

void SectionsArea::setBeat(int num, int den) {
    setBeat(QPoint(num, den));
}

void SectionsArea::adjustWidth() {
    setFixedWidth((m_ptrs->currentSections + 1) * 4 * m_ptrs->currentWidth);
}

void SectionsArea::handleModifyGlobalTempo() {
    qDragOut.removeAll();
    m_ptrs->tab->showTempoEdit();
}

void SectionsArea::handleModifyTempo() {
    if (currentNote) {
        currentNote->handler()->handleTempoTriggered();
    }
}

void SectionsArea::handleRemoveTempo() {
    if (currentNote) {
        currentNote->handler()->handleRemoveTempoTriggered();
    }
}

void SectionsArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipRegion(event->region());

    QPen pen(m_lineColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen2(m_numColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QRect rect = this->rect();
    int h = rect.height() / 2;

    int i, j, k;

    int retract = 5;

    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawLine(QPoint(rect.left(), rect.center().y()),
                     QPoint(rect.right(), rect.center().y()));

    int curX;

    int startSemiquavers = -1 * 16;
    int maxSemiquavers = m_ptrs->currentSections * 16;
    int unit = 16 / m_beat.y();

    double zeroX = (-startSemiquavers / 16) * 4 * m_ptrs->currentWidth;
    double unitX = m_ptrs->currentWidth * 4 / unit;

    QRectF rectTop, rectHalfTop, rectText;

    rectTop.setTop(0);
    rectTop.setBottom(rect.center().y());

    rectHalfTop.setTop(rectTop.center().y());
    rectHalfTop.setBottom(rectTop.bottom());

    rectText = rectTop;

    j = 0;
    k = 0;
    for (i = 0; i >= startSemiquavers; i -= unit) {
        curX = zeroX - j * unitX;

        if (j % m_beat.x() == 0) {
            painter.setPen(pen);
            painter.drawLine(QPointF(curX, rectTop.top()), QPointF(curX, rectTop.bottom()));

            rectText.setLeft(curX);
            rectText.setWidth(unitX * m_beat.x());
            rectText.adjust(retract, 0, -retract, 0);
            painter.setPen(pen2);
            painter.drawText(rectText, Qt::AlignVCenter | Qt::AlignLeft, QString::number(-k));
            k++;
        } else {
            painter.setPen(pen);
            painter.drawLine(QPointF(curX, rectHalfTop.top()), QPointF(curX, rectHalfTop.bottom()));
        }
        j++;
    }

    j = 0;
    k = 0;
    for (i = unit; i <= maxSemiquavers; i += unit) {
        curX = zeroX + j * unitX;

        if (j % m_beat.x() == 0) {
            painter.setPen(pen);
            painter.drawLine(QPointF(curX, rectTop.top()), QPointF(curX, rectTop.bottom()));

            rectText.setLeft(curX);
            rectText.setWidth(unitX * m_beat.x());
            rectText.adjust(retract, 0, -retract, 0);
            painter.setPen(pen2);
            painter.drawText(rectText, Qt::AlignVCenter | Qt::AlignLeft, QString::number(k));
            k++;
        } else {
            painter.setPen(pen);
            painter.drawLine(QPointF(curX, rectHalfTop.top()), QPointF(curX, rectHalfTop.bottom()));
        }
        j++;
    }

    // Draw Tempo
    const QList<GraphicsNote *> &SNotesList = m_ptrs->notesArea->NotesList;
    painter.setPen(m_globalTempoColor);

    {
        QRect rect(0, h, m_ptrs->currentWidth * 4, h);
        rect.adjust(retract, 0, -retract, 0);
        painter.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft,
                         QString::number(m_ptrs->notesArea->globalTempo()));
        painter.setPen(m_noteTempoColor);
        for (int i = 0; i < SNotesList.size(); ++i) {
            GraphicsNote *p = SNotesList.at(i);
            QRect rect(p->x(), h, p->width(), h);
            rect.adjust(retract, 0, -retract, 0);
            if (p->tempoEdited()) {
                painter.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft,
                                 QString::number(p->tempo()));
            }
        }
    }
}

void SectionsArea::contextMenuEvent(QContextMenuEvent *event) {
    QAction *globalTempoAction = new QAction(tr("Set Global Tempo..."), m_menu);
    QAction *tempoAction = new QAction(tr("Set Tempo here..."), m_menu);
    QAction *removeTempoAction = new QAction(tr("Remove Tempo"), m_menu);

    m_menu->addAction(globalTempoAction);
    m_menu->addAction(tempoAction);
    m_menu->addAction(removeTempoAction);

    connect(globalTempoAction, &QAction::triggered, this, &SectionsArea::handleModifyGlobalTempo);
    connect(tempoAction, &QAction::triggered, this, &SectionsArea::handleModifyTempo);
    connect(removeTempoAction, &QAction::triggered, this, &SectionsArea::handleRemoveTempo);

    const QList<GraphicsNote *> &SNotesList = m_ptrs->notesArea->NotesList;
    int x = event->pos().x();
    GraphicsNote *p = nullptr;

    if (SNotesList.isEmpty() || x < SNotesList.front()->x()) {
    } else if (x < SNotesList.back()->x() + SNotesList.back()->width()) {
        int pos = m_ptrs->notesArea->findNoteAtPos(x);
        p = SNotesList[pos];
    } else {
        return;
    }

    if (p) {
        globalTempoAction->setVisible(false);
        tempoAction->setVisible(true);
        removeTempoAction->setVisible(true);
        removeTempoAction->setEnabled(p->tempoEdited());
    } else {
        globalTempoAction->setVisible(true);
        tempoAction->setVisible(false);
        removeTempoAction->setVisible(false);
    }
    currentNote = p;

    m_menu->exec(QCursor::pos());
    event->accept();

    m_menu->clear();
}
