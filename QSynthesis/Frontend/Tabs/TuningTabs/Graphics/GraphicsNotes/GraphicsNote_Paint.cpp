#include "../../Areas/Editor/NotesArea.h"
#include "../../TuningGroup.h"
#include "../GraphicsNote.h"

void GraphicsNote::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
    if (isSelected()) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(0, 0, 0, 48));
        painter->drawRoundedRect(rect(), 3, 3);
    }

    m_handler->drawNote(painter);
}
