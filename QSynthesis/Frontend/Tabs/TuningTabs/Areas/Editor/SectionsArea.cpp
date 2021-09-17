#include "SectionsArea.h"
#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Interfaces/EditorInterface.h"
#include "../../TuningGroup.h"

SectionsArea::SectionsArea(EditorInterface *editor, QWidget *parent) : MoreWidget(parent) {
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
        currentNote->handleTempoTriggered();
    }
}

void SectionsArea::handleRemoveTempo() {
    if (currentNote) {
        currentNote->handleRemoveTempoTriggered();
    }
}

QColor SectionsArea::lineColor() const {
    return m_lineColor;
}

void SectionsArea::setLineColor(const QColor &lineColor) {
    m_lineColor = lineColor;
    update();

    emit colorChanged();
}

QColor SectionsArea::numColor() const {
    return m_numColor;
}

void SectionsArea::setNumColor(const QColor &numColor) {
    m_numColor = numColor;
    update();

    emit colorChanged();
}

QColor SectionsArea::beatColor() const {
    return m_beatColor;
}

void SectionsArea::setBeatColor(const QColor &beatColor) {
    m_beatColor = beatColor;
    update();

    emit colorChanged();
}

QColor SectionsArea::globalTempoColor() const {
    return m_globalTempoColor;
}

void SectionsArea::setGlobalTempoColor(const QColor &globalTempoColor) {
    m_globalTempoColor = globalTempoColor;
    update();

    emit colorChanged();
}

QColor SectionsArea::noteTempoColor() const {
    return m_noteTempoColor;
}

void SectionsArea::setNoteTempoColor(const QColor &noteTempoColor) {
    m_noteTempoColor = noteTempoColor;
    update();

    emit colorChanged();
}

void SectionsArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipRegion(event->region());

    QRect vision = event->region().boundingRect();
    NotesArea *notesArea = m_ptrs->notesArea;

    QPen pen(m_lineColor, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
    QPen pen2(m_numColor, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

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
    const QList<GraphicsNote *> &SNotesList = notesArea->NotesList;

    int absIndex = notesArea->absIndexAtPos(vision.x());
    int index = absIndex;
    while (index >= 0 && (index >= SNotesList.size() || !SNotesList.at(index)->tempoEdited())) {
        index--;
    }

    QPen firstPen;
    if (index < 0) {
        firstPen.setColor(m_globalTempoColor);
    } else {
        firstPen.setColor(m_noteTempoColor);
    }

    QVector<QPair<double, double>> tempos;
    tempos.push_back(qMakePair(vision.x(), notesArea->tempoAt(index)));

    for (int i = absIndex + 1; i < SNotesList.size(); ++i) {
        GraphicsNote *p = SNotesList.at(i);
        if (p->x() > vision.right()) {
            break;
        }
        if (p->tempoEdited()) {
            tempos.append(qMakePair(p->x(), p->tempo()));
        }
    }

    for (int i = 0; i < tempos.size(); ++i) {
        QPair<double, double> cur = tempos.at(i);

        double curX = cur.first;
        double nextX = (i == tempos.size() - 1) ? 0 : tempos.at(i + 1).first;
        QString tempoStr = QString::number(cur.second);

        QRect rect(curX, h, nextX + retract - curX, h);
        if (nextX == 0) {
            rect.setWidth(QFontMetrics(painter.font()).horizontalAdvance(tempoStr) + 2 * retract);
        }

        rect.adjust(retract, 0, -retract, 0);

        if (i == 0) {
            painter.setPen(firstPen);
        } else {
            painter.setPen(QPen(m_noteTempoColor));
        }
        painter.drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, tempoStr);
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
