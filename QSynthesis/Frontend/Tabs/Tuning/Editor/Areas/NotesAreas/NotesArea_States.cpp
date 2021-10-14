#include "../../../Controllers/EnvelopeHandler.h"
#include "../../../Controllers/Mode2Handler.h"
#include "../../../Graphics/GraphicsNote.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"
#include "application.h"

bool NotesArea::isMoving() const {
    return m_moving;
}

bool NotesArea::notesVisible() const {
    return m_notesVisible;
}

bool NotesArea::pitchesVisible() const {
    return m_pitchesVisible;
}

bool NotesArea::envelopesVisible() const {
    return m_envelopesVisible;
}

bool NotesArea::paramsVisible() const {
    return m_paramsVisible;
}

bool NotesArea::envelopesEnabled() const {
    return m_envelopesEnabled;
}

bool NotesArea::pitchesEnabled() const {
    return m_pitchesEnabled;
}

bool NotesArea::notesEnabled() const {
    return m_notesEnabled;
}

void NotesArea::setNotesEnabled(bool enabled) {
    m_notesEnabled = enabled;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->setMovable(enabled);
    }
    callForChange();
}

void NotesArea::setPitchesEnabled(bool enabled) {
    m_pitchesEnabled = enabled;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->curves()->setSolid(enabled);
    }
    callForChange();
}

void NotesArea::setEnvelopesEnabled(bool enabled) {
    m_envelopesEnabled = enabled;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->envelope()->setSolid(enabled);
    }
    callForChange();
}

void NotesArea::setNotesVisible(bool visible) {
    m_notesVisible = visible;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->setBlock(visible);
    }
    qSetting->noteVisibility = visible;
}

void NotesArea::setPitchesVisible(bool visible) {
    m_pitchesVisible = visible;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->curves()->setVisible(visible);
    }
    qSetting->pitchVisibility = visible;
}

void NotesArea::setEnvelopesVisible(bool visible) {
    m_envelopesVisible = visible;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->envelope()->setVisible(visible);
    }
    qSetting->envelopeVisibility = visible;
}

void NotesArea::setParamsVisible(bool visible) {
    m_paramsVisible = visible;
    for (int i = 0; i < NotesList.size(); ++i) {
        NotesList.at(i)->setDisplay(visible);
    }
    qSetting->paramsVisibility = visible;
}

bool NotesArea::playHeadOnCenter() const {
    return m_playHeadOnCenter;
}

void NotesArea::setPlayHeadOnCenter(bool playHeadOnCenter) {
    m_playHeadOnCenter = playHeadOnCenter;
    qSetting->playHeadCenter = playHeadOnCenter;
}

bool NotesArea::spriteVisible() const {
    return m_spriteVisible;
}

void NotesArea::setSpriteVisible(bool visible) {
    m_spriteVisible = visible;
    updateSprite();
    qSetting->spriteVisibility = visible;
}
double NotesArea::spriteAlpha() const {
    return sprite->opacity();
}

void NotesArea::setSpriteAlpha(double alpha) {
    sprite->setOpacity(alpha);
    qSetting->spriteOpacity = alpha;
}

Qt::Corner NotesArea::spritePosition() const {
    return m_spritePosition;
}

void NotesArea::setSpritePosition(Qt::Corner position) {
    m_spritePosition = position;
    updateSprite();
    qSetting->spritePosition = position;
}
