#include "../../Editor/Areas/NotesArea.h"
#include "../../TuningGroup.h"
#include "../Elements/TrackContent.h"
#include "../Elements/TrackHead.h"
#include "../TracksForm.h"
#include "../TracksInterface.h"

void TracksInterface::setDefaultResampler(const QString &resampler) {
    lefts->setTrackResampler(0, resampler);
}

void TracksInterface::setDefaultFlags(const QString &flags) {
    lefts->setTrackFlags(0, flags);
}

void TracksInterface::setDefaultName(const QString &name) {
    lefts->setTrackName(0, name);
}

void TracksInterface::setDefaultVoice(const QString &voice) {
    lefts->setTrackVoice(0, voice);
}

QString TracksInterface::defaultResampler() const {
    return lefts->Tracks.front()->resampler();
}

QString TracksInterface::defaultName() const {
    return lefts->Tracks.front()->name();
}

QString TracksInterface::defaultFlags() const {
    return lefts->Tracks.front()->flags();
}

QString TracksInterface::defaultVoiceDir() const {
    return lefts->Tracks.front()->voiceDir();
}

void TracksInterface::handleVoiceChanged(int index, QString newVal) {
    if (index == 0) {
        m_ptrs->tab->switchToOtoReferenceMap(newVal);
    }
}

void TracksInterface::handleResamplerChanged(int index, QString newVal) {
}

void TracksInterface::handleNameChanged(int index, QString newVal) {
}

void TracksInterface::handleFlagsChanged(int index, QString newVal) {
}
