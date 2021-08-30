#include "SequenceTextData.h"
#include "QUtauStrings.h"

using namespace UtaProjectText;

// Project File Settings
SectionSettings::SectionSettings() {
    clear();
}

void SectionSettings::clear() {
    globalTempo = DEFAULT_VALUE_TEMPO;
    globalFlags = "";
    projectName = "";
    outputFileName = "";
    voiceDirectory = "";
    cacheDirectory = "";
    wavtoolPath = "";
    resamplerPath = "";
    isMode2 = true;
}

bool SectionSettings::operator==(const SectionSettings &another) const {
    return (globalTempo == another.globalTempo) && (globalFlags == another.globalFlags) &&
           (projectName == another.projectName) && (outputFileName == another.outputFileName) &&
           (voiceDirectory == another.voiceDirectory) &&
           (cacheDirectory == another.cacheDirectory) && (wavtoolPath == another.wavtoolPath) &&
           (resamplerPath == another.resamplerPath) && (isMode2 == another.isMode2);
}

bool SectionSettings::operator!=(const SectionSettings &another) const {
    return !((*this) == another);
}

// Project File Version
SectionVersion::SectionVersion() {
    clear();
}

void SectionVersion::clear() {
    version = UST_VERSION_1_2;
    charset = "";
}

// Project File Notes
bool SectionVersion::operator==(const SectionVersion &another) const {
    return (version == another.version);
}

bool SectionVersion::operator!=(const SectionVersion &another) const {
    return !((*this) == another);
}

SectionNotes::SectionNotes() {
    m_initTempo = DEFAULT_VALUE_TEMPO;
}

SectionNotes::SectionNotes(QVector<QLinkNote> &&notes) {
    m_initTempo = DEFAULT_VALUE_TEMPO;
    swap(notes);
}

double SectionNotes::initTempo() const {
    return m_initTempo;
}

void SectionNotes::setInitTempo(double initTempo) {
    m_initTempo = initTempo;
}

QString SectionNotes::trackName() const {
    return m_trackName;
}

void SectionNotes::setTrackName(const QString &trackName) {
    m_trackName = trackName;
}

void SectionNotes::setData(QVector<QLinkNote> &&notes) {
    swap(notes);
}

void SectionNotes::setData(const QVector<QLinkNote> &notes) {
    resize(notes.size());
    for (int i = 0; i < notes.size(); ++i) {
        (*this)[i] = notes.at(i);
    }
}
