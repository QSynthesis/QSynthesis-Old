#include "OtoVisionArea.h"
#include "../VoiceBankGroup.h"
#include "mainwindow.h"

#define MIN(x, y) (x) < (y) ? (x) : (y)
#define MAX(x, y) (x) > (y) ? (x) : (y)

OtoVisionArea::OtoVisionArea(VoiceBankTab *tab, QWidget *parent) : VoiceBankArea(tab, parent) {
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
    mainLayout->setMargin(10);

    scroll = new WaveformScrollArea(this);
    vision = new WaveformArea(scroll);
    scroll->setScene(vision);

    mainLayout->addWidget(scroll);
    setLayout(mainLayout);

    connect(vision, &WaveformArea::editing, this, &OtoVisionArea::handleEditing);
    connect(vision, &WaveformArea::editOver, this, &OtoVisionArea::handleEditOver);

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

void OtoVisionArea::wheelEvent(QWheelEvent *event) {
    if (editing()) {
        return;
    }

    Qt::KeyboardModifiers c = event->modifiers(); // 当前辅助组合键
    QPoint delta = event->angleDelta();           // 滚轮移动方向

    if (delta.y() != 0) {
        if (c == MainWindow::config.wave.zoomHorizontally) {
            zoomHorizontally(delta.y() * 2);
        }
    }
    return VoiceBankArea::wheelEvent(event);
}

void OtoVisionArea::resizeEvent(QResizeEvent *event) {
    limitWidth();
}
