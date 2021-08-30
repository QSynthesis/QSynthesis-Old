#include "../../Areas/Editor/NotesArea.h"
#include "../../Graphics/GraphicsNote.h"
#include "../../TuningGroup.h"
#include "../NoteHandler.h"

QColor NoteHandler::lyricColor() const {
    return m_lyricColor;
}

void NoteHandler::setLyricColor(const QColor &lyricColor) {
    m_lyricColor = lyricColor;
    update();
}

QColor NoteHandler::unlistedLineColor() const {
    return m_unlistedLineColor;
}

void NoteHandler::setUnlistedLineColor(const QColor &unlistedLineColor) {
    m_unlistedLineColor = unlistedLineColor;
}

QColor NoteHandler::unlistedFillColor() const {
    return m_unlistedFillColor;
}

void NoteHandler::setUnlistedFillColor(const QColor &unlistedFillColor) {
    m_unlistedFillColor = unlistedFillColor;
}

QColor NoteHandler::listedLineColor() const {
    return m_listedLineColor;
}

void NoteHandler::setListedLineColor(const QColor &listedLineColor) {
    m_listedLineColor = listedLineColor;
}

QColor NoteHandler::listedFillColor() const {
    return m_listedFillColor;
}

void NoteHandler::setListedFillColor(const QColor &listedFillColor) {
    m_listedFillColor = listedFillColor;
}

QColor NoteHandler::restLineColor() const {
    return m_restLineColor;
}

void NoteHandler::setRestLineColor(const QColor &restLineColor) {
    m_restLineColor = restLineColor;
}

QColor NoteHandler::restFillColor() const {
    return m_restFillColor;
}

void NoteHandler::setRestFillColor(const QColor &restFillColor) {
    m_restFillColor = restFillColor;
}
