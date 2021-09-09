#include "../../Areas/Editor/NotesArea.h"
#include "../../TuningGroup.h"
#include "../GraphicsNote.h"

QGenonSettings GraphicsNote::genonSettings() const {
    return m_genonSettings;
}

QCorrectGenon GraphicsNote::correctGenon() const {
    return m_correctGenon;
}

Qs::NoteStatus GraphicsNote::status() const {
    return m_status;
}

void GraphicsNote::setStatus(const Qs::NoteStatus &status) {
    m_status = status;
    update();
}

void GraphicsNote::setSelected(bool selected) {
    GraphicsDragger::setSelected(selected);

    if (selected && qDragIn.selectedNotes.size() == 1) {
        setFocus();
    }

    if (m_lifter) {
        m_lifter->setHighlighted(selected);
    }

    update();
}

bool GraphicsNote::isRest() const {
    return m_status == Qs::Rest;
}

bool GraphicsNote::isListed() const {
    return m_status == Qs::Listed;
}

bool GraphicsNote::isUnisted() const {
    return m_status == Qs::Unlisted;
}

double GraphicsNote::time() const {
    return m_time;
}

void GraphicsNote::setTime(double time) {
    m_time = time;
    setToolTip(QString::number(m_time / 1000) + "s");
}

int GraphicsNote::tick() const {
    return m_tick;
}

void GraphicsNote::setTick(int tick) {
    m_tick = tick;
    setToolTip(QString::number(m_time / 1000) + "s");
}

int GraphicsNote::lengthRef() const {
    return m_lengthRef;
}

double GraphicsNote::tempo() const {
    return m_tempo;
}

void GraphicsNote::setTempo(double tempo) {
    m_tempo = tempo;
}

bool GraphicsNote::tempoEdited() const {
    return Note.tempo != NODEF_DOUBLE;
}

double GraphicsNote::duration() const {
    double unit = 120.0 / m_tempo / 0.96;
    return Note.length * unit;
}

double GraphicsNote::endTime() const {
    return m_time + duration();
}

double GraphicsNote::intensity() const {
    return (Note.intensity == NODEF_DOUBLE) ? DEFAULT_VALUE_INTENSITY : Note.intensity;
}

double GraphicsNote::modulation() const {
    return (Note.modulation == NODEF_DOUBLE) ? DEFAULT_VALUE_MODULATION : Note.modulation;
}

double GraphicsNote::velocity() const {
    return (Note.velocity == NODEF_DOUBLE) ? DEFAULT_VALUE_VELOCITY : Note.velocity;
}

double GraphicsNote::startPoint() const {

    return (Note.stp == NODEF_DOUBLE) ? DEFAULT_VALUE_START_POINT : Note.stp;
}

double GraphicsNote::preUtterance() const {
    double otoPreUttr = m_genonSettings.mPreUtterance;
    return (Note.preUttr == NODEF_DOUBLE) ? otoPreUttr : Note.preUttr;
}

double GraphicsNote::voiceOverlap() const {
    double otoOverlap = m_genonSettings.mVoiceOverlap;
    return (Note.overlap == NODEF_DOUBLE) ? otoOverlap : Note.overlap;
}

double GraphicsNote::inPoint() const {
    return -m_correctGenon.PreUtterance;
}

double GraphicsNote::outPoint() const {
    double endPlus = 0;
    if (m_next) {
        QCorrectGenon nextGenon = m_next->m_correctGenon;
        double nextDuration = m_next->duration();

        endPlus = -nextGenon.PreUtterance + nextGenon.VoiceOverlap;
        if (endPlus > nextDuration) {
            endPlus = nextDuration;
        }
    }
    return duration() + endPlus;
}

double GraphicsNote::inOverlapPoint() const {
    return -m_correctGenon.PreUtterance + m_correctGenon.VoiceOverlap;
}

double GraphicsNote::outOverlapPoint() const {
    double endPlus = 0;
    if (m_next) {
        QCorrectGenon nextGenon = m_next->m_correctGenon;
        endPlus = -nextGenon.PreUtterance;
    }
    return duration() + endPlus;
}

QPointF GraphicsNote::headPos() const {
    return QPointF(x(), y() + height() / 2);
}

QPointF GraphicsNote::bodyPos() const {
    return QPointF(x() + width() / 2, y() + height() / 2);
}

QPointF GraphicsNote::tailPos() const {
    return QPointF(x() + width(), y() + height() / 2);
}
