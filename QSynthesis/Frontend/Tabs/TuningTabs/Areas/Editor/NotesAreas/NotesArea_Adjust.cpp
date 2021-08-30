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
        NotesList[i]->adjustSize(false);
    }
    adjustNoteComponents(range);
}

void NotesArea::adjustNoteComponents(QPoint range) {
    if (range.x() < 0 || range.x() >= NotesList.size()) {
        range.rx() = 0;
    }
    if (range.y() < 0 || range.y() >= NotesList.size()) {
        range.ry() = NotesList.size() - 1;
    }
    for (int i = range.x(); i <= range.y(); ++i) {
        NotesList[i]->adjustCurves();
    }
    for (int i = range.x(); i <= range.y(); ++i) {
        NotesList[i]->adjustEnvelope();
    }
    for (int i = range.x(); i <= range.y(); ++i) {
        NotesList[i]->adjustLifter();
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
            if (!NotesList[i]->isSelected()) {
                qDragOut.addOne(NotesList[i]);
            }
        }
    }

    return QPoint(min, max);
}
