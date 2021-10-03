#include "../../../Forms/EditorForm.h"
#include "../../../Operations/LengthOperation.h"
#include "../../../Operations/LyricsOperation.h"
#include "../../../Operations/SequenceOperation.h"
#include "../../../Operations/TempoOperation.h"
#include "../../../Scrolls/NotesScrollArea.h"
#include "../../../TuningGroup.h"
#include "../NotesArea.h"

void NotesArea::replaceSingleLyric(const QString &lyric, GraphicsNote *p) {
    replaceLyrics({NotesList.indexOf(p)}, {lyric});
}

void NotesArea::replaceLyrics(const QList<int> &indexs, const QStringList &lyrics) {
    QStringList orgs, news;

    for (int i = 0; i < indexs.size(); ++i) {
        GraphicsNote *p = NotesList.at(indexs.at(i));
        QString lrc = lyrics.at(i);

        orgs.append(p->Note.lyric);
        news.append(lrc);

        p->Note.lyric = lrc;
    }

    // New Operation
    LyricsOperation *l = new LyricsOperation();

    // Set History Values
    l->setIndex(indexs);
    l->setOrigin(orgs);
    l->setModified(news);

    // Save Operation
    saveOperation(l);

    // Adjust vision

    for (int i = 0; i < indexs.size(); ++i) {
        GraphicsNote *p = NotesList.at(indexs.at(i));
        p->updateNoteStatus();
        p->adjustComponents();
        updateNoteFindStatus(p);
    }

    adjustNoteComponents(QPoint(indexs.front() - 1, indexs.back() + 1));
}

void NotesArea::replaceSelectedLyrics(const QStringList &lyrics, bool ignoreRest) {
    if (lyrics.isEmpty() || qDragOut.selectedNotes.isEmpty()) {
        return;
    }

    qDragOut.filter(GraphicsDragger::Note);

    int index = NotesList.indexOf(static_cast<GraphicsNote *>(qDragOut.leftmost()));
    auto it = lyrics.begin();

    QList<int> indexs;
    QStringList lyrics2;

    QPoint range = continuousSelection();
    bool isContinuous = isSelectionContinuous();

    for (int i = index; i < NotesList.size(); ++i) {
        if (it == lyrics.end()) {
            break;
        }

        QString lrc = *it;
        GraphicsNote *p = NotesList.at(i);

        if (ignoreRest && p->isRest()) {
            continue;
        }

        if (!isContinuous) {
            if (i > range.y()) {
                break;
            }
            if (!p->isSelected()) {
                continue;
            }
        } else {
            if (!p->isSelected()) {
                qDragOut.addOne(p);
            }
        }

        lyrics2.append(lrc);
        indexs.append(i);

        ++it;
    }

    replaceLyrics(indexs, lyrics2);
}

void NotesArea::insertRest() {
    int noteNum = 60;
    int length = 480 / m_ptrs->currentAdsorb;
    QString lyric = "R";

    QLinkNote note(noteNum, length, lyric);

    pasteNotes({note});
}

void NotesArea::removeRestLessThan(int len) {
    QList<int> indexs, preIndexs;
    QList<int> orgLens, newLens;
    QList<QLinkNote> notes;

    qDragOut.filter(GraphicsDragger::Note);
    if (qDragOut.selectedNotes.isEmpty()) {
        for (int i = 1; i < NotesList.size(); ++i) {
            GraphicsNote *c = NotesList.at(i);
            if (c->isRest() && c->Note.length < len) {
                indexs.append(i);
                notes.append(c->Note);

                preIndexs.append(i - 1);
                orgLens.append(c->prev()->Note.length);
                newLens.append(c->prev()->Note.length + c->Note.length);
            }
        }
    } else {
        for (int i = 0; i < qDragOut.selectedNotes.size(); ++i) {
            GraphicsNote *c = qDragOut.selectedNotes.at(i);
            if (c->isRest() && c->Note.length < len) {
                int index = NotesList.indexOf(c);
                if (index == 0) {
                    continue;
                }
                indexs.append(index);
                notes.append(c->Note);

                preIndexs.append(index - 1);
                orgLens.append(c->prev()->Note.length);
                newLens.append(c->prev()->Note.length + c->Note.length);
            }
        }
    }
    if (indexs.isEmpty()) {
        return;
    }

    // Deselect all
    qDragOut.removeAll();

    // New Operation
    SequenceOperation *s = new SequenceOperation(false);

    // Set History Values
    s->setIndex(indexs);
    s->setNotes(notes);

    LengthOperation *l = new LengthOperation();
    l->setIndex(preIndexs);
    l->setOrigin(orgLens);
    l->setModified(newLens);

    l->setTail(s); // Length change should be put first

    // Save Operation
    saveOperation(l);

    // Update Core
    for (int i = 0; i < preIndexs.size(); ++i) {
        NotesList[preIndexs.at(i)]->Note.length = newLens[i];
    }
    removeNotes(indexs);

    // Adjust vision
    adjustNotes(QPoint(preIndexs.front(), -1));
}

void NotesArea::modifySelectedTempo(double tempo) {
    if (!qDragOut.selectedNotes.isEmpty()) {
        GraphicsNote *p = qDragOut.selectedNotes.front();

        TempoOperation *t = new TempoOperation();
        int index = NotesList.indexOf(p);

        double newTempo = (tempo >= 0) ? tempo : tempoAt(index - 1);
        bool newStatus = (tempo >= 0) ? true : false;

        t->setIndex(index);
        t->setOrgStatus(p->tempoEdited());
        t->setOrigin(p->tempo());
        t->setNewStatus(newStatus);
        t->setModified(newTempo);
        saveOperation(t);

        p->Note.tempo = newStatus ? newTempo : NODEF_DOUBLE;
        p->setTempo(newTempo);

        updateNoteTempoAfter(index);
        updateNoteTimeAfter(index);

        adjustNoteComponents(QPoint(index - 1, -1));
    } else {
        TempoOperation *t = new TempoOperation();
        t->setIndex(-1);
        t->setOrgStatus(true);
        t->setOrigin(m_globalTempo);
        t->setNewStatus(true);
        t->setModified(tempo);
        saveOperation(t);

        setGlobalTempo(tempo);

        updateNoteTempoAfter(-1);
        updateNoteTimeAfter(0);

        adjustNoteComponents();
    }
}

void NotesArea::modifySelectedEnvelope(Qs::EnvelopeBatch method) {
    if (qDragOut.selectedNotes.isEmpty()) {
        return;
    }

    ItemList<ScopeHandler> scopes;
    for (auto it = qDragOut.selectedNotes.begin(); it != qDragOut.selectedNotes.end(); ++it) {
        GraphicsNote *p = *it;
        bool changed = false;

        QList<QControlPoint> list = p->Note.envelope;
        if (list.isEmpty()) {
            list = EnvelopeHandler::defaultEnvelope;
        }

        QCorrectGenon curGenon = p->correctGenon();
        QCorrectGenon nextGenon = p->next() ? p->next()->correctGenon() : QCorrectGenon();

        if (method == Qs::P2P3Fade) {
            if (p->prev() && !p->prev()->isRest() && curGenon.VoiceOverlap > 0) {
                changed = true;

                list[0].mX = 0;
                list[1].mX = curGenon.VoiceOverlap;
            }
            if (p->next() && !p->next()->isRest() && nextGenon.VoiceOverlap > 0) {
                changed = true;

                list[list.size() - 1].mX = 0;
                list[list.size() - 2].mX = nextGenon.VoiceOverlap;
            }

            // 如果是五点，把第二个点删了
            if (changed && list.size() == 5) {
                list.removeAt(2);
            }
        } else if (method == Qs::P1P4Fade) {
            if (p->prev() && !p->prev()->isRest() && curGenon.VoiceOverlap > 0) {
                changed = true;

                list[0].mX = curGenon.VoiceOverlap;
                list[0].mY = list[1].mY;

                list[1].mX = 5;
            }
            if (p->next() && !p->next()->isRest() && nextGenon.VoiceOverlap > 0) {
                changed = true;

                list[list.size() - 1].mX = nextGenon.VoiceOverlap;
                list[list.size() - 1].mY = list[list.size() - 2].mY;

                list[list.size() - 2].mX = 5;
            }

            // 如果是五点，把第二个点删了
            if (changed && list.size() == 5) {
                list.removeAt(2);
            }
        } else {
            list = EnvelopeHandler::defaultEnvelope;
        }

        EnvelopeHandler *envelope = p->envelope();
        envelope->replacePoints(list);
        scopes.insertAuto(envelope);

        envelope->note()->adjustComponents();
    }

    savePointsCore(scopes, false);
}

void NotesArea::insertLyrics(const QStringList &lyrics) {
    if (lyrics.isEmpty()) {
        return;
    }

    int noteNum = 60;
    int length = 480 / m_ptrs->currentAdsorb;

    GraphicsNote *leftmost = static_cast<GraphicsNote *>(qDragOut.leftmost());

    if (leftmost) {
        noteNum = leftmost->Note.noteNum;
    } else if (!NotesList.isEmpty()) {
        noteNum = NotesList.back()->Note.noteNum;
    }

    QList<QLinkNote> notes;

    for (auto it = lyrics.begin(); it != lyrics.end(); ++it) {
        QLinkNote note;

        note.length = length;
        note.noteNum = noteNum;
        note.lyric = *it;

        notes.append(note);
    }

    pasteNotes(notes);
}
