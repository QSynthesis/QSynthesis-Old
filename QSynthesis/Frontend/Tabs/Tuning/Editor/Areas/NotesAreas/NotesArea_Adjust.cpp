#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::adjustNotes(QPoint range) {
    if (range.x() < 0 || range.x() >= NotesList.size()) {
        range.rx() = 0;
    }
    if (range.y() < 0 || range.y() >= NotesList.size()) {
        range.ry() = NotesList.size() - 1;
    }
    for (int i = range.x(); i <= range.y(); ++i) {
        NotesList.at(i)->adjustSize(false);
    }
    adjustNoteComponents(range);
}

void NotesArea::adjustNoteComponents(QPoint range) {
    if (range.x() < 0 || range.x() >= NotesList.size()) {
        range.rx() = 0;
    }
    if (range.y() < 0 || range.y() >= NotesList.size())  {
        range.ry() = NotesList.size() - 1;
    }
    for (int i = range.x(); i <= range.y(); ++i) {
        NotesList.at(i)->adjustCurves();
    }
    for (int i = range.x(); i <= range.y(); ++i) {
        NotesList.at(i)->adjustEnvelope();
    }
    for (int i = range.x(); i <= range.y(); ++i) {
        NotesList.at(i)->adjustLifter();
    }
}

QPoint NotesArea::selectContinuously(bool selectAll) {
    int min, max;

    if (!selectAll) {
        QPoint region = continuousSelection();
        min = region.x();
        max = region.y();
    } else {
        min = 0;
        max = NotesList.size() - 1;
    }
    if (min >= 0) {
        for (int i = min; i <= max; ++i) {
            if (!NotesList.at(i)->isSelected()) {
                qDragOut.addOne(NotesList.at(i));
            }
        }
    }

    return QPoint(min, max);
}

QPoint NotesArea::selectRange(QPoint range) {
    if (range.x() >= NotesList.size() || range.y() < range.x()) {
        return QPoint(-1, -1);
    }
    if (range.y() >= NotesList.size()) {
        range.ry() = NotesList.size() - 1;
    }

    qDragOut.removeAll();
    for (int i = range.x(); i <= range.y(); ++i) {
        qDragOut.addOne(NotesList.at(i));
    }
    return range;
}

QPoint NotesArea::selectSequence(const QList<int> &indexs) {
    if (indexs.isEmpty()) {
        return QPoint(-1, -1);
    }
    int min = indexs.front();
    int max = indexs.back();

    qDragOut.removeAll();
    for (int i = 0; i < indexs.size(); ++i) {
        int cur = indexs.at(i);
        if (cur >= 0 && cur < NotesList.size()) {
            min = (min > cur) ? cur : min;
            max = (max < cur) ? cur : max;
            qDragOut.addOne(NotesList.at(cur));
        }
    }
    return QPoint(min, max);
}
