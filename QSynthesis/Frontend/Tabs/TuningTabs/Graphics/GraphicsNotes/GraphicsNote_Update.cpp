#include "../../Areas/Editor/NotesArea.h"
#include "../../TuningGroup.h"
#include "../GraphicsNote.h"

#include <cmath>

void GraphicsNote::updateNoteStatus() {
    if (isRestNoteLyric(Note.lyric)) {
        m_genonSettings = QGenonSettings();
        setStatus(Qs::Rest);
    } else {
        setStatus(updateGenonSettings() ? Qs::Listed : Qs::Unlisted);
    }
    updateCorrectGenon();
}

bool GraphicsNote::updateGenonSettings() {
    m_genonSettings = QGenonSettings();
    bool aSuccess = m_editor->getGenonSettings(Note.lyric, &m_genonSettings, Note.noteNum);
    return aSuccess;
}

void GraphicsNote::updateCorrectGenon() {
    double CorrectRate = 1;

    double tmpPreUttr = preUtterance();
    double tmpOverlap = voiceOverlap();

    double tmpSTPoint = startPoint();
    double velocity = this->velocity();

    double velocityRate = pow(2, 1 - velocity / 100);

    tmpPreUttr *= velocityRate;
    tmpOverlap *= velocityRate;

    if (!m_prev) {
        m_correctGenon = QCorrectGenon(tmpPreUttr, tmpOverlap, tmpSTPoint);
        return;
    }

    double prevDuration = m_prev->duration();
    double curDuration = this->duration();
    double MaxOccupy = (m_prev->isRest()) ? prevDuration : (prevDuration / 2);

    if (tmpPreUttr - tmpOverlap > MaxOccupy) {
        CorrectRate = MaxOccupy / (tmpPreUttr - tmpOverlap);
    }

    double CorrecetPreUttr = CorrectRate * tmpPreUttr;
    double CorrecetOverlap = CorrectRate * tmpOverlap;
    double CorrecetSTPoint = tmpPreUttr - CorrecetPreUttr;

    CorrecetSTPoint += tmpSTPoint;

    // Voice Overlap shouldn't be too long
    if (CorrecetOverlap - CorrecetPreUttr > curDuration) {
        CorrecetOverlap = CorrecetPreUttr + curDuration;
    }

    m_correctGenon = QCorrectGenon(CorrecetPreUttr, CorrecetOverlap, CorrecetSTPoint);
}

void GraphicsNote::updateNeighborCorrectGenons(bool update) {
    if (m_next) {
        m_next->updateCorrectGenon();

        if (update) {
            m_next->adjustComponents();
        }
    }
}

void GraphicsNote::updateComponents(bool prev, bool curr, bool next) {
    if (prev && m_prev) {
        m_prev->update();
        m_prev->m_screen->update();
    }
    if (curr) {
        update();
        m_screen->update();
    }
    if (next && m_next) {
        m_next->update();
        m_next->m_screen->update();
    }
}
