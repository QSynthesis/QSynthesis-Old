#include "TrackContent.h"

#include "../../Areas/Tracks/BlocksArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../TuningGroup.h"

TrackContent::TrackContent(ItemList<GraphicsNote> &notesList, BlocksArea *parent)
    : QWidget(parent), m_parent(parent), notesList(notesList) {
    m_width = 48;

    m_midiColor = QColor(0x0060C0);
    m_backColor = Qt::white;
}

TrackContent::~TrackContent() {
}

void TrackContent::adjustWidth() {
    //    int totalLength =
    //        notesList.isEmpty() ? 0 : (notesList.back()->tick() + notesList.back()->Note.length);

    setFixedWidth(m_parent->ptrs()->currentSections * 4 * m_width);
    update();
}

void TrackContent::onLengthChanged() {
    adjustWidth();
}

double TrackContent::sectionWidth() const {
    return m_width;
}

void TrackContent::setSectionWidth(double value) {
    m_width = value;
    adjustWidth();
}

QColor TrackContent::midiColor() const {
    return m_midiColor;
}

void TrackContent::setMidiColor(const QColor &midiColor) {
    m_midiColor = midiColor;

    update();
    emit colorChanged();
}

QColor TrackContent::backColor() const {
    return m_backColor;
}

void TrackContent::setBackColor(const QColor &backColor) {
    m_backColor = backColor;

    update();
    emit colorChanged();
}

void TrackContent::moveEvent(QMoveEvent *event) {
    emit moved(pos());
}

void TrackContent::resizeEvent(QResizeEvent *event) {
    emit resized(size());
}

void TrackContent::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipRegion(event->region());

    int length = 0;

    int highest = 83, lowest = 36;
    if (notesList.empty()) {
        return;
    }
    for (int i = 0; i < notesList.size(); i++) {
        int noteNum = notesList.at(i)->Note.noteNum;
        highest = (noteNum > highest) ? noteNum : highest;
        lowest = (noteNum < lowest) ? noteNum : lowest;
    }

    int midiH = 4;
    double unitH = double(height() - midiH) / (highest - lowest);

    painter.setPen(Qt::NoPen);
    painter.setBrush(m_midiColor);

    for (int i = 0; i < notesList.size(); i++) {
        int l = notesList[i]->Note.length;
        int n = notesList[i]->Note.noteNum;

        double x = double(length) / 480 * m_width;
        double y = (highest - n) * unitH;
        double w = double(l) / 480 * m_width;

        painter.drawRect(x, y, w, midiH);

        length += l;
    }
}
