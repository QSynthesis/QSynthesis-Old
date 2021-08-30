#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::updateNoteTickAfter(int index) {
    if (index >= NotesList.size() || NotesList.isEmpty()) {
        return;
    }
    if (index < 0) {
        NotesList.front()->setTick(0);
        index = 0;
    }
    GraphicsNote *p = NotesList[index];
    // Update tick
    for (GraphicsNote *it = p->next(); it; it = it->next()) {
        it->setTick(it->prev()->tick() + it->prev()->Note.length);
    }
    updateNoteTimeAfter(index);
}

void NotesArea::updateNoteTimeAfter(int index) {
    if (index >= NotesList.size() || NotesList.isEmpty()) {
        return;
    }
    if (index < 0) {
        index = 0;
        NotesList.front()->setTime(0);
    }
    GraphicsNote *p = NotesList[index];
    // Update time
    for (GraphicsNote *it = p->next(); it; it = it->next()) {
        it->setTime(it->prev()->time() + it->prev()->duration());
        it->updateCorrectGenon();
    }
}

int NotesArea::updateNoteTempoAfter(int index, bool br) {
    if (index < 0) {
        index = -1;
    }
    if (index >= NotesList.size()) {
        return -1;
    }
    // Update tick
    int i;
    for (i = index + 1; i < NotesList.size(); ++i) {
        if (NotesList.at(i)->tempoEdited()) {
            if (br) {
                break;
            } else {
                continue;
            }
        }
        NotesList.at(i)->setTempo(tempoAt(i - 1));
        NotesList.at(i)->updateCorrectGenon();
    }

    return i;
}

void NotesArea::updateNotesStatus(QPoint range) {
    if (range.x() < 0 || range.x() >= NotesList.size()) {
        range.rx() = 0;
    }
    if (range.y() < 0 || range.y() >= NotesList.size()) {
        range.ry() = NotesList.size() - 1;
    }
    for (int i = range.x(); i <= range.y(); ++i) {
        NotesList[i]->updateNoteStatus();
    }
}
