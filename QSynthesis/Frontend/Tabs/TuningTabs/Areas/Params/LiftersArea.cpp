#include "LiftersArea.h"
#include "../../Graphics/GraphicsLifter.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Interfaces/ParamsInterface.h"
#include "../../Modules/Scrolls/LiftersScrollArea.h"
#include "../../TuningGroup.h"

LiftersArea::LiftersArea(ParamsInterface *editor, LiftersScrollArea *parent)
    : QGraphicsScene(parent), m_view(parent) {
    m_ptrs = editor->ptrs();

    m_timeLineColor = QColor(0xD4D4D4);
    m_sectionLineColor = QColor(0xBFBFBF);
    m_backColor = QColor(0xFFFFFF);

    m_standardHeight = 0;

    connect(this, &QGraphicsScene::sceneRectChanged, this, &LiftersArea::handleSceneRectChanged);
}

LiftersArea::~LiftersArea() {
}

TuningGroup *LiftersArea::ptrs() const {
    return m_ptrs;
}

LiftersScrollArea *LiftersArea::view() const {
    return m_view;
}

Qs::Panels::Params LiftersArea::prop() const {
    return m_prop;
}

void LiftersArea::setProp(const Qs::Panels::Params &prop) {
    m_prop = prop;
    for (int i = 0; i < LiftersList.size(); ++i) {
        LiftersList.at(i)->setProp(GraphicsLifter::Props(prop));
    }
}

double LiftersArea::standardHeight() const {
    return m_standardHeight;
}

GraphicsLifter *LiftersArea::createLifter(GraphicsNote *p) {
    GraphicsLifter *lifter = new GraphicsLifter(p, this);
    addItem(lifter);

    lifter->setZValue(lifterZIndex);
    LiftersList.append(lifter);

    lifter->setProp(GraphicsLifter::Props(m_prop));
    return lifter;
}

void LiftersArea::removeLifter(GraphicsLifter *p) {
    if (p->isSelected()){
        qDragOut.removeOne(p);
    }
    LiftersList.removeOne(p);
    removeItem(p);
    delete p;
}

void LiftersArea::handleSceneRectChanged(const QRectF &rect) {
    if (rect.height() != m_standardHeight) {
        m_standardHeight = rect.height();
        for (int i = 0; i < LiftersList.size(); ++i) {
            LiftersList.at(i)->adjustSize();
        }
    }
    updateBackground();
}
