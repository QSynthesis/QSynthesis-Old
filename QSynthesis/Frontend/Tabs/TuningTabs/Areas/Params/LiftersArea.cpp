#include "LiftersArea.h"
#include "../../Graphics/GraphicsLifter.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../Interfaces/ParamsInterface.h"
#include "../../Scrolls/LiftersScrollArea.h"
#include "../../TuningGroup.h"
#include "mainwindow.h"

LiftersArea::LiftersArea(ParamsInterface *editor, LiftersScrollArea *view) : GraphicsArea(view) {
    m_ptrs = editor->ptrs();

    m_standardHeight = 0;

    connect(this, &QGraphicsScene::sceneRectChanged, this, &LiftersArea::handleSceneRectChanged);

    updateColorTheme();
    connect(view, &LiftersScrollArea::editorThemeUpdated, this, &LiftersArea::updateColorTheme);
}

LiftersArea::~LiftersArea() {
}

LiftersScrollArea *LiftersArea::view() const {
    return qobject_cast<LiftersScrollArea *>(m_view);
}

void LiftersArea::updateColorTheme() {
    m_timeLineColor = view()->editorTimeLine();
    m_sectionLineColor = view()->editorSectionLine();
    m_backColor = view()->editorBack();

    updateBackground();
}

TuningGroup *LiftersArea::ptrs() const {
    return m_ptrs;
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
    if (p->isSelected()) {
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
