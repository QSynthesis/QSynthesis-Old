#include "ParamsInterface.h"
#include "../Areas/Editor/NotesArea.h"
#include "../Areas/Params/LiftersArea.h"
#include "../Areas/Params/ParamsDialArea.h"
#include "../Forms/ParamsForm.h"
#include "../Interfaces/EditorInterface.h"
#include "../Modules/Scrolls/LiftersScrollArea.h"
#include "../Modules/Scrolls/NotesScrollArea.h"
#include "../TuningGroup.h"
#include "mainwindow.h"

#include <QScrollBar>

ParamsInterface::ParamsInterface(ParamsForm *parent) : BaseInterface(parent) {
    m_ptrs = parent->ptrs();

    // Initialize Components
    mainLayout = new QHBoxLayout(this);

    // Controls Window
    liftersScroll = new LiftersScrollArea(this);
    liftersArea = new LiftersArea(this, liftersScroll);

    liftersScroll->setFrameShape(QFrame::NoFrame);
    liftersScroll->setScene(liftersArea);

    // Left Area
    dialArea = new ParamsDialArea(this, this);

    mainLayout->addWidget(dialArea);
    mainLayout->addWidget(liftersScroll);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    // Pointers
    m_ptrs->dialArea = dialArea;
    m_ptrs->liftersArea = liftersArea;
    m_ptrs->liftersScroll = liftersScroll;

    connect(m_ptrs->notesScroll->horizontalScrollBar(), &QScrollBar::valueChanged, this,
            &ParamsInterface::handleHorizontalMove);

    dialArea->setFixedWidth(120);

    liftersArea->adjustWidth();
}

ParamsInterface::~ParamsInterface() {
}

void ParamsInterface::setVisionStatus(Qs::Panels::Params mode) {
    dialArea->setScale(mode);
    liftersArea->setProp(mode);
}

TuningGroup *ParamsInterface::ptrs() const {
    return m_ptrs;
}

void ParamsInterface::wheelEvent(QWheelEvent *event) {
    Qt::KeyboardModifiers c = event->modifiers();
    if (c != MainWindow::config.notes.zoomHorizontally &&
        c != MainWindow::config.notes.moveHorizontally) {
        return;
    }
    QApplication::sendEvent(m_ptrs->editorContent, event);
}

void ParamsInterface::handleHorizontalMove(int value) {
    liftersScroll->horizontalScrollBar()->setValue(value);
}
