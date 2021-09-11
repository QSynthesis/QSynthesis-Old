#include "../../../Interfaces/TracksInterface.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::initPlayModules() {
    playHead = new GraphicsPlayHead();
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

    int start = m_renderRange.x();
    int end = m_renderRange.y();
    double startTime = NotesList[start]->time();

    playToPosition = position;
    position -= NotesList[start]->correctGenon().PreUtterance;
    if (position < 0) {
        position = 0;
    }

    // 将 m_playToNote 位置确定
    if (playToNote < start) {
        playToNote = start;
    }
    if (playToNote > end) {
        playToNote = end;
    }

    // 调整范围
    while (playToNote <= end && NotesList[playToNote]->endTime() - startTime < position) {
        playToNote++;
    }

    // 不能超过范围
    if (playToNote > qMin(end + 1, NotesList.size() - 1)) {
        qDebug() << "Over line.";
        playHead->hide();
        return;
    }

    while (playToNote >= start && NotesList[playToNote]->time() - startTime > position) {
        playToNote--;
    }

    // 不能小于范围
    if (playToNote < start) {
        playHead->hide();
        return;
    }

    // 减掉第一个音符的先行声音
    double unit = 120.0 / NotesList[playToNote]->tempo() / 0.96;
    double ticks = (position + startTime - NotesList[playToNote]->time()) / unit / 480 * unit_w;

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

void NotesArea::jumpPlaying(double x) {
    int start = m_renderRange.x();
    int end = m_renderRange.y();

    int index = findNoteAtPos(x);
    if (index > end) {
        return;
    }
    if (index < start) {
        index = start;
    }

    GraphicsNote *startNote = NotesList.at(start);
    double startTime = startNote->time();

    GraphicsNote *p = NotesList.at(index);
    double realTime = p->time() - startTime + (x - p->x()) / p->width() * p->duration();
    double position = realTime + startNote->correctGenon().PreUtterance;

    m_ptrs->tab->jump(position);
}
