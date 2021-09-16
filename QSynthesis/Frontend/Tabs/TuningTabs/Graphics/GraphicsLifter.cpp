#include "GraphicsLifter.h"
#include "QUtauConstants.h"
#include "mainwindow.h"

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

    updateColorTheme();
    connect(qTheme, &ColorTheme::updated, this, &GraphicsLifter::updateColorTheme);
}

GraphicsLifter::~GraphicsLifter() {
}

void GraphicsLifter::updateColorTheme() {
    m_activeColor = qTheme->lifter_active;
    m_activeHColor = qTheme->lifter_activeH;
    m_inactiveColor = qTheme->lifter_inactive;
    m_inactiveHColor = qTheme->lifter_inactiveH;
    update();
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
