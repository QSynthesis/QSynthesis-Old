#include "GraphicsNote.h"
#include "../Areas/Editor/NotesArea.h"
#include "../Areas/Params/LiftersArea.h"
#include "../TuningGroup.h"
#include "mainwindow.h"

GraphicsNote::GraphicsNote(NotesArea *editor, QGraphicsItem *parent)
    : GraphicsDragger(parent), m_editor(editor) {
    init();
}

GraphicsNote::~GraphicsNote() {
    m_handler->deleteLater();
    m_curves->deleteLater();
    m_envelope->deleteLater();
}

void GraphicsNote::init() {
    m_element = GraphicsDragger::Note;
    m_prev = m_next = m_MPrev = m_MNext = nullptr;

    m_movable = true;
    m_stretch = false;
    m_drawing = false;

    m_time = 0;
    m_tick = 0;
    m_tempo = DEFAULT_VALUE_TEMPO;

    m_lengthRef = 0;

    m_handler = new NoteHandler(this, m_editor);
    m_curves = new Mode2Handler(this, m_editor);
    m_envelope = new EnvelopeHandler(this, m_editor);

    m_lifter = nullptr;
    m_screen = nullptr;

    setFlag(ItemIsFocusable);
}

void GraphicsNote::addLifter() {
    m_lifter = m_editor->ptrs()->liftersArea->createLifter(this);
}

void GraphicsNote::removeLifter() {
    m_editor->ptrs()->liftersArea->removeLifter(m_lifter);
    m_lifter = nullptr;
}

void GraphicsNote::addScreen() {
    m_screen = new GraphicsLines(this, m_editor);
    m_editor->addItem(m_screen);

    m_screen->setZValue(m_editor->linesZIndex);
}

void GraphicsNote::removeScreen() {
    m_editor->removeItem(m_screen);
    m_screen = nullptr;
}

QVariant GraphicsNote::itemChange(GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}
