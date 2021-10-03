#include "../../../Handlers/DraggerHandler.h"
#include "../../../Scrolls/NotesScrollArea.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::updateFindStatus() {
    if (!m_finding) {
        qDragOut.removeAllFind();
        updateFindIndexs();
    } else {
        for (int i = 0; i < NotesList.size(); ++i) {
            GraphicsNote *p = NotesList.at(i);
            updateNoteFindStatus(p);
        }
    }
}

void NotesArea::updateFindStatusAt(int index) {
    GraphicsNote *p = NotesList.at(index);
    updateNoteFindStatus(p);
}

void NotesArea::updateNoteFindStatus(GraphicsNote *p) {
    if (m_finding) {
        m_findOption.match(p->Note.lyric) ? qDragOut.addFind(p) : qDragOut.removeFind(p);
    } else {
        qDragOut.removeFind(p);
    }
    updateFindIndexs();
}

void NotesArea::updateFindIndexs() {
    if (qDragOut.findedNotes.isEmpty()) {
        m_ptrs->notesScroll->updateFinderCaption(0, 0);
    } else {
        GraphicsNote *p = static_cast<GraphicsNote *>(qDragOut.leftmost(GraphicsDragger::Note));
        int pos;
        qDragOut.findedNotes.findAuto(p, &pos);
        m_ptrs->notesScroll->updateFinderCaption(pos + 1, qDragOut.findedNotes.size());
    }
}

bool NotesArea::finding() const {
    return m_finding;
}

void NotesArea::setFinding(bool finding) {
    m_finding = finding;
    updateFindStatus();
}

FindOption NotesArea::findOption() const {
    return m_findOption;
}

void NotesArea::setFindOption(const FindOption &opt) {
    m_findOption = opt;
    updateFindStatus();
}

void NotesArea::findAtIndex(int index) {
    if (index < 0 || index >= qDragOut.findedNotes.size()) {
        qDragOut.removeAll();
    } else {
        selectNote(qDragOut.findedNotes.at(index));
        updateFindIndexs();
    }
}

void NotesArea::replaceByFind(const ReplaceOption &opt, bool all) {
    if (!all) {
        GraphicsNote *p = static_cast<GraphicsNote *>(qDragOut.leftmost(GraphicsDragger::Note));
        int pos;
        qDragOut.findedNotes.findAuto(p, &pos);
        if (pos >= 0) {
            if (opt.preserveCase) {
                QString orgLrc = p->Note.lyric;
                QString newLrc = opt.replaceText;

                if (!orgLrc.isEmpty() && !newLrc.isEmpty()) {
                    QChar fr = orgLrc.front();
                    if (fr.isUpper()) {
                        newLrc = newLrc.front().toUpper() + newLrc.mid(1);
                    } else if (fr.isLower()) {
                        newLrc = newLrc.front().toLower() + newLrc.mid(1);
                    }
                    replaceSingleLyric(newLrc, p);
                }
            } else {
                replaceSingleLyric(opt.replaceText, p);
            }
        }
    } else {
        QString newLrc = opt.replaceText;
        qDragOut.removeAll();
        QList<int> indexs;
        QStringList lyrics;
        for (int i = 0; i < NotesList.size(); ++i) {
            GraphicsNote *p = NotesList.at(i);
            if (p->highlighted()) {
                qDragOut.addOne(p);
                indexs.append(i);
                lyrics.append(newLrc);
            }
        }
        replaceLyrics(indexs, lyrics);
    }
}
