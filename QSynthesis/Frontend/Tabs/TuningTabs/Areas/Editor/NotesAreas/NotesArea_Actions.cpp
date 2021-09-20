#include "../../../Operations/ImplicitOperation.h"
#include "../../../Operations/LengthOperation.h"
#include "../../../Operations/MoveOperation.h"
#include "../../../Operations/SequenceOperation.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::autoDelete() {
    if (m_notesEnabled) {
        qDragOut.filter(GraphicsDragger::Note);
        removeSelectedNotes();
    } else {
        qDragOut.filter(GraphicsDragger::Point);
        removeSelectedPoints();
    }
}

void NotesArea::autoPaste(const QList<QLinkNote> &notes) {
    if (m_notesEnabled) {
        pasteNotes(notes);
    } else if (m_pitchesEnabled) {
        pasteMode2(notes);
    } else {
        pasteEnvelope(notes);
    }
}

void NotesArea::inputNotes(const QList<QLinkNote> &notes) {
    removeAllNotes();
    insertNotes({}, notes);
    adjustNotes();

    lengthCall();
}

void NotesArea::preparePlugin(PluginTempData &ns, bool all) {
    QPoint region = selectContinuously(all);

    QVector<QLinkNote> &notes = ns.notes;
    QVector<NoteReadonlys> &readonlys = ns.readonlys;

    if (region.x() < 0) {
        region = QPoint(NotesList.size(), NotesList.size() - 1);
    }

    bool hasPrev = region.x() != 0;
    bool hasNext = region.y() != NotesList.size() - 1;

    int start = region.x() - (hasPrev ? 1 : 0);
    int end = region.y() + (hasNext ? 1 : 0) + 1;

    notes.clear();
    readonlys.clear();

    for (int i = start; i < end; ++i) {
        GraphicsNote *p = NotesList.at(i);
        notes.append(p->Note);

        NoteReadonlys r;
        QGenonSettings genon = p->genonSettings();
        QCorrectGenon correctGenon = p->correctGenon();

        if (p->isListed()) {
            r.preuttr = correctGenon.PreUtterance;
            r.overlap = correctGenon.VoiceOverlap;
            r.stpoint = correctGenon.StartPoint;

            r.filename = genon.mFileName;
            r.alias = genon.mAlias;

            r.cache = NODEF_STRING;
        }

        readonlys.append(r);
    }

    ns.hasPrev = hasPrev;
    ns.hasNext = hasNext;

    ns.start = region.x();
}

void NotesArea::receivePlugin(const PluginTempData &ns, QPoint orgRegion) {
    QList<int> indexs, newIndexs;
    QList<QLinkNote> notes;

    // Remove Notes
    for (int i = orgRegion.x(); i <= orgRegion.y(); ++i) {
        indexs.append(i);
        notes.append(NotesList[i]->Note);
    }

    // Insert Notes
    QList<QLinkNote> newNotes = ns.notes.toList();
    for (int i = 0; i < newNotes.size(); ++i) {
        int index = ns.start - ns.normalBegin() + i;
        newIndexs.append(index);
    }

    // Deselect all
    qDragOut.removeAll();

    // New Operation
    SequenceOperation *s = new SequenceOperation(false);
    SequenceOperation *s2 = new SequenceOperation(true);
    int ig = Qs::IgnoreNone;

    if (ns.hasPrev) {
        ig |= Qs::IgnoreFront;
    }
    if (ns.hasNext) {
        ig |= Qs::IgnoreBack;
    }

    // Set History Values
    s->setIndex(indexs);
    s->setNotes(notes);
    s->setIgnore((Qs::IgnoreSelection) ig);

    s2->setIndex(newIndexs);
    s2->setNotes(newNotes);
    s2->setIgnore((Qs::IgnoreSelection) ig);

    s->setNext(s2);

    // Save Operation
    saveOperation(s);

    // Update Core
    removeNotes(indexs);

    insertNotes(newIndexs, newNotes);

    // Adjust vision
    adjustNotes(QPoint(newIndexs.front(), -1));
    if ((ig & Qs::IgnoreFront) && !newIndexs.isEmpty()) {
        newIndexs.pop_front();
    }
    if ((ig & Qs::IgnoreBack) && !newIndexs.isEmpty()) {
        newIndexs.pop_back();
    }
    selectSequence(newIndexs);

    lengthCall();
}

void NotesArea::removeSelectedNotes() {
    if (qDragOut.selectedNotes.isEmpty()) {
        return;
    }

    QList<int> indexs;
    QList<QLinkNote> notes;

    for (int i = 0; i < qDragOut.selectedNotes.size(); ++i) {
        GraphicsNote *c = qDragOut.selectedNotes.at(i);

        int index = NotesList.indexOf(c);
        indexs.append(index);
        notes.append(c->Note);
    }

    // Deselect all
    qDragOut.removeAll(GraphicsDragger::Note);

    // New Operation
    SequenceOperation *s = new SequenceOperation(false);

    // Set History Values
    s->setIndex(indexs);
    s->setNotes(notes);

    // Save Operation
    saveOperation(s);

    // Update Core
    removeNotes(indexs);

    // Adjust vision
    adjustNotes(QPoint(indexs.front(), -1));

    lengthCall();
}

void NotesArea::removeSelectedPoints() {
    if (qDragOut.selectedPoints.isEmpty()) {
        return;
    }

    bool mode2 = true;
    ItemList<ScopeHandler> list, successList;

    for (int i = 0; i < qDragOut.selectedPoints.size(); ++i) {
        GraphicsPoint *p = qDragOut.selectedPoints.at(i);
        ScopeHandler *s = p->scope();
        list.insertAuto(s);

        if (s->type() == Qs::Envelopes) {
            mode2 = false;
        }
    }

    for (auto it = list.begin(); it != list.end(); ++it) {
        ScopeHandler *s = *it;
        QList<GraphicsPoint *> points;
        for (int i = 0; i < s->Points.size(); ++i) {
            GraphicsPoint *p = s->Points.at(i);
            if (p->isSelected()) {
                points.append(p);
            }
        }
        if (!s->removePoints(points)) {
            continue;
        }

        successList.insertAuto(s);
    }

    savePointsCore(successList, mode2);

    // Update
    for (auto it = successList.begin(); it != successList.end(); ++it) {
        ScopeHandler *s = *it;

        s->adjustPoints();
        s->note()->updateComponents();
    }
}

void NotesArea::shiftSelectedNotes(int offset) {
    QList<int> orgNoteNums, changes;

    QPoint selection = continuousSelection();
    if (selection.x() < 0) {
        return;
    }

    int aIndex = selection.x();
    int bIndex = selection.y();

    for (int i = aIndex; i <= bIndex; ++i) {
        GraphicsNote *c = NotesList.at(i);
        int noteNum = c->Note.noteNum + (c->isSelected() ? offset : 0);

        if (noteNum > 107) {
            noteNum = 107;
        } else if (noteNum < 24) {
            noteNum = 24;
        }

        // Save Values
        orgNoteNums.push_back(c->Note.noteNum);
        changes.push_back(noteNum - c->Note.noteNum);

        // Change
        c->Note.noteNum = noteNum;
    }

    // New Operation
    MoveOperation *m = new MoveOperation();
    int index = aIndex;
    int movement = 0;

    // Set History Values
    m->setIndex(index);
    m->setVerticals(changes);
    m->setMovement(movement);

    qDebug() << "[Save Move]" << index << changes << movement;

    // Save Operation
    saveOperation(m);

    // Update Core
    moveNotes(QPoint(index, index + changes.size() - 1), movement);

    // Adjust vision
    adjustNotes(QPoint(aIndex, bIndex + 1));

    lengthCall();
}

void NotesArea::modifySelectedNotes(const NoteProperties &orgValues,
                                    const NoteProperties &newValues) {
    NoteOperation *n = nullptr;

    QList<int> indexs;
    for (int i = 0; i < NotesList.size(); ++i) {
        if (NotesList[i]->isSelected()) {
            indexs.append(i);
        }
    }

    // Length
    if (orgValues.length != newValues.length && !newValues.length.isEmpty()) {
        QList<int> orgs, news;
        LengthOperation *l = new LengthOperation();
        int newVal = newValues.length.toInt();

        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(p->Note.length);
            news.append(newVal);

            p->Note.length = newVal;
        }

        l->setOrigin(orgs);
        l->setModified(news);
        l->setIndex(indexs);
        n = l;
    }

    // Intensity
    if (orgValues.intensity != newValues.intensity) {
        QStringList orgs, news;
        ImplicitOperation *l = new ImplicitOperation(NoteOperation::Intensity);
        double newVal =
            newValues.intensity.isEmpty() ? NODEF_DOUBLE : newValues.intensity.toDouble();

        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(QString::number(p->Note.intensity));
            news.append(QString::number(newVal));

            p->Note.intensity = newVal;
        }

        l->setOrigin(orgs);
        l->setModified(news);
        l->setIndex(indexs);

        if (n) {
            n->setNext(l);
        } else {
            n = l;
        }
    }

    // Modulation
    if (orgValues.modulation != newValues.modulation) {
        QStringList orgs, news;
        ImplicitOperation *l = new ImplicitOperation(NoteOperation::Modulation);
        double newVal =
            newValues.modulation.isEmpty() ? NODEF_DOUBLE : newValues.modulation.toDouble();

        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(QString::number(p->Note.modulation));
            news.append(QString::number(newVal));

            p->Note.modulation = newVal;
        }

        l->setOrigin(orgs);
        l->setModified(news);
        l->setIndex(indexs);

        if (n) {
            n->setNext(l);
        } else {
            n = l;
        }
    }

    // Velocity
    if (orgValues.velocity != newValues.velocity) {
        QStringList orgs, news;
        ImplicitOperation *l = new ImplicitOperation(NoteOperation::Velocity);
        double newVal = newValues.velocity.isEmpty() ? NODEF_DOUBLE : newValues.velocity.toDouble();

        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(QString::number(p->Note.velocity));
            news.append(QString::number(newVal));

            p->Note.velocity = newVal;
        }

        l->setOrigin(orgs);
        l->setModified(news);
        l->setIndex(indexs);

        if (n) {
            n->setNext(l);
        } else {
            n = l;
        }
    }

    // StartPoint
    if (orgValues.startpoint != newValues.startpoint) {
        QStringList orgs, news;
        ImplicitOperation *l = new ImplicitOperation(NoteOperation::StartPoint);
        double newVal =
            newValues.startpoint.isEmpty() ? NODEF_DOUBLE : newValues.startpoint.toDouble();

        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(QString::number(p->Note.stp));
            news.append(QString::number(newVal));

            p->Note.stp = newVal;
        }

        l->setOrigin(orgs);
        l->setModified(news);
        l->setIndex(indexs);

        if (n) {
            n->setNext(l);
        } else {
            n = l;
        }
    }

    // Pre-Utterance
    if (orgValues.preUttr != newValues.preUttr) {
        QStringList orgs, news;
        ImplicitOperation *l = new ImplicitOperation(NoteOperation::PreUtterance);
        double newVal = newValues.preUttr.isEmpty() ? NODEF_DOUBLE : newValues.preUttr.toDouble();

        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(QString::number(p->Note.preUttr));
            news.append(QString::number(newVal));

            p->Note.preUttr = newVal;
        }

        l->setOrigin(orgs);
        l->setModified(news);
        l->setIndex(indexs);

        if (n) {
            n->setNext(l);
        } else {
            n = l;
        }
    }

    // Overlap
    if (orgValues.overlap != newValues.overlap) {
        QStringList orgs, news;
        ImplicitOperation *l = new ImplicitOperation(NoteOperation::VoiceOverlap);
        double newVal = newValues.overlap.isEmpty() ? NODEF_DOUBLE : newValues.overlap.toDouble();

        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(QString::number(p->Note.overlap));
            news.append(QString::number(newVal));

            p->Note.overlap = newVal;
        }

        l->setOrigin(orgs);
        l->setModified(news);
        l->setIndex(indexs);

        if (n) {
            n->setNext(l);
        } else {
            n = l;
        }
    }

    // Flags
    if (orgValues.flags != newValues.flags) {
        QStringList orgs, news;
        ImplicitOperation *l = new ImplicitOperation(NoteOperation::VoiceOverlap);
        QString newVal = newValues.flags;

        for (int i = 0; i < indexs.size(); ++i) {
            GraphicsNote *p = NotesList.at(indexs[i]);
            orgs.append(p->Note.flags);
            news.append(newVal);

            p->Note.flags = newVal;
        }

        l->setOrigin(orgs);
        l->setModified(news);
        l->setIndex(indexs);

        if (n) {
            n->setNext(l);
        } else {
            n = l;
        }
    }

    if (!n) {
        return;
    }

    saveOperation(n);

    // Update Core 2
    for (int i = 0; i < indexs.size(); ++i) {
        GraphicsNote *p = NotesList.at(indexs[i]);
        p->updateCorrectGenon();
        p->updateNeighborCorrectGenons();
        p->lifter()->fromNoteProps();
    }
    updateNoteTickAfter(indexs.front());

    // Adjust vision
    adjustNotes(QPoint(indexs.front() - 1, -1));

    lengthCall();
}
