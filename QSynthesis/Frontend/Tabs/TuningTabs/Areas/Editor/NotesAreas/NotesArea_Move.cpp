#include "../../../Modules/Scrolls/NotesScrollArea.h"
#include "../../../Operations/ImplicitOperation.h"
#include "../../../Operations/LengthOperation.h"
#include "../../../Operations/MoveOperation.h"
#include "../../../Operations/SequenceOperation.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::prepareMove(GraphicsNote *p) {
    int index = NotesList.indexOf(p);
    int i;

    // Put the note right behind it to involved list
    if (qDragOut.stretching == Qs::RelativeStretch) {
        if (index < NotesList.size() - 1) {
            qDragOut.addOneT(NotesList.at(index + 1));
        }
        return;
    } else if (qDragOut.stretching == Qs::AbsoluteStretch) {
        // Put notes behind it to involved list
        for (i = index + 1; i < NotesList.size(); ++i) {
            qDragOut.addOneT(NotesList.at(i));
        }
    } else {
        // Put all notes to involved list
        for (i = 0; i < NotesList.size(); ++i) {
            if (!NotesList.at(i)->isSelected()) {
                qDragOut.addOneT(NotesList.at(i));
            }
        }

        // Set Possible Positions
        qDragOut.possiblePositions.clear();
        for (i = 0; i < NotesList.size(); ++i) {
            GraphicsNote *c = NotesList.at(i);
            if (c->isSelected()) {
                if (c == qDragOut.leftmost()) {
                    qDragOut.possiblePositions.append(c->x());
                }
            } else if (c->x() < qDragOut.leftmost()->x()) {
                qDragOut.possiblePositions.append(c->x());
            } else {
                qDragOut.possiblePositions.append(c->x() + c->width() - qDragOut.totalWidth());
            }
        }
    }
}

void NotesArea::refreshMove(GraphicsNote *p) {
    GraphicsNote *leftmostNote;
    GraphicsNote *rightmostNote;

    // Reset
    for (int i = 0; i < NotesList.size(); ++i) {
        GraphicsNote *c = NotesList.at(i);
        if (c->MPrev() != c->prev() || c->MNext() != c->next()) {
            c->setMPrev(c->prev());
            c->setMNext(c->next());

            c->adjustComponents();
        }
    }

    if (qDragOut.stretching) {
        leftmostNote = p->prev() ? p->prev() : p;
        if (qDragOut.stretching == Qs::RelativeStretch) {
            rightmostNote = p->next() ? (p->next()->next() ? p->next()->next() : p->next()) : p;
        } else {
            rightmostNote = NotesList.back();
        }
    } else {
        GraphicsNote *leftmost = static_cast<GraphicsNote *>(qDragOut.leftmost());

        int aIndex = qDragOut.findPossiblePos(leftmost->staticPos().x());
        int bIndex = qDragOut.findPossiblePos(leftmost->x());

        // Simulate Moving
        int movement = bIndex - aIndex;

        int left = NotesList.indexOf(leftmost);
        int length = qDragOut.selectedNotes.size();

        GraphicsNote *selectionLeft = NotesList[left];
        GraphicsNote *selectionRight = NotesList[left + length - 1];

        GraphicsNote *involvedLeft;
        GraphicsNote *involvedRight;

        GraphicsNote *neighborLeft;
        GraphicsNote *neighborRight;

        // Move
        if (movement > 0) {
            involvedLeft = NotesList[left + length];
            involvedRight = NotesList[left + length + movement - 1];

            neighborLeft = selectionLeft->prev();
            neighborRight = involvedRight->next();

            leftmostNote = involvedLeft;
            rightmostNote = selectionRight;

            // Set neighbor notes's Next and Prev
            if (neighborLeft) {
                neighborLeft->setMNext(involvedLeft);
            }
            if (neighborRight) {
                neighborRight->setMPrev(selectionRight);
            }

            // Set Next and Prev
            involvedLeft->setMPrev(neighborLeft);
            selectionLeft->setMPrev(involvedRight);
            selectionRight->setMNext(neighborRight);
            involvedRight->setMNext(selectionLeft);

        } else if (movement < 0) {
            involvedLeft = NotesList[left + movement];
            involvedRight = NotesList[left - 1];

            neighborLeft = involvedLeft->prev();
            neighborRight = selectionRight->next();

            leftmostNote = selectionLeft;
            rightmostNote = involvedRight;

            // Set neighbor notes's Next and Prev
            if (neighborLeft) {
                neighborLeft->setMNext(selectionLeft);
            }
            if (neighborRight) {
                neighborRight->setMPrev(involvedRight);
            }

            // Set Next and Prev
            selectionLeft->setMPrev(neighborLeft);
            involvedLeft->setMPrev(selectionRight);
            involvedRight->setMNext(neighborRight);
            selectionRight->setMNext(involvedLeft);
        } else {
            neighborLeft = selectionLeft->prev();
            neighborRight = selectionRight->next();

            leftmostNote = selectionLeft;
            rightmostNote = selectionRight;
        }

        if (neighborLeft) {
            leftmostNote = neighborLeft;
        }
        if (neighborRight) {
            rightmostNote = neighborRight;
        }
    }

    for (auto it = leftmostNote; true; it = it->MNext()) {
        it->adjustComponents();
        if (it == rightmostNote) {
            break;
        }
    }
}

void NotesArea::endMove(GraphicsNote *p) {
    if (qDragOut.stretching) {
        int index = NotesList.indexOf(p);
        int length = p->lengthRef();
        int length2;

        // New Operation
        LengthOperation *l = new LengthOperation();

        QList<int> indexs;
        QList<int> orgs;
        QList<int> news;

        indexs.append(index);
        orgs.append(p->Note.length);
        news.append(length);

        // Relative Stretch
        GraphicsNote *pNext = nullptr;
        if (qDragOut.stretching == Qs::RelativeStretch && index < NotesList.size() - 1) {
            pNext = NotesList.at(index + 1);

            if (pNext->isVisible()) {
                length2 = p->Note.length + pNext->Note.length - length;
                indexs.append(index + 1);
                orgs.append(pNext->Note.length);
                news.append(length2);
            } else {
                // Delete the next note
                SequenceOperation *s = new SequenceOperation(false);
                s->setIndex({index + 1});
                s->setNotes({pNext->Note});

                qDragOut.removeAllT();
                removeNote(index + 1);
                l->setNext(s);
                pNext = nullptr;
            }
        }

        // Set History Values
        l->setIndex(indexs);
        l->setOrigin(orgs);
        l->setModified(news);

        qDebug() << "[Save Stretch]" << p->Note.lyric;

        // Save Operation
        saveOperation(l);

        // Update Core
        p->Note.length = length;
        if (pNext) {
            pNext->Note.length = length2;
        } else {
            updateNoteTempoAfter(index);
        }
        updateNoteTickAfter(index);
        p->updateNeighborCorrectGenons(true);
    } else {
        qDebug() << "[Save Move]" << p->Note.lyric;

        GraphicsNote *leftmost = static_cast<GraphicsNote *>(qDragOut.leftmost());
        int aIndex = qDragOut.possiblePositions.indexOf(leftmost->staticPos().x());
        int bIndex = qDragOut.possiblePositions.indexOf(leftmost->x());

        qDragOut.possiblePositions.clear();

        QList<int> orgNoteNums, changes;

        bool verticalMove = false;
        for (int i = 0; i < qDragOut.selectedNotes.size(); ++i) {
            GraphicsNote *c = qDragOut.selectedNotes.at(i);
            int noteNum = convertPositionToValue(c->pos()).second;

            int verticalChange = noteNum - c->Note.noteNum;

            // Save Values
            orgNoteNums.push_back(c->Note.noteNum);
            changes.push_back(verticalChange);

            // Change
            c->Note.noteNum = noteNum;

            if (verticalChange != 0) {
                verticalMove = true;
            }
        }

        // New Operation
        MoveOperation *m = new MoveOperation();
        int index = NotesList.indexOf(leftmost);
        int movement = bIndex - aIndex;

        // Set History Values
        m->setIndex(index);
        m->setVerticals(changes);
        m->setMovement(movement);

        qDebug() << "[Save Move]" << index << changes << movement;

        // Save Operation
        saveOperation(m);

        // Update Core
        moveNotes(QPoint(index, index + changes.size() - 1), movement);
        if (verticalMove) {
            int newIndex = index + movement;
            updateNotesStatus(QPoint(newIndex, newIndex + changes.size() - 1));
        }
        adjustNoteComponents();
    }
    lengthCall();
}

void NotesArea::afterDraw(GraphicsNote *p) {
    int index = NotesList.indexOf(p);
    int length = p->lengthRef();

    p->Note.length = length;

    // New Operation
    SequenceOperation *s = new SequenceOperation(true);

    // Set History Values
    s->setIndex({index});
    s->setNotes({p->Note});

    if (p->tempoEdited()) {
        updateNoteTempoAfter(index);
    }
    updateNoteTickAfter(index);

    qDebug() << "[Save Draw]" << p->Note.lyric;

    // Save Operation
    saveOperation(s);

    // Update Status
    p->setMovable(m_notesEnabled);
    p->updateNeighborCorrectGenons(true);

    lengthCall();

    m_drawingItem = nullptr;
}

void NotesArea::prepareMove(GraphicsPoint *p) {
    qDragOut.InvolvedScopes.clear();
    // Get involved scopes
    for (int i = 0; i < qDragOut.selectedPoints.size(); ++i) {
        GraphicsPoint *p = static_cast<GraphicsPoint *>(qDragOut.selectedPoints[i]);
        qDragOut.InvolvedScopes.insertAuto(p->scope());
    }
    for (auto it = qDragOut.InvolvedScopes.begin(); it != qDragOut.InvolvedScopes.end(); ++it) {
        // Add points to involved list
        (*it)->prepareMove(p);
    }
}

void NotesArea::refreshMove(GraphicsPoint *p, QPointF pos) {
    bool changed = false;
    for (auto it = qDragOut.InvolvedScopes.begin(); it != qDragOut.InvolvedScopes.end(); ++it) {
        changed |= (*it)->updateXRank();
    }

    // One more limit
    if (changed) {
        qDragOut.duringDrag(p, pos);
        qDragOut.duringInvolve(p, pos);
    }

    for (auto it = qDragOut.InvolvedScopes.begin(); it != qDragOut.InvolvedScopes.end(); ++it) {
        (*it)->note()->updateComponents();
    }
}

void NotesArea::endMove(GraphicsPoint *p) {
    bool mode2 = qDragOut.InvolvedScopes.front()->type() == Qs::Mode2;
    for (auto it = qDragOut.InvolvedScopes.begin(); it != qDragOut.InvolvedScopes.end(); ++it) {
        ScopeHandler *s = *it;
        s->note()->updateComponents(); // Update Vision
        s->endMove(p);                 // Save moving points to backend value
    }
    savePointsCore(qDragOut.InvolvedScopes, mode2);
    qDragOut.InvolvedScopes.clear();
}

void NotesArea::afterDraw(GraphicsPoint *p) {
    endMove(p);
    m_drawingItem = nullptr;
}

void NotesArea::afterModifyVibrato(GraphicsNote *p) {
    ItemList<Mode2Handler> list;
    list.append(p->curves());
    saveScatterCore(list, true);
}

void NotesArea::afterModifyLifters(GraphicsLifter::Props prop) {
    QList<int> indexs;

    for (int i = 0; i < NotesList.size(); ++i) {
        if (NotesList.at(i)->isSelected()) {
            indexs.append(i);
        }
    }

    QStringList orgs, news;
    ImplicitOperation *l = nullptr;

    switch (prop) {
    case GraphicsLifter::Intensity: {
        l = new ImplicitOperation(NoteOperation::Intensity);
        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(QString::number(p->Note.intensity));
            p->lifter()->fromHandle();
            p->lifter()->toNoteProps(GraphicsLifter::Intensity);
            news.append(QString::number(p->Note.intensity));
        }
        break;
    }
    case GraphicsLifter::Modulation: {
        l = new ImplicitOperation(NoteOperation::Modulation);
        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(QString::number(p->Note.modulation));
            p->lifter()->fromHandle();
            p->lifter()->toNoteProps(GraphicsLifter::Modulation);
            news.append(QString::number(p->Note.modulation));
        }
        break;
    }
    case GraphicsLifter::Velocity: {
        l = new ImplicitOperation(NoteOperation::Velocity);
        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(QString::number(p->Note.velocity));
            p->lifter()->fromHandle();
            p->lifter()->toNoteProps(GraphicsLifter::Velocity);
            news.append(QString::number(p->Note.velocity));
        }
        break;
    }
    default:
        break;
    }

    l->setOrigin(orgs);
    l->setModified(news);
    l->setIndex(indexs);

    saveOperation(l);

    // Update Core 2
    for (int i = 0; i < indexs.size(); ++i) {
        GraphicsNote *p = NotesList.at(indexs[i]);
        p->updateCorrectGenon();
        p->updateNeighborCorrectGenons();
        p->lifter()->fromNoteProps();
    }
    updateNoteTickAfter(indexs.front());

    // Adjust vision
    adjustNotes(QPoint(indexs.front() - 1, indexs.back() + 1));

    lengthCall();
}
