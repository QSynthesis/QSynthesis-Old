#include "HeadsArea.h"
#include "../../Interfaces/TracksInterface.h"
#include "../../Modules/Elements/TrackHead.h"
#include "../../TuningGroup.h"

HeadsArea::HeadsArea(TracksInterface *editor, QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_StyledBackground);
    m_ptrs = editor->ptrs();

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);

    setLayout(mainLayout);
}

HeadsArea::~HeadsArea() {
}

TuningGroup *HeadsArea::ptrs() const {
    return m_ptrs;
}

void HeadsArea::addTrack(const QString &resampler, const QString &flags, const QString &name,
                         const QString &voice) {
    TrackHead *head = new TrackHead(resampler, flags, name, voice, this);
    head->setFixedHeight(75);
    head->show();

    Tracks.push_back(head);
    mainLayout->addWidget(head);

    connect(head, &TrackHead::nameChanged, this, &HeadsArea::handleNameChanged);
    connect(head, &TrackHead::flagsChanged, this, &HeadsArea::handleFlagsChanged);
    connect(head, &TrackHead::voiceChanged, this, &HeadsArea::handleVoiceChanged);
    connect(head, &TrackHead::resamplerChanged, this, &HeadsArea::handleResamplerChanged);

    adjustSize();
}

void HeadsArea::setTrackResampler(int index, const QString &resampler) {
    TrackHead *head = Tracks.at(index);
    head->blockSignals(true);
    head->setResampler(resampler);
    head->blockSignals(false);

    emit resamplerChanged(index, resampler);
}

void HeadsArea::setTrackFlags(int index, const QString &flags) {
    TrackHead *head = Tracks.at(index);
    head->blockSignals(true);
    head->setFlags(flags);
    head->blockSignals(false);

    emit flagsChanged(index, flags);
}

void HeadsArea::setTrackName(int index, const QString &name) {
    TrackHead *head = Tracks.at(index);
    head->blockSignals(true);
    head->setName(name);
    head->blockSignals(false);

    emit nameChanged(index, name);
}

void HeadsArea::setTrackVoice(int index, const QString &voice) {
    TrackHead *head = Tracks.at(index);
    head->blockSignals(true);
    head->setVoiceDir(voice);
    head->blockSignals(false);

    emit voiceChanged(index, voice);
}

void HeadsArea::setHeadsMode(int n) {
    for (auto it = Tracks.begin(); it != Tracks.end(); ++it) {
        (*it)->setMode(n);
    }
}
