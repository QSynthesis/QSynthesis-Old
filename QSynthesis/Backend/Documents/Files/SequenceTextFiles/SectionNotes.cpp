#include "SectionNotes.h"
#include "QUtauConstants.h"
#include "QUtauStrings.h"

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
