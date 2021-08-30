#include "EditorInterface.h"
#include "../Areas/Editor/NotesArea.h"
#include "../Areas/Editor/PianoArea.h"
#include "../Areas/Editor/SectionsArea.h"
#include "../Forms/EditorForm.h"
#include "../Modules/Scrolls/NoneScrollArea.h"
#include "../Modules/Scrolls/NotesScrollArea.h"
#include "../TuningGroup.h"
#include "mainwindow.h"

#include <QDynamicPropertyChangeEvent>
#include <QPushButton>
#include <QScrollBar>
#include <QWheelEvent>

EditorInterface::EditorInterface(EditorForm *parent) : BaseInterface(parent) {
    m_ptrs = parent->ptrs();

    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    sectionsScroll = new NoneScrollArea();
    pianoScroll = new NoneScrollArea();
    notesScroll = new NotesScrollArea();

    notesScroll->setFrameStyle(QFrame::NoFrame);

    sectionsArea = new SectionsArea(this, sectionsScroll);
    pianoArea = new PianoArea(this, pianoScroll);
    notesArea = new NotesArea(this, notesScroll);

    sectionsScroll->setWidget(sectionsArea);
    pianoScroll->setWidget(pianoArea);
    notesScroll->setScene(notesArea);

    QWidget *emptyRow = new QWidget(this);
    QWidget *emptyRect = new QWidget(this);

    mainLayout->addWidget(emptyRow, 0, 0, 1, 2);
    mainLayout->addWidget(emptyRect, 1, 0);
    mainLayout->addWidget(sectionsScroll, 1, 1);
    mainLayout->addWidget(pianoScroll, 2, 0);
    mainLayout->addWidget(notesScroll, 2, 1);

    setLayout(mainLayout);

    // Set Pointers
    m_ptrs->sectionsArea = sectionsArea;
    m_ptrs->pianoArea = pianoArea;
    m_ptrs->notesArea = notesArea;

    m_ptrs->sectionsScroll = sectionsScroll;
    m_ptrs->pianoScroll = pianoScroll;
    m_ptrs->notesScroll = notesScroll;

    connect(notesScroll->horizontalScrollBar(), &QScrollBar::valueChanged, this,
            &EditorInterface::handleHorizontalMove);
    connect(notesScroll->verticalScrollBar(), &QScrollBar::valueChanged, this,
            &EditorInterface::handleVerticalMove);

    installEventFilter(this);

    // Init
    emptyRow->setFixedHeight(5);
    emptyRect->setFixedHeight(15);

    sectionsArea->setFixedHeight(40);
    sectionsScroll->setFixedHeight(sectionsArea->height());

    pianoArea->setFixedWidth(120);
    pianoScroll->setFixedWidth(pianoArea->width());

    notesArea->adjustSize();
    sectionsArea->adjustWidth();
    pianoArea->adjustHeight();
}

EditorInterface::~EditorInterface() {
}

void EditorInterface::setVisionStatus(Qs::Panels::Editor mode) {
    m_ptrs->notesArea->setNotesEnabled(mode == Qs::Panels::Note);
    m_ptrs->notesArea->setPitchesEnabled(mode == Qs::Panels::Pitch);
    m_ptrs->notesArea->setEnvelopesEnabled(mode == Qs::Panels::Envelope);
}

TuningGroup *EditorInterface::ptrs() const {
    return m_ptrs;
}

void EditorInterface::wheelEvent(QWheelEvent *event) {
    Qt::KeyboardModifiers c = event->modifiers();
    QPoint delta = event->angleDelta();

    if (delta.isNull()) {
        return;
    }

    if (delta.x() * delta.y() == 0) {
        delta.ry() = delta.x() + delta.y();
        delta.rx() = 0;
    }

#ifdef __APPLE__
    if (c == Qt::NoModifier) {
        if (delta.x() != 0) {
            moveHorizontally(delta.x());
        }
        if (delta.y() != 0) {
            moveVertically(delta.y());
        }
    } else {
        if (delta.x() * delta.y() == 0) {
            delta.ry() = delta.x() + delta.y();
            delta.rx() = 0;
        }
        if (c == MainWindow::config.notes.zoomHorizontally) {
            zoomHorizontally(delta.y());
        } else if (c == MainWindow::config.notes.zoomVertically) {
            zoomVertically(delta.y());
        } else if (c == MainWindow::config.notes.moveHorizontally) {
            notesScroll->horizontalScrollBar()->triggerAction(
                delta.y() < 0 ? QAbstractSlider::SliderSingleStepAdd
                              : QAbstractSlider::SliderSingleStepSub);
        } else if (c == MainWindow::config.notes.moveVertically) {
            notesScroll->verticalScrollBar()->triggerAction(
                delta.y() < 0 ? QAbstractSlider::SliderSingleStepAdd
                              : QAbstractSlider::SliderSingleStepSub);
        }
    }
#else
    if (delta.x() == 0) {
        if (c == MainWindow::config.notes.zoomHorizontally) {
            zoomHorizontally(delta.y());
        } else if (c == MainWindow::config.notes.zoomVertically) {
            zoomVertically(delta.y());
        } else if (c == MainWindow::config.notes.moveHorizontally) {
            notesScroll->horizontalScrollBar()->triggerAction(
                delta.y() < 0 ? QAbstractSlider::SliderSingleStepAdd
                              : QAbstractSlider::SliderSingleStepSub);

        } else if (c == MainWindow::config.notes.moveVertically) {
            notesScroll->verticalScrollBar()->triggerAction(
                delta.y() < 0 ? QAbstractSlider::SliderSingleStepAdd
                              : QAbstractSlider::SliderSingleStepSub);
        }
    }
#endif
}

bool EditorInterface::eventFilter(QObject *obj, QEvent *event) {
    return BaseInterface::eventFilter(obj, event);
}

void EditorInterface::handleHorizontalMove(int value) {
    notesArea->update();
    sectionsScroll->setValueX(value);
}

void EditorInterface::handleVerticalMove(int value) {
    notesArea->update();
    pianoScroll->setValueY(value);
}
