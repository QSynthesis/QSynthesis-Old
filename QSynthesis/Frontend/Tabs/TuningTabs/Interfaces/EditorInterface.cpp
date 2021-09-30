#include "EditorInterface.h"
#include "../Areas/Editor/NotesArea.h"
#include "../Areas/Editor/PianoArea.h"
#include "../Areas/Editor/SectionsArea.h"
#include "../Forms/EditorForm.h"
#include "../Scrolls/NoneScrollArea.h"
#include "../Scrolls/NotesScrollArea.h"
#include "../TuningGroup.h"

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
    connect(notesScroll, &NotesScrollArea::horizontalZoomRequested, this,
            &EditorInterface::handleHorizontalZoom);
    connect(notesScroll, &NotesScrollArea::verticalZoomRequested, this,
            &EditorInterface::handleVerticalZoom);

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
    m_ptrs->notesArea->endEditingNote();
    m_ptrs->notesArea->setNotesEnabled(mode == Qs::Panels::Note);
    m_ptrs->notesArea->setPitchesEnabled(mode == Qs::Panels::Pitch);
    m_ptrs->notesArea->setEnvelopesEnabled(mode == Qs::Panels::Envelope);
}

TuningGroup *EditorInterface::ptrs() const {
    return m_ptrs;
}

void EditorInterface::wheelEvent(QWheelEvent *event) {
    m_ptrs->notesScroll->wheelEvent(event);
}

bool EditorInterface::eventFilter(QObject *obj, QEvent *event) {
    return BaseInterface::eventFilter(obj, event);
}

void EditorInterface::handleHorizontalMove(int value) {
    // notesArea->update();
    sectionsScroll->setValueX(value);
}

void EditorInterface::handleVerticalMove(int value) {
    // notesArea->update();
    pianoScroll->setValueY(value);
}

void EditorInterface::handleHorizontalZoom(int delta) {
    zoomHorizontally(delta);
}

void EditorInterface::handleVerticalZoom(int delta) {
    zoomVertically(delta);
}
