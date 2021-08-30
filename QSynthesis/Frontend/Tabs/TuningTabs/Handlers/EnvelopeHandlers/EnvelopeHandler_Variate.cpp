#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../EnvelopeHandler.h"

void EnvelopeHandler::fromNotePoints() {
    replacePoints(m_note->Note.envelope);
}

void EnvelopeHandler::toNotePoints() {
    QList<QControlPoint> arr;
    for (int i = 0; i < Points.size(); ++i) {
        GraphicsPoint *p = Points[i];
        arr.append(p->TPoint);
    }
    RelativePoints = fromCorrectPoints(arr);
    if (RelativePoints != EnvelopeHandler::defaultEnvelope) {
        m_note->Note.envelope = RelativePoints;
    } else {
        m_note->Note.envelope.clear();
    }
}

void EnvelopeHandler::replacePoints(const QList<QControlPoint> &arr) {
    RelativePoints = arr;
    if (RelativePoints.size() < 4) {
        RelativePoints = EnvelopeHandler::defaultEnvelope;
    }
    ScopeHandler::replacePoints(toCorrectPoints(RelativePoints));
}

bool EnvelopeHandler::removePoints(const QList<GraphicsPoint *> &points) {
    int index;
    if (Points.size() == 4 || points.isEmpty()) {
        return false;
    } else {
        index = Points.indexOf(points.front());
    }
    if (ScopeHandler::removePoints({Points[index]})) {
        return true;
    } else {
        return false;
    }
}

void EnvelopeHandler::makeDefaultPoints() {
    replacePoints(EnvelopeHandler::defaultEnvelope);
}
