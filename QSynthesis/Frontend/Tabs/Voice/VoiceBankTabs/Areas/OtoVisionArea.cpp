#include "OtoVisionArea.h"
#include "../VoiceBankGroup.h"

#define MIN(x, y) (x) < (y) ? (x) : (y)
#define MAX(x, y) (x) > (y) ? (x) : (y)

OtoVisionArea::OtoVisionArea(VoiceBankTab *tab,QWidget *parent) : VoiceBankArea(tab, parent) {
    init();
}

OtoVisionArea::~OtoVisionArea() {
}

void OtoVisionArea::initExtern() {
}

void OtoVisionArea::setSampleAndIndex(const QGenonSettings &genon, int index) {
    vision->setSample(genon);
    vision->setIndex(index);
    limitWidth();

    const QWaveInfo &wave = vision->waveInfo();
    if (!wave.isEmpty()) {
        m_ptrs->playerArea->setMedia(genon, wave.duration(), wave.sampleRate(), wave.bitPerSample(),
                                     wave.channels());
    } else {
        m_ptrs->playerArea->removeMedia();
    }
}

void OtoVisionArea::reset() {
    vision->reset();
}

bool OtoVisionArea::editing() const {
    return m_editing;
}

void OtoVisionArea::init() {
    m_editing = false;

    mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);

    scroll = new WaveformScrollArea(this);
    vision = new WaveformArea(scroll);
    scroll->setScene(vision);

    mainLayout->addWidget(scroll);
    setLayout(mainLayout);

    connect(vision, &WaveformArea::editing, this, &OtoVisionArea::handleEditing);
    connect(vision, &WaveformArea::editOver, this, &OtoVisionArea::handleEditOver);

    connect(scroll, &WaveformScrollArea::horizontalZoomRequested, this,
            &OtoVisionArea::handleHorizontalZoom);

    limitWidth();

    m_ptrs->otoVision = vision;
}

int OtoVisionArea::minWidth() const {
    return 800;
}

void OtoVisionArea::limitWidth() {
    if (vision->width() < minWidth()) {
        scroll->horizontalScrollBar()->setValue(0);
        vision->setWidth(minWidth());
    }
}

void OtoVisionArea::resizeEvent(QResizeEvent *event) {
    limitWidth();
}
