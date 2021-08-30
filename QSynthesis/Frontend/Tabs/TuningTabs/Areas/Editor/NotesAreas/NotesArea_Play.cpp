#include "../../../Interfaces/TracksInterface.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::initPlayModules() {
    playHead = new QGraphicsRectItem();
    addItem(playHead);

    playHead->setZValue(playHeadZIndex);
    playHead->setBrush(Qt::black);

    playToNote = 0;
    playToPosition = 0;

    playHead->setPos(0, 0);
    playHead->hide();

    adjustPlayHead();
}

void NotesArea::adjustPlayHead() {
    playHead->setRect(-0.5, 0, 1, sceneRect().height());
    if (playHead->isVisible()) {
        advancePlaying(playToPosition);
    }
}

void NotesArea::advancePlaying(qint64 position) {
    double unit_w = m_ptrs->currentWidth;

    // position /= 1000; // USec -> MSec

    playToPosition = position;
    position -= NotesList[m_renderRange.x()]->correctGenon().PreUtterance;
    if (position < 0) {
        position = 0;
    }

    // 将 m_playToNote 位置确定
    if (playToNote < m_renderRange.x()) {
        playToNote = m_renderRange.x();
    }
    if (playToNote > m_renderRange.y()) {
        playToNote = m_renderRange.y();
    }

    // 调整范围
    while (playToNote <= m_renderRange.y() && NotesList[playToNote]->time() +
                                                        NotesList[playToNote]->duration() -
                                                        NotesList[m_renderRange.x()]->time() <
                                                    position) {
        playToNote++;
    }

    // 不能超过范围
    if (playToNote > qMin(m_renderRange.y() + 1, NotesList.size() - 1)) {
        qDebug() << "Over line.";
        playHead->hide();
        return;
    }

    while (playToNote >= m_renderRange.x() &&
           NotesList[playToNote]->time() - NotesList[m_renderRange.x()]->time() > position) {
        playToNote--;
    }

    // 不能小于范围
    if (playToNote < m_renderRange.x()) {
        playHead->hide();
        return;
    }

    // 减掉第一个音符的先行声音
    double unit = 120.0 / NotesList[playToNote]->tempo() / 0.96;
    double ticks =
        (position + NotesList[m_renderRange.x()]->time() - NotesList[playToNote]->time()) / unit /
        480 * unit_w;

    if (!playHead->isVisible()) {
        playHead->show();
    }

    playHead->setPos(NotesList[playToNote]->x() + ticks, playHead->y());

    showOnStage(playHead);
}

void NotesArea::stopPlaying() {
    playToNote = 0;
    playToPosition = 0;
    playHead->setVisible(false);
}
