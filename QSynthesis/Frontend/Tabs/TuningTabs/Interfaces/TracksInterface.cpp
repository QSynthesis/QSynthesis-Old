#include "TracksInterface.h"
#include "../Areas/Editor/NotesArea.h"
#include "../Forms/TracksForm.h"
#include "../Modules/Elements/TrackContent.h"
#include "../Modules/Elements/TrackHead.h"
#include "../TuningGroup.h"

#include <QScrollBar>

TracksInterface::TracksInterface(TracksForm *parent) : BaseInterface(parent) {
    m_ptrs = parent->ptrs();

    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    btnMenu = new VectorButton(true, QSizeF(2, 2), this);
    btnMenu->setProperty("type", "tracks-menu");

    btnMenu->setIcons(":/images/NormalMenuBtn.svg");
    btnMenu->setFixedSize(20, 20);
    connect(btnMenu, &VectorButton::clicked, this, &TracksInterface::handleMenuBtnClicked);

    topLeftLayout = new QHBoxLayout();
    topLeftLayout->addStretch();
    topLeftLayout->addWidget(btnMenu);

    sectionsScroll = new NoneScrollArea(this);
    sections = new SectionsLine(sectionsScroll);
    sectionsScroll->setWidget(sections);

    leftScroll = new NoneScrollArea(this);
    lefts = new HeadsArea(this, leftScroll); // Track Heads
    leftScroll->setWidget(lefts);

    rightScroll = new QScrollArea(this);
    rightScroll->setFrameShape(QFrame::NoFrame);
    rights = new BlocksArea(this, rightScroll); // Track Contents
    rightScroll->setWidget(rights);

    mainLayout->addLayout(topLeftLayout, 0, 0);
    mainLayout->addWidget(sectionsScroll, 0, 2);
    mainLayout->addWidget(leftScroll, 1, 0);

    QFrame *separator = new QFrame(this);
    separator->setProperty("type", "track-separator");
    separator->setFrameStyle(QFrame::VLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setFixedWidth(1);
    mainLayout->addWidget(separator, 0, 1, 2, 1);
    mainLayout->addWidget(rightScroll, 1, 2);
    mainLayout->setColumnStretch(2, 1);
    setLayout(mainLayout);

    m_ptrs->trackHeads = lefts;
    m_ptrs->trackBlocks = rights;

    m_ptrs->headsScroll = leftScroll;
    m_ptrs->blocksScroll = rightScroll;

    connect(rightScroll->horizontalScrollBar(), &QScrollBar::valueChanged, this,
            &TracksInterface::handleHorizontalMove);
    connect(rightScroll->verticalScrollBar(), &QScrollBar::valueChanged, this,
            &TracksInterface::handleVerticalMove);

    connect(lefts, &HeadsArea::voiceChanged, this, &TracksInterface::handleVoiceChanged);
    connect(lefts, &HeadsArea::resamplerChanged, this, &TracksInterface::handleResamplerChanged);
    connect(lefts, &HeadsArea::nameChanged, this, &TracksInterface::handleNameChanged);
    connect(lefts, &HeadsArea::flagsChanged, this, &TracksInterface::handleFlagsChanged);

    m_menu = new QMenu(this);

    sections->setFixedHeight(24);
    sectionsScroll->setFixedHeight(sections->height());

    lefts->setFixedWidth(350);
    leftScroll->setFixedWidth(lefts->width());

    sections->setSectionWidth(48);
    rights->setSectionWidth(48);

    initDefaultTrack();
}

TracksInterface::~TracksInterface() {
}

void TracksInterface::initDefaultTrack() {
    lefts->addTrack("", "", "", "");
    rights->addTrack(m_ptrs->notesArea->NotesList);
}

void TracksInterface::adjustDefaultTrack() {
    rights->adjustTrack(0);
    sections->setCount(m_ptrs->currentSections);
    sections->setFixedWidth(rights->width());
}

void TracksInterface::setVisionStatus(Qs::Panels::Tracks mode) {
    lefts->setHeadsMode(mode == Qs::Panels::Overview ? 1 : 2);
}

TuningGroup *TracksInterface::ptrs() const {
    return m_ptrs;
}

void TracksInterface::handleHorizontalMove(int value) {
    sectionsScroll->setValueX(value);
}

void TracksInterface::handleVerticalMove(int value) {
    leftScroll->setValueY(value);
}
