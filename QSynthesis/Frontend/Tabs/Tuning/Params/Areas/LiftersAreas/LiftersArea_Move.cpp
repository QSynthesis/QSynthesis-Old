#include "../../../Editor/Areas/NotesArea.h"
#include "../../../Graphics/GraphicsNote.h"
#include "../../../TuningGroup.h"
#include "../LiftersArea.h"

void LiftersArea::prepareMove(GraphicsLifter *p) {
    qDragOut.filter(GraphicsDragger::Note);
    if (!p->note()->isSelected()) {
        qDragOut.removeAll();
        qDragOut.addOne(p->note());
    }
    for (int i = 0; i < qDragOut.selectedNotes.size(); ++i) {
        qDragOut.addOne(qDragOut.selectedNotes.at(i)->lifter());
    }
}

void LiftersArea::refreshMove(GraphicsLifter *p) {
    for (auto it = qDragOut.selectedHandles.begin(); it != qDragOut.selectedHandles.end(); ++it) {
        (*it)->update();
    }
}

void LiftersArea::endMove(GraphicsLifter *p) {
    qDragOut.filter(GraphicsDragger::Note);
    m_ptrs->notesArea->afterModifyLifters(p->prop());
}
