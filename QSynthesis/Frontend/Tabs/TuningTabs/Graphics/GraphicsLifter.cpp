#include "GraphicsLifter.h"
#include "../Areas/Params/LiftersArea.h"
#include "../Scrolls/LiftersScrollArea.h"
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
    connect(qViewIn, &LiftersScrollArea::themeUpdated, this, &GraphicsLifter::updateColorTheme);
}

GraphicsLifter::~GraphicsLifter() {
}

void GraphicsLifter::updateColorTheme() {
    m_activeColor = qViewIn->lifterActive();
    m_activeHColor = qViewIn->lifterActiveH();
    m_inactiveColor = qViewIn->lifterInactive();
    m_inactiveHColor = qViewIn->lifterInactiveH();
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
