#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../EnvelopeHandler.h"

void EnvelopeHandler::adjustGeometry() {
    int currentWidth = m_editor->ptrs()->currentWidth;
    int currentHeight = m_editor->ptrs()->currentHeight;

    double voiceStartPlusTime = m_note->convertTimeToTick(m_note->inPoint());
    double voiceEndPlusTime = m_note->convertTimeToTick(m_note->outPoint()) -
                              m_note->convertTimeToTick(m_note->duration());

    QRectF realNoteRect;

    realNoteRect.setLeft(m_note->headPos().x() + voiceStartPlusTime / 480 * currentWidth);
    realNoteRect.setRight(m_note->tailPos().x() + voiceEndPlusTime / 480 * currentWidth);

    realNoteRect.setTop(m_note->y() - currentHeight);
    realNoteRect.setBottom(m_note->y() + currentHeight);

    m_geometry = m_activeScope = realNoteRect;
}

void EnvelopeHandler::adjustPoints() {
    GraphicsPoint *p;
    int i;

    QList<QControlPoint> arr = toCorrectPoints(RelativePoints);
    for (i = 0; i < Points.size(); ++i) {
        p = Points[i];

        QControlPoint tp = arr[i];
        p->TPoint = tp;
        double posX = convertValueToPosX(tp.mX);
        double posY = convertValueToPosY(tp.mY);

        p->setLocation(posX, posY);
    }

    // Limit leftmost and rightmost
    limitAllPoints();
}
