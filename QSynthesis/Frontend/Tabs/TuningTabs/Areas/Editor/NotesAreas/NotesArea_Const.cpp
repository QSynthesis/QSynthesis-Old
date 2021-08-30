#include "../../../TuningGroup.h"
#include "../NotesArea.h"

double NotesArea::zeroLine() const {
    return m_ptrs->currentWidth * 4;
}

QList<QLinkNote> NotesArea::allNotes() const {
    QList<QLinkNote> notes;
    for (int i = 0; i < NotesList.size(); ++i) {
        notes.append(NotesList.at(i)->Note);
    }
    return notes;
}

QList<QLinkNote> NotesArea::selectedNotes() const {
    QList<QLinkNote> notes;
    for (int i = 0; i < NotesList.size(); ++i) {
        if (NotesList.at(i)->isSelected()) {
            notes.append(NotesList.at(i)->Note);
        }
    }
    return notes;
}

QPoint NotesArea::continuousSelection() const {
    int min, max;
    int i;

    bool findNote = false;

    min = 0;
    max = NotesList.size() - 1;

    for (i = 0; i < NotesList.size(); ++i) {
        if (NotesList[i]->isSelected()) {
            findNote = true;
            min = i;
            break;
        }
    }
    for (i = NotesList.size() - 1; i >= 0; --i) {
        if (NotesList[i]->isSelected()) {
            max = i;
            break;
        }
    }

    if (findNote) {
        return QPoint(min, max);
    } else {
        return QPoint(-1, -1);
    }
}

int NotesArea::totalLength() const {
    if (NotesList.isEmpty()) {
        return 0;
    }
    return NotesList.back()->tick() + NotesList.back()->Note.length;
}

QList<NoteProperties> NotesArea::selectedProperties() const {
    QList<NoteProperties> list;
    for (int i = 0; i < qDragOut.selectedNotes.size(); ++i) {
        GraphicsNote *p = qDragOut.selectedNotes.at(i);
        NoteProperties np;

        np.length = QString::number(p->Note.length);

        np.intensity = p->Note.intensity == NODEF_DOUBLE ? "" : QString::number(p->Note.intensity);
        np.modulation =
            p->Note.modulation == NODEF_DOUBLE ? "" : QString::number(p->Note.modulation);

        np.preUttr = p->Note.preUttr == NODEF_DOUBLE ? "" : QString::number(p->Note.preUttr);
        np.overlap = p->Note.overlap == NODEF_DOUBLE ? "" : QString::number(p->Note.overlap);

        np.startpoint = p->Note.stp == NODEF_DOUBLE ? "" : QString::number(p->Note.stp);
        np.velocity = p->Note.velocity == NODEF_DOUBLE ? "" : QString::number(p->Note.velocity);

        np.flags = p->Note.flags;

        np.tempo = QString::number(p->tempo());

        if (p->isListed()) {
            np.preUttrOto = QString::number(p->genonSettings().mPreUtterance);
            np.overlapOto = QString::number(p->genonSettings().mVoiceOverlap);
        }

        list.append(np);
    }
    return list;
}
