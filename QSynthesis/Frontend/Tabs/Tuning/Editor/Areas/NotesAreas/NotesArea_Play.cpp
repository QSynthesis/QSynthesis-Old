#include "../../../Scrolls/NotesScrollArea.h"
#include "../../../Tracks/TracksInterface.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::initPlayModules() {
    playHead = new GraphicsPlayHead();
    addItem(playHead);

    playHead->setPen(Qt::NoPen);
    playHead->setZValue(playHeadZIndex);

    m_playToNote = 0;
    m_playToPosition = 0;
    m_playToTick = 0;

    playHead->setPos(0, 0);
    playHead->setAlwaysShow(true);
    playHead->setPlaying(false);

    adjustPlayHead();
}

void NotesArea::adjustPlayHead() {
    if (playHead->rect().height() != sceneRect().height()) {
        playHead->setRect(-1, 0, 2, sceneRect().height());
    }
    playHead->setPos(m_playToTick / 480 * m_ptrs->currentWidth + zeroLine(), 0);
}

void NotesArea::advancePlayHead() {
    // position /= 1000; // USec -> MSec

    int start = 0;
    int end = NotesList.size() - 1;
    double startTime = NotesList.at(start)->time();

    // qint64 position = m_playToPosition - NotesList.at(start)->correctGenon().PreUtterance;
    qint64 position = m_playToPosition;
    int realPos = position;
    if (position < 0) {
        position = 0;
    }

    // 将 m_playToNote 位置确定
    if (m_playToNote < start) {
        m_playToNote = start;
    }
    if (m_playToNote > end) {
        m_playToNote = end;
    }

    // 调整范围
    while (m_playToNote <= end && NotesList.at(m_playToNote)->endTime() - startTime < position) {
        m_playToNote++;
    }

    // 不能超过范围
    if (m_playToNote > qMin(end + 1, NotesList.size() - 1)) {
        // qDebug() << "Over line.";
        playHead->setPlaying(false);
        return;
    }

    while (m_playToNote >= start && NotesList.at(m_playToNote)->time() - startTime > position) {
        m_playToNote--;
    }

    // 不能小于范围
    if (m_playToNote < start) {
        playHead->setPlaying(false);
        return;
    }

    // 减掉第一个音符的先行声音
    double unit = 120.0 / tempoAt(realPos < 0 ? (m_playToNote - 1) : m_playToNote) / 0.96;
    double ticks = (realPos + startTime - NotesList.at(m_playToNote)->time()) / unit;
    double width = ticks / 480 * m_ptrs->currentWidth;

    if (!playHead->playing()) {
        playHead->setPlaying(true);
    }

    GraphicsNote *p = NotesList.at(m_playToNote);
    playHead->setPos(p->x() + width, playHead->y());

    m_playToTick = p->tick() + ticks;

    QRectF vp = viewportRect();
    if (m_playHeadOnCenter) {
        setVisionFitToItem(playHead, Qt::AnchorHorizontalCenter);
    } else {
        if (playHead->left() < vp.left() || playHead->right() > vp.right()) {
            setVisionFitToItem(playHead, Qt::AnchorLeft);
        }
    }
}

void NotesArea::advancePlaying(qint64 position) {
    m_playToPosition = position;
    advancePlayHead();
    if (!playHead->playing()) {
        return;
    }

    QRectF viewportRect = m_view->viewportRect();
    GraphicsNote *p = NotesList.at(m_playToNote);

    int y1 = p->y();
    int y2 = y1 + p->height();

    if (y1 < viewportRect.top()) {
        setVisionFitToItem(p, Qt::AnchorTop, true);
    } else if (y2 > viewportRect.bottom()) {
        setVisionFitToItem(p, Qt::AnchorBottom, true);
    }
}

void NotesArea::stopPlaying() {
    m_playToNote = 0;
    m_playToPosition = 0;
    playHead->setPlaying(false);
}

void NotesArea::setPlayPosition(double x) {
    if (!isPlaying()) {
        int tick = convertPositionToValue(QPoint(x, 0)).first;
        if (tick < 0) {
            tick = 0;
        }
        m_playToTick = tick;
        adjustPlayHead();
        callForPlayback();
    }
}
