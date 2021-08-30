#include "../../../Operations/SequenceOperation.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

GraphicsNote *NotesArea::insertNote(int index, const QLinkNote &note) {
    return insertNotes({index}, {note});
}

GraphicsNote *NotesArea::appendNote(const QLinkNote &note) {
    GraphicsNote *p = createNoteCore(note);
    if (!NotesList.isEmpty()) {
        // Update tick
        p->setTick(NotesList.back()->tick() + NotesList.back()->Note.length);
        p->setTime(NotesList.back()->time() + NotesList.back()->duration());

        NotesList.back()->setNext(p);
        p->setPrev(NotesList.back());
    } else {
        p->setTick(0);
        p->setTime(0);
    }
    // Update Tempo
    if (!p->tempoEdited()) {
        p->setTempo(tempoAt(NotesList.size() - 1));
    } else {
        p->setTempo(p->Note.tempo);
    }
    NotesList.append(p);
    return p;
}

GraphicsNote *NotesArea::insertNotes(const QList<int> &indexs, const QList<QLinkNote> &notes) {
    int frontIndex = 0;
    int tempoEditIndex = -1;
    GraphicsNote *frontNote = nullptr;

    if (notes.isEmpty()) {
        return nullptr;
    }

    for (int i = 0; i < notes.size(); ++i) {
        int index = (i < indexs.size()) ? indexs.at(i) : NotesList.size();
        const QLinkNote &note = notes.at(i);

        if (index < 0) {
            index = 0;
        }
        GraphicsNote *p;
        if (index >= NotesList.size()) {
            p = appendNote(note);
        } else {
            p = createNoteCore(note);

            if (index == 0) {
                GraphicsNote *next = NotesList[index];
                NotesList.prepend(p);

                p->setNext(next);
                next->setPrev(p);

                p->setTick(0);
                p->setTime(0);
            } else {
                GraphicsNote *prev = NotesList[index - 1];
                GraphicsNote *next = NotesList[index];
                NotesList.insert(index, p);

                prev->setNext(p);
                next->setPrev(p);

                p->setNext(next);
                p->setPrev(prev);

                // Update tick
                p->setTick(prev->tick() + prev->Note.length);
                p->setTime(prev->time() + prev->duration());
            }

            // Update Tempo
            if (!p->tempoEdited()) {
                p->setTempo(tempoAt(index - 1));
            } else {
                p->setTempo(p->Note.tempo);
                if (tempoEditIndex < 0) {
                    tempoEditIndex = index;
                }
            }
        }

        if (i == 0) {
            frontIndex = index;
            frontNote = p;
        }
    }

    // Update tick
    if (tempoEditIndex >= 0) {
        updateNoteTempoAfter(tempoEditIndex);
    }
    updateNoteTickAfter(frontIndex);

    return frontNote;
}

void NotesArea::removeNote(int index) {
    removeNotes({index});
}

void NotesArea::removeNote(GraphicsNote *p) {
    removeNote(NotesList.findAuto(p));
}

void NotesArea::removeNotes(const QList<int> &indexs) {
    for (int i = indexs.size() - 1; i >= 0; i--) {
        int index = indexs.at(i);
        GraphicsNote *c = NotesList.at(index);
        if (index < 0 || index > NotesList.size() - 1) {
            break;
        }
        if (index == 0) {
            NotesList.pop_front();
            if (!NotesList.isEmpty()) {
                NotesList.front()->setPrev(nullptr);
                NotesList.front()->setTick(0);
                NotesList.front()->setTime(0);
            }
        } else if (index == NotesList.size() - 1) {
            NotesList.pop_back();
            if (!NotesList.isEmpty()) {
                NotesList.back()->setNext(nullptr);
            }
        } else {
            GraphicsNote *prev = NotesList[index - 1];
            GraphicsNote *next = NotesList[index + 1];
            NotesList.removeAt(index);
            prev->setNext(next);
            next->setPrev(prev);
        }
        removeNoteCore(c);
    }

    updateNoteTempoAfter(indexs.front() - 1);
    updateNoteTickAfter(indexs.front() - 1);

    lengthCall();
}

void NotesArea::clearNotes() {
    removeAllNotes();
    lengthCall();
}

void NotesArea::removeAllNotes() {
    for (int i = 0; i < NotesList.size(); ++i) {
        removeNoteCore(NotesList.at(i));
    }
    NotesList.clear();
}

void NotesArea::moveNotes(QPoint range, int movement) {
    if (range.x() + movement < 0) {
        movement = -range.x();
    } else if (range.y() + movement > NotesList.size() - 1) {
        movement = NotesList.size() - 1 - range.y();
    }
    if (movement == 0) {
        return;
    }

    int left = range.x();                   // Leftmost note
    int length = range.y() - range.x() + 1; // Range Length

    int totalLen = 0;         // Selection Ticks
    int totalLenInvolved = 0; // Involved notes Ticks

    int i;

    GraphicsNote *selectionLeft = NotesList[range.x()];
    GraphicsNote *selectionRight = NotesList[range.y()];

    GraphicsNote *involvedLeft;
    GraphicsNote *involvedRight;

    GraphicsNote *newLeftmost;
    int leftmostIndex;
    int totalCount;

    // Add up notes of selection's length
    for (i = 0; i < length; ++i) {
        totalLen += NotesList[left + i]->Note.length;
    }

    // Move
    if (movement > 0) {
        involvedLeft = NotesList[left + length];
        involvedRight = NotesList[left + length + movement - 1];
        // Move Involved notes
        for (i = 0; i < movement; ++i) {
            // Add up same count of notes after selection's length
            totalLenInvolved += NotesList[left + length + i]->Note.length;

            int orgTick = NotesList[left + length + i]->tick();
            NotesList[left + length + i]->setTick(orgTick - totalLen);
        }
        // Move Selection
        for (int i = 0; i < length; ++i) {
            // Add up notes of selection's length
            int orgTick = NotesList[left + i]->tick();
            NotesList[left + i]->setTick(orgTick + totalLenInvolved); // change ticks
        }

        newLeftmost = involvedLeft;
        leftmostIndex = left;
        totalCount = length + movement;

        // Set neighbor notes's Next and Prev
        if (selectionLeft->prev()) {
            selectionLeft->prev()->setNext(involvedLeft);
        }
        if (involvedRight->next()) {
            involvedRight->next()->setPrev(selectionRight);
        }

        // Set Next and Prev
        involvedLeft->setPrev(selectionLeft->prev());
        selectionLeft->setPrev(involvedRight);
        selectionRight->setNext(involvedRight->next());
        involvedRight->setNext(selectionLeft);
    } else {
        involvedLeft = NotesList[left + movement];
        involvedRight = NotesList[left - 1];
        // Move Involved notes
        for (i = 0; i < -movement; ++i) {
            // Add up same count of notes before selection's length
            totalLenInvolved += NotesList[left + movement + i]->Note.length;

            int orgTick = NotesList[left + movement + i]->tick();
            NotesList[left + movement + i]->setTick(orgTick + totalLen);
        }

        // Move Selection
        for (int i = 0; i < length; ++i) {
            // Add up notes of selection's length
            int orgTick = NotesList[left + i]->tick();
            NotesList[left + i]->setTick(orgTick - totalLenInvolved); // change ticks
        }

        newLeftmost = selectionLeft;
        leftmostIndex = left + movement;
        totalCount = length - movement;

        // Set neighbor notes's Next and Prev
        if (involvedLeft->prev()) {
            involvedLeft->prev()->setNext(selectionLeft);
        }
        if (selectionRight->next()) {
            selectionRight->next()->setPrev(involvedRight);
        }

        // Set Next and Prev
        selectionLeft->setPrev(involvedLeft->prev());
        involvedLeft->setPrev(selectionRight);
        involvedRight->setNext(selectionRight->next());
        selectionRight->setNext(involvedLeft);
    }

    // Sort In Notes List
    GraphicsNote *cur = newLeftmost;
    for (i = 0; i < totalCount; ++i) {
        NotesList[leftmostIndex + i] = cur;
        cur = cur->next();
    }

    if (newLeftmost->prev()) {
        newLeftmost->setTime(newLeftmost->prev()->time() + newLeftmost->prev()->duration());
    } else {
        newLeftmost->setTime(0);
    }

    // Update Time
    updateNoteTempoAfter(leftmostIndex - 1);
    updateNoteTimeAfter(leftmostIndex);
}
