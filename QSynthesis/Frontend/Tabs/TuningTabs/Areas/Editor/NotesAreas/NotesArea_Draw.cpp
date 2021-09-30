#include "../../../Forms/EditorForm.h"
#include "../../../Scrolls/NotesScrollArea.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

GraphicsNote *NotesArea::insertNoteFromCursor(QPointF pos) {
    int index = findNoteAtPos(pos.x());
    int curAdsorb = m_ptrs->currentAdsorb;
    int len = (curAdsorb == 0) ? 15 : 480 / curAdsorb;
    QPair<int, int> notePos = convertPositionToValue(pos);

    QLinkNote note(notePos.second, len);
    GraphicsNote *p = insertNote(index, note);

    // Adjust Geometries
    adjustNotes();
    return p;
}

void NotesArea::prepareDrawNote(QGraphicsSceneMouseEvent *event) {
    GraphicsNote *p = insertNoteFromCursor(event->scenePos());

    p->setDrawing(true);
    p->setMovable(true); // Temporary
    p->setStretch(true);

    p->grabMouse();
    p->afterPress();
    p->afterMove(event->scenePos());

    m_drawingItem = p;
}

GraphicsPoint *NotesArea::insertPointFromCursor(QPointF pos) {
    GraphicsNote *cur = nullptr, *next = nullptr;
    GraphicsPoint *p;
    Qt::KeyboardModifiers c = QApplication::keyboardModifiers();

    // Find the note nearest to the cursor
    int index = findNoteAtPosAbs(pos.x());
    if (index >= 0 && index < NotesList.size()) {
        cur = NotesList[index];
        next = cur->next();
    } else {
        return nullptr;
    }

    bool mode2 = m_pitchesEnabled;

    ScopeHandler *curScope = cur ? cur->curves() : nullptr;
    ScopeHandler *nextScope = next ? next->curves() : nullptr;

    if (!mode2) {
        curScope = cur ? cur->envelope() : nullptr;
        nextScope = next ? next->envelope() : nullptr;
    }

    // Curves exists and the last point is in the right of cursor
    if (curScope && curScope->lastPoint() && curScope->lastPoint()->x() > pos.x() &&
        c != Qt::ControlModifier) {
        // 直接加点
        if (!mode2 && curScope->Points.size() > 4) {
            return nullptr;
        }
        p = curScope->insertPoint(pos);
        return p;
    }

    // Next note exists and the first point of it is in the left of cursor
    if (nextScope && nextScope->firstPoint()) {
        if (nextScope->firstPoint()->x() < pos.x()) {
            if (!mode2 && nextScope->Points.size() > 4) {
                return nullptr;
            }
            p = nextScope->insertPoint(pos);
            return p;
        } else if (c == Qt::ControlModifier) {
            if (!mode2 && nextScope->Points.size() > 4) {
                return nullptr;
            }
            p = nextScope->insertPoint(pos);
            return p;
        }
    }

    // Otherwise insert point to current note
    if (curScope) {
        if (!mode2 && curScope->Points.size() > 4) {
            return nullptr;
        }
        p = curScope->insertPoint(pos);
        return p;
    }

    return nullptr;
}

void NotesArea::prepareDrawPoint(QGraphicsSceneMouseEvent *event) {
    GraphicsPoint *p = insertPointFromCursor(event->scenePos());
    if (!p) {
        return;
    }

    p->setDrawing(true);
    p->grabMouse();
    p->afterPress();
    p->afterMove(event->scenePos());

    m_drawingItem = p;
}

void NotesArea::removePointFromCursor(GraphicsPoint *p) {
    ScopeHandler *s = p->scope();

    if (!s->removePoints({p})) {
        return;
    }

    ItemList<ScopeHandler> list;
    list.append(s);

    savePointsCore(list, s->type() == Qs::Mode2);

    s->adjustPoints();
    s->note()->updateComponents();
}

void NotesArea::changePointFromCursor(GraphicsPoint *p) {
    ScopeHandler *s = p->scope();
    bool mode2 = s->type() == Qs::Mode2;

    if (mode2) {
        Qs::PitchPoint type = p->TPoint.mP;
        // First point is not able to change
        if (p->specialPos() == Qs::Leftmost) {
            return;
        }

        if (type == Qs::sJoin) { // S type
            type = Qs::linearJoin;
        } else if (type == Qs::rJoin) { // R type
            type = Qs::jJoin;
        } else if (type == Qs::jJoin) { // J type
            type = Qs::sJoin;
        } else {
            type = Qs::rJoin;
        }

        p->TPoint.mP = type;

    } else {
        EnvelopeHandler *e = qobject_cast<EnvelopeHandler *>(s);
        p->TPoint.mY = 100;
    }

    ItemList<ScopeHandler> list;
    list.append(s);
    savePointsCore(list, mode2);

    s->adjustPoints();
    s->note()->updateComponents();
}

void NotesArea::addPortamento(GraphicsNote *p) {
    ItemList<ScopeHandler> list;

    for (int i = 0; i < qDragOut.selectedNotes.size(); ++i) {
        GraphicsNote *c = qDragOut.selectedNotes.at(i);
        Mode2Handler *s = c->curves();
        if (s->Points.isEmpty()) {
            s->makeDefaultPoints();
            list.insertAuto(s);
        }
        s->adjustPoints();
        s->note()->updateComponents();
    }

    savePointsCore(list, true);
}

void NotesArea::removePortamento(GraphicsNote *p) {
    ItemList<ScopeHandler> list;
    for (int i = 0; i < qDragOut.selectedNotes.size(); ++i) {
        GraphicsNote *c = qDragOut.selectedNotes.at(i);
        Mode2Handler *s = c->curves();
        if (!s->Points.isEmpty()) {
            s->clearPoints();
            list.insertAuto(s);
        }
        s->note()->updateComponents();
    }

    savePointsCore(list, true);
}

void NotesArea::addVibrato(GraphicsNote *p) {
    ItemList<Mode2Handler> list;
    for (int i = 0; i < qDragOut.selectedNotes.size(); ++i) {
        GraphicsNote *c = qDragOut.selectedNotes.at(i);
        Mode2Handler *s = c->curves();
        if (s->Vibrato.isEmpty()) {
            s->makeDefaultVibrato();
            list.insertAuto(s);
        }
        s->adjustPoints();
        s->note()->updateComponents();
    }

    saveScatterCore(list, true);
}

void NotesArea::removeVibrato(GraphicsNote *p) {
    ItemList<Mode2Handler> list;
    for (int i = 0; i < qDragOut.selectedNotes.size(); ++i) {
        GraphicsNote *c = qDragOut.selectedNotes.at(i);
        Mode2Handler *s = c->curves();
        if (!s->Vibrato.isEmpty()) {
            s->clearVibrato();
            list.insertAuto(s);
        }
        s->note()->updateComponents();
    }

    saveScatterCore(list, true);
}
