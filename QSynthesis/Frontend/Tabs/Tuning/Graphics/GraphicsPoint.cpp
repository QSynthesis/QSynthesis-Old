#include "GraphicsPoint.h"
#include "../Controllers/ScopeHandler.h"

GraphicsPoint::GraphicsPoint(ScopeHandler *scope, NotesArea *editor, QGraphicsItem *parent)
    : GraphicsDragger(parent), m_editor(editor), m_scope(scope) {
    init();
}

GraphicsPoint::~GraphicsPoint() {
}

void GraphicsPoint::init() {
    m_element = GraphicsDragger::Point;

    m_radius = 10;

    m_hovered = false;
    m_specialPos = Qs::Middle;
    m_drawing = false;

    setTopLeft(-m_radius, -m_radius);
    setSize(2 * m_radius, 2 * m_radius);
}

void GraphicsPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                         QWidget *widget) {
    m_scope->drawPoint(painter, this);
}
