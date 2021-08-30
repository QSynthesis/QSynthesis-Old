#include "../../../TuningGroup.h"
#include "../NotesArea.h"

QColor NotesArea::timeLineColor() const {
    return m_timeLineColor;
}

void NotesArea::setTimeLineColor(const QColor &timeLineColor) {
    m_timeLineColor = timeLineColor;
    updateBackground();
    emit colorChanged();
}

QColor NotesArea::sectionLineColor() const {
    return m_sectionLineColor;
}

void NotesArea::setSectionLineColor(const QColor &sectionLineColor) {
    m_sectionLineColor = sectionLineColor;
    updateBackground();
    emit colorChanged();
}

QColor NotesArea::pitchLineColor() const {
    return m_pitchLineColor;
}

void NotesArea::setPitchLineColor(const QColor &pitchLineColor) {
    m_pitchLineColor = pitchLineColor;
    updateBackground();
    emit colorChanged();
}

QColor NotesArea::levelLineColor() const {
    return m_levelLineColor;
}

void NotesArea::setLevelLineColor(const QColor &levelLineColor) {
    m_levelLineColor = levelLineColor;
    updateBackground();
    emit colorChanged();
}

QColor NotesArea::backLowColor() const {
    return m_backLowColor;
}

void NotesArea::setBackLowColor(const QColor &backLowColor) {
    m_backLowColor = backLowColor;
    updateBackground();
    emit colorChanged();
}

QColor NotesArea::backHighColor() const {
    return m_backHighColor;
}

void NotesArea::setBackHighColor(const QColor &backHighColor) {
    m_backHighColor = backHighColor;
    updateBackground();
    emit colorChanged();
}
