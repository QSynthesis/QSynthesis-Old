#include "../../../Forms/EditorForm.h"
#include "../../../Operations/PointsOperation.h"
#include "../../../Operations/ScatterOperation.h"
#include "../../../Scrolls/NotesScrollArea.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

#include <QScrollBar>

GraphicsNote *NotesArea::createNoteCore(const QLinkNote &note) {
    GraphicsNote *p = new GraphicsNote(this);
    addItem(p);
    p->setZValue(noteZIndex);

    // Add Components
    p->addScreen(); // Add Screen
    p->addLifter(); // Add Lifter

    // Init
    p->Note = note;
    p->updateNoteStatus();
    p->lifter()->fromNoteProps();
    p->curves()->fromNotePoints();   // Add Pit Points
    p->curves()->fromNoteVibrato();  // Add Vibrato
    p->envelope()->fromNotePoints(); // Add Env Points

    updateNoteFindStatus(p);

    return p;
}

void NotesArea::removeNoteCore(GraphicsNote *p) {
    p->curves()->removeAllPoints();    // Remove Pit Points
    p->curves()->removeVibrtoEditor(); // Remove Vibrato

    p->envelope()->removeAllPoints(); // Remove Env Points

    if (p->isInvolved()) {
        qDragOut.removeOneT(p);
    }
    if (p->isSelected()) {
        qDragOut.removeOne(p);
    }
    if (p->highlighted()){
        qDragOut.removeFind(p);
    }

    p->removeLifter(); // Remove Lifter
    p->removeScreen(); // Remove Screen

    removeItem(p);
    delete p;
}

void NotesArea::savePointsCore(const ItemList<ScopeHandler> &list, bool mode2) {
    QList<QList<QControlPoint>> orgs, news;
    QList<int> indexs;

    if (list.isEmpty()) {
        return;
    }

    for (auto it = list.begin(); it != list.end(); ++it) {
        ScopeHandler *s = *it;
        if (mode2) {
            orgs.push_back(s->note()->Note.Mode2Pitch); // Set origin
            s->toNotePoints();                          // Save to note
            news.push_back(s->note()->Note.Mode2Pitch); // Set new
        } else {
            orgs.push_back(s->note()->Note.envelope); // Set origin
            s->toNotePoints();                        // Save to note
            news.push_back(s->note()->Note.envelope); // Set new
        }
        indexs.push_back(NotesList.indexOf(s->note()));
    }

    if (mode2) {
        PointsOperation *m = new PointsOperation(true); // New Operation
        m->setIndex(indexs);                            // Set Modified Indexs
        m->setOrigin(orgs);                             // Set Origin Values
        m->setModified(news);                           // Set New Values
        saveOperation(m);                               // Save Operation
    } else {
        PointsOperation *m = new PointsOperation(false); // New Operation
        m->setIndex(indexs);                             // Set Modified Indexs
        m->setOrigin(orgs);                              // Set Origin Values
        m->setModified(news);                            // Set New Values
        saveOperation(m);                                // Save Operation
    }
}

void NotesArea::saveScatterCore(const ItemList<Mode2Handler> &list, bool vbr) {
    QList<QList<double>> orgs, news;
    QList<int> indexs;

    if (list.isEmpty()) {
        return;
    }
    for (auto it = list.begin(); it != list.end(); ++it) {
        Mode2Handler *s = *it;
        if (vbr) {
            orgs.push_back(s->note()->Note.vibrato); // Set origin
            s->toNoteVibrato();                      // Save to note
            news.push_back(s->note()->Note.vibrato); // Set new
        } else {
            orgs.push_back(s->note()->Note.pitches); // Set origin
            s->toNotePitches();                      // Save to note
            news.push_back(s->note()->Note.pitches); // Set new
        }
        indexs.push_back(NotesList.indexOf(s->note()));
    }

    if (vbr) {
        ScatterOperation *m = new ScatterOperation(false); // New Operation
        m->setIndex(indexs);                               // Set Modified Indexs
        m->setOrigin(orgs);                                // Set Origin Values
        m->setModified(news);                              // Set New Values
        saveOperation(m);                                  // Save Operation
    } else {
        ScatterOperation *m = new ScatterOperation(true); // New Operation
        m->setIndex(indexs);                              // Set Modified Indexs
        m->setOrigin(orgs);                               // Set Origin Values
        m->setModified(news);                             // Set New Values
        saveOperation(m);                                 // Save Operation
    }
}
