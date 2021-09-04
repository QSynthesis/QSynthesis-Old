#include "../../Areas/Editor/NotesArea.h"
#include "../../Areas/Editor/PianoArea.h"
#include "../../Areas/Editor/SectionsArea.h"
#include "../../Areas/Params/LiftersArea.h"
#include "../../Modules/Scrolls/NotesScrollArea.h"
#include "../../TuningGroup.h"
#include "../EditorInterface.h"

#include <QScrollBar>

void EditorInterface::zoomHorizontally(int delta) {
    if (notesArea->isLyricEditing()) {
        return;
    }
    QPoint relativePos = notesScroll->mapFromGlobal(QCursor::pos());
    QPointF absPos = notesScroll->mapToScene(relativePos);

    // Calculate target coordinates
    int fromX = relativePos.x();

    if (fromX < 0) {
        fromX = 0;
    } else if (fromX > notesScroll->width()) {
        fromX = notesScroll->width();
    }

    int fromW = m_ptrs->currentWidth;
    int toW = m_ptrs->currentWidth + delta / 12;

    if (toW < 12) {
        toW = 12;
    }
    if (toW > 480) {
        toW = 480;
    }

    int fromAbs = absPos.x() - (relativePos.x() - fromX);
    int toX = fromX - fromAbs * double(toW) / (fromW);

    if (toX > 0) {
        toX = 0;
    }

    m_ptrs->currentWidth = toW;

    notesArea->adjustSize();
    sectionsArea->adjustWidth();
    m_ptrs->liftersArea->adjustWidth();

    QScrollBar *bar = notesScroll->horizontalScrollBar();
    bar->setValue(-toX);
}

void EditorInterface::zoomVertically(int delta) {
    if (notesArea->isLyricEditing()) {
        return;
    }
    QPoint relativePos = notesScroll->mapFromGlobal(QCursor::pos());
    QPointF absPos = notesScroll->mapToScene(relativePos);

    // Calculate target coordinates
    int fromY = relativePos.y();

    if (fromY < 0) {
        fromY = 0;
    } else if (fromY > notesScroll->height()) {
        fromY = notesScroll->height();
    }

    int fromH = m_ptrs->currentHeight;
    int toH = m_ptrs->currentHeight + delta / 12;

    if (toH < 12) {
        toH = 12;
    }
    if (toH > 60) {
        toH = 60;
    }

    int fromAbs = absPos.y() - (relativePos.y() - fromY);
    int toY = fromY - fromAbs * double(toH) / (fromH);

    if (toY > 0) {
        toY = 0;
    }

    m_ptrs->currentHeight = toH;
    notesArea->adjustSize();
    pianoArea->adjustHeight();

    QScrollBar *bar = notesScroll->verticalScrollBar();
    bar->setValue(-toY);
}

void EditorInterface::moveHorizontally(int delta) {
    QScrollBar *bar = notesScroll->horizontalScrollBar();
    bar->setValue(bar->value() + delta);
}

void EditorInterface::moveVertically(int delta) {
    QScrollBar *bar = notesScroll->verticalScrollBar();
    bar->setValue(bar->value() + delta);
}
