#include "../../../Modules/Scrolls/NotesScrollArea.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::initLyricModules() {
    m_lyricEdit = new GraphicsLineEdit();
    addItem(m_lyricEdit);

    m_lyricEdit->setZValue(lyricEditZIndex);

    m_lyricEdit->installEventFilter(this);
    m_lyricEdit->hide();

    m_curEditNote = nullptr;
}

void NotesArea::setCurEditNote(GraphicsNote *p) {
    GraphicsNote *org = m_curEditNote;
    m_curEditNote = p;

    if (org) {
        org->update();
    }
    if (p) {
        p->update();
    }
}

void NotesArea::editFinish() {
    if (!m_lyricEdit->isVisible() || !m_curEditNote) {
        return;
    }
    replaceSingleLyric(m_lyricEdit->text(), m_curEditNote);

    m_lyricEdit->hide();
    m_curEditNote->setFocus();
    setCurEditNote(nullptr);
}

void NotesArea::editNextLyric() {
    if (!m_lyricEdit->isVisible() || !m_curEditNote) {
        return;
    }

    replaceSingleLyric(m_lyricEdit->text(), m_curEditNote);

    if (m_curEditNote->next()) {
        editNoteLyric(m_curEditNote->next());
    }
}

bool NotesArea::isLyricEditing() const {
    return m_lyricEdit->isVisible();
}

bool NotesArea::isPlaying() const {
    return playHead->isVisible();
}

void NotesArea::editNoteLyric(GraphicsNote *pNote) {
    qDragOut.removeAll();
    qDragOut.addOne(pNote);

    m_lyricEdit->setText(pNote->Note.lyric);
    // m_lyricEdit->resize(100, 25);
    m_lyricEdit->setPos(pNote->x(),
                        pNote->headPos().y() - m_lyricEdit->boundingRect().height() / 2);
    m_lyricEdit->show();
    m_lyricEdit->setFocus();
    m_lyricEdit->selectAll();

    setCurEditNote(pNote);

    // emit checkOnStage(pNote, true);
    // emit checkOnStage(m_lyricEdit, true);
}

void NotesArea::switchLyric() {
    if (!isLyricEditing()) {
        return;
    }
    editNextLyric();
}

void NotesArea::abandonLyric() {
    if (!m_lyricEdit->isVisible() || !m_curEditNote) {
        return;
    }
    m_lyricEdit->hide();
    setCurEditNote(nullptr);
}

GraphicsNote *NotesArea::curEditNote() const {
    return m_curEditNote;
}
