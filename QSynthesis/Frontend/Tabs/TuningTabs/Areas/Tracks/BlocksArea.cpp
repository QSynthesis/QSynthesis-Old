#include "BlocksArea.h"
#include "../../Interfaces/TracksInterface.h"
#include "../../Modules/Elements/TrackContent.h"
#include "../../TuningGroup.h"

BlocksArea::BlocksArea(TracksInterface *editor, QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground);
    m_ptrs = editor->ptrs();

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    // mainLayout->setSpacing(0);

    setLayout(mainLayout);
}

BlocksArea::~BlocksArea() {
}

TuningGroup *BlocksArea::ptrs() const {
    return m_ptrs;
}

void BlocksArea::addTrack(ItemList<GraphicsNote> &notes) {
    TrackContent *content = new TrackContent(notes, this);
    content->setFixedHeight(75);
    content->setSectionWidth(m_width);
    content->show();

    // connect(notes, &NotesArea::lengthChanged, content, &TrackContent::onLengthChanged);

    Tracks.push_back(content);
    mainLayout->addWidget(content);

    adjustSize();
}

void BlocksArea::adjustTrack(int n) {
    Tracks[n]->adjustWidth();
    adjustSize();
}

double BlocksArea::sectionWidth() const {
    return m_width;
}

void BlocksArea::setSectionWidth(double width) {
    m_width = width;
    for (auto it = Tracks.begin(); it != Tracks.end(); ++it) {
        (*it)->setSectionWidth(width);
    }
}
