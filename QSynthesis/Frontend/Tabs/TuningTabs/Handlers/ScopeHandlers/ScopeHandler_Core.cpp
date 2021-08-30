#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsPoint.h"
#include "../../TuningGroup.h"
#include "../ScopeHandler.h"

GraphicsPoint *ScopeHandler::createPointCore() {
    GraphicsPoint *p = new GraphicsPoint(this, m_editor);
    m_editor->addItem(p);
    p->setZValue(m_editor->pointZIndex);
    p->setVisible(m_solid);

    return p;
}

void ScopeHandler::removePointCore(GraphicsPoint *p) {
    if (p->isInvolved()) {
        qDragIn.removeOneT(p);
    }
    if (p->isSelected()) {
        qDragIn.removeOne(p);
    }
    m_editor->removeItem(p);
    delete p;
}
