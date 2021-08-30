#include "GraphicsLifter.h"
#include "QUtauConstants.h"

int GraphicsLifter::Radius = 6;

GraphicsLifter::GraphicsLifter(GraphicsNote *note, LiftersArea *editor, QGraphicsItem *parent)
    : GraphicsLineHandle(Qt::Vertical, parent), m_note(note), m_editor(editor) {
    m_element = GraphicsDragger::Lifter;
    m_prop = Undefined;

    m_active = true;
    m_highlighted = false;

    m_values[Intensity] = DEFAULT_VALUE_INTENSITY;
    m_values[Modulation] = DEFAULT_VALUE_MODULATION;
    m_values[Velocity] = DEFAULT_VALUE_VELOCITY;

    m_activeColor = QColor(0x79BBEE);
    m_inactiveColor = Qt::gray;

    m_activeHColor = QColor(QColorConstants::Svg::pink);
    m_inactiveHColor = Qt::lightGray;
}

GraphicsLifter::~GraphicsLifter() {
}

GraphicsNote *GraphicsLifter::note() const {
    return m_note;
}

LiftersArea *GraphicsLifter::editor() const {
    return m_editor;
}

void GraphicsLifter::fromHandle() {
    m_values[m_prop] = convertRatioToProp(m_prop, 1 - value());
}
