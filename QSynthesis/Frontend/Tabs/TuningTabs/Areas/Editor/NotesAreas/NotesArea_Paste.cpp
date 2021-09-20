#include "../../../Operations/ImplicitOperation.h"
#include "../../../Operations/LengthOperation.h"
#include "../../../Operations/MoveOperation.h"
#include "../../../Operations/PointsOperation.h"
#include "../../../Operations/ScatterOperation.h"
#include "../../../Operations/SequenceOperation.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::pasteNotes(const QList<QLinkNote> &notes) {
    QList<int> indexs;

    int index = NotesList.size();
    GraphicsNote *leftmost = static_cast<GraphicsNote *>(qDragOut.leftmost());
    if (leftmost) {
        index = NotesList.indexOf(leftmost);
    }

    for (int i = 0; i < notes.size(); ++i) {
        indexs.push_back(index + i);
    }

    // New Operation
    SequenceOperation *s = new SequenceOperation(true);

    // Set History Values
    s->setIndex(indexs);
    s->setNotes(notes);

    // Save Operation
    saveOperation(s);

    // Update Core
    insertNotes(indexs, notes);

    // Adjust vision
    updateNotesStatus(QPoint(indexs.front(), indexs.back() + 1));
    adjustNotes(QPoint(indexs.front() - 1, -1));
    selectSequence(indexs);

    lengthCall();
}

void NotesArea::pasteMode2(const QList<QLinkNote> &notes) {
    if (qDragOut.selectedNotes.isEmpty() || notes.isEmpty()) {
        return;
    }

    QList<int> indexs;
    QList<QList<QControlPoint>> orgPoints, newPoints;
    QList<QList<double>> orgDoubles, newDoubles;
    for (int i = 0; i < qMin(qDragOut.selectedNotes.size(), notes.size()); ++i) {
        GraphicsNote *p = qDragOut.selectedNotes.at(i);
        const QLinkNote &note = notes.at(i);

        orgPoints.append(p->Note.Mode2Pitch);
        newPoints.append(notes.at(i).Mode2Pitch);

        orgDoubles.append(p->Note.vibrato);
        newDoubles.append(note.vibrato);

        p->Note.Mode2Pitch = note.Mode2Pitch;
        p->Note.vibrato = note.vibrato;

        int index = NotesList.indexOf(p);
        indexs.append(index);

        p->curves()->fromNoteVibrato();
        p->curves()->fromNotePoints();
    }

    PointsOperation *m = new PointsOperation(true); // New Operation
    m->setIndex(indexs);                            // Set Modified Indexs
    m->setOrigin(orgPoints);                        // Set Origin Values
    m->setModified(newPoints);                      // Set New Values

    ScatterOperation *n = new ScatterOperation(false);
    n->setIndex(indexs);
    n->setOrigin(orgDoubles);
    n->setModified(newDoubles);

    m->setNext(n);

    saveOperation(m); // Save Operation

    adjustNotes(QPoint(indexs.front() - 1, indexs.back() + 1));
    selectSequence(indexs);
}

void NotesArea::pasteEnvelope(const QList<QLinkNote> &notes) {
    if (qDragOut.selectedNotes.isEmpty() || notes.isEmpty()) {
        return;
    }

    QList<int> indexs;
    QList<QList<QControlPoint>> orgPoints, newPoints;
    for (int i = 0; i < qMin(qDragOut.selectedNotes.size(), notes.size()); ++i) {
        GraphicsNote *p = qDragOut.selectedNotes.at(i);
        const QLinkNote &note = notes.at(i);

        orgPoints.append(p->Note.envelope);
        newPoints.append(notes.at(i).envelope);

        p->Note.Mode2Pitch = note.envelope;

        int index = NotesList.indexOf(p);
        indexs.append(index);

        p->envelope()->fromNotePoints();
    }

    PointsOperation *m = new PointsOperation(false); // New Operation
    m->setIndex(indexs);                             // Set Modified Indexs
    m->setOrigin(orgPoints);                         // Set Origin Values
    m->setModified(newPoints);                       // Set New Values

    saveOperation(m); // Save Operation

    adjustNotes(QPoint(indexs.front() - 1, indexs.back() + 1));
    selectSequence(indexs);
}
