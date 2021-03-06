#include "GraphicsNote.h"
#include "../Editor/Areas/NotesArea.h"
#include "../Params/Areas/LiftersArea.h"
#include "../Scrolls/NotesScrollArea.h"
#include "../TuningGroup.h"

GraphicsNote::GraphicsNote(NotesArea *editor, QGraphicsItem *parent)
    : GraphicsDragger(parent), m_editor(editor) {
    init();
}

GraphicsNote::~GraphicsNote() {
    m_curves->deleteLater();
    m_envelope->deleteLater();
}

void GraphicsNote::updateColorTheme() {
    m_lyricColor = qViewIn->noteLyric();
    m_restLineColor = qViewIn->noteRestLine();
    m_restFillColor = qViewIn->noteRestFill();
    m_listedLineColor = qViewIn->noteListedLine();
    m_listedFillColor = qViewIn->noteListedFill();
    m_unlistedLineColor = qViewIn->noteUnlistedLine();
    m_unlistedFillColor = qViewIn->noteUnlistedFill();
    m_selectColor = qViewIn->noteSelect();
    m_lyricBlockColor = qViewIn->noteLyricBlock();
    m_paramsColor = qViewIn->noteParams();
    m_highlightColor = qViewIn->noteHighlight();

    update();
}

void GraphicsNote::init() {
    m_element = GraphicsDragger::Note;
    m_prev = m_next = m_MPrev = m_MNext = nullptr;

    m_movable = m_editor->notesEnabled();
    m_block = m_editor->notesVisible();
    m_display = m_editor->paramsVisible();

    m_stretch = false;
    m_drawing = false;
    m_highlighted = false;

    m_time = 0;
    m_tick = 0;
    m_tempo = Utau::DEFAULT_VALUE_TEMPO;

    m_lengthRef = 0;

    m_lifter = nullptr;
    m_screen = nullptr;

    m_curves = new Mode2Handler(this, m_editor);
    m_envelope = new EnvelopeHandler(this, m_editor);

    setFlag(ItemIsFocusable);

    updateColorTheme();
    connect(qViewIn, &NotesScrollArea::noteThemeUpdated, this, &GraphicsNote::updateColorTheme);
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
    delete m_screen;
    m_screen = nullptr;
}

QVariant GraphicsNote::itemChange(GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}
