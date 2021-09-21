#include "GraphicsLines.h"
#include "../Areas/Editor/NotesArea.h"
#include "../Handlers/EnvelopeHandler.h"
#include "../Handlers/Mode2Handler.h"
#include "GraphicsNote.h"

GraphicsLines::GraphicsLines(GraphicsNote *note, NotesArea *editor, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_note(note), m_editor(editor) {
    m_rect = NO_RECTF;
}

GraphicsLines::~GraphicsLines() {
}

GraphicsNote *GraphicsLines::note() const {
    return m_note;
}

NotesArea *GraphicsLines::editor() const {
    return m_editor;
}

void GraphicsLines::updateLocation() {
    prepareGeometryChange();
    setPos(m_note->x(), 0);
}

void GraphicsLines::updateSize() {
    prepareGeometryChange();
    m_rect.setSize(QSizeF(m_note->width(), m_editor->height()));
    update();
}

int GraphicsLines::type() const {
    return UserType + 1;
}

QPainterPath GraphicsLines::shape() const {
    return QPainterPath();
}

void GraphicsLines::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget) {
    m_note->curves()->drawMode1(painter);
    m_note->curves()->drawMode2(painter);
    m_note->curves()->drawVibrato(painter);
    m_note->curves()->drawVibratoEditor(painter);
    m_note->envelope()->drawEnvelope(painter);
}

QRectF GraphicsLines::boundingRect() const {
    Mode2Handler *curves = m_note->curves();
    EnvelopeHandler *envelope = m_note->envelope();

    QRectF rect(curves->visionScope());

    rect.setLeft(qMin(curves->visionScope().left(), envelope->visionScope().left()));
    rect.setRight(qMax(curves->visionScope().right(), envelope->visionScope().right()));

    rect.moveLeft(rect.x() - x());
    rect.moveTop(rect.y() - y());

    return rect;
}
