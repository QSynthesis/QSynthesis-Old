#include "../../Editor/Areas/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../Mode2Handler.h"

void Mode2Handler::fromNotePoints() {
    replacePoints(m_note->Note.Mode2Pitch);
}

void Mode2Handler::toNotePoints() {
    m_note->Note.Mode2Pitch.clear();
    for (int i = 0; i < Points.size(); ++i) {
        GraphicsPoint *p = Points[i];
        if (p->specialPos() == Qs::Rightmost) {
            p->TPoint.mY = 0;
        } else if (p->specialPos() == Qs::Leftmost && !(prevNote() && prevNote()->isRest())) {
            p->TPoint.mY = 0;
        }
        m_note->Note.Mode2Pitch.push_back(p->TPoint);
    }
    ::insertSort(m_note->Note.Mode2Pitch);
}

bool Mode2Handler::removePoints(const QList<GraphicsPoint *> &points) {
    QList<GraphicsPoint *> filtered = points;

    if (Points.size() - filtered.size() < 2) {
        int leftIndex = filtered.indexOf(firstPoint());
        if (leftIndex >= 0) {
            filtered.removeAt(leftIndex);
        }

        int rightIndex = filtered.indexOf(lastPoint());
        if (rightIndex >= 0) {
            filtered.removeAt(rightIndex);
        }
    }

    return ScopeHandler::removePoints(filtered);
}

void Mode2Handler::clearPoints() {
    removeAllPoints();
}

void Mode2Handler::makeDefaultPoints() {
    replacePoints(Mode2Handler::defaultPortamento);
}
