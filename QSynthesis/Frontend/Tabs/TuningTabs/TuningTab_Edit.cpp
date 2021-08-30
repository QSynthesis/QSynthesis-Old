#include "../TuningTab.h"
#include "Areas/Editor/NotesArea.h"
#include "Areas/Tracks/HeadsArea.h"
#include "Operations/NoteOperation.h"
#include "Operations/ProjectOperation.h"
#include "Operations/TrackOperation.h"
#include "ProjectInfoHandler.h"
#include "TuningGroup.h"
#include "mainwindow.h"

void TuningTab::undo() {
    bool success = true;
    if (!earliest()) {
        TuneOperation *t = historyList.at(historyIndex - 1);
        switch (t->type()) {
        case TuneOperation::Note: {
            NoteOperation *n = static_cast<NoteOperation *>(t);
            success = m_ptrs->notesArea->handleOperation(n);
            break;
        }
        case TuneOperation::Track: {
            TrackOperation *tr = static_cast<TrackOperation *>(t);
            success = m_ptrs->trackHeads->handleOperation(tr);
            break;
        }
        case TuneOperation::Project: {
            ProjectOperation *p = static_cast<ProjectOperation *>(t);
            success = projectInfo->handleOperation(p);
            break;
        }
        default:
            break;
        }
        if (success) {
            historyIndex--;
        }
    }
    setEdited(savedHistoryIndex != historyIndex);
}

void TuningTab::redo() {
    bool success = true;
    if (!latest()) {
        TuneOperation *t = historyList.at(historyIndex);
        switch (t->type()) {
        case TuneOperation::Note: {
            NoteOperation *n = static_cast<NoteOperation *>(t);
            success = m_ptrs->notesArea->handleOperation(n, false);
            break;
        }
        case TuneOperation::Track: {
            TrackOperation *tr = static_cast<TrackOperation *>(t);
            success = m_ptrs->trackHeads->handleOperation(tr, false);
            break;
        }
        case TuneOperation::Project: {
            ProjectOperation *p = static_cast<ProjectOperation *>(t);
            success = projectInfo->handleOperation(p, false);
            break;
        }
        default:
            break;
        }
        if (success) {
            historyIndex++;
        }
    }
    setEdited(savedHistoryIndex != historyIndex);
}

void TuningTab::selectAll() {
    m_ptrs->notesArea->selectContinuously(true);
    updateMenuCore();
}

void TuningTab::deselect() {
    m_ptrs->draggers.removeAll();
    updateMenuCore();
}

void TuningTab::reset() {
    resetNoteProperty();
}

void TuningTab::copy() {
    QList<QLinkNote> notes = m_ptrs->notesArea->selectedNotes();
    if (notes.isEmpty()) {
        return;
    }

    QJsonArray arr;
    for (int i = 0; i < notes.size(); ++i) {
        arr.append(notes[i].toJson());
    }

    // Add to clipboard
    QMimeData *data = new QMimeData();
    data->setData(CLIPBOARD_FORMAT_NAME_NOTE, QJsonDocument(arr).toJson());

    QClipboard *board = QApplication::clipboard();
    board->setMimeData(data);

    updatePasteMenu();
}

void TuningTab::cut() {
    copy();
    remove();

    updateMenuCore();
}

void TuningTab::paste() {
    QClipboard *board = QApplication::clipboard();
    QByteArray data = board->mimeData()->data(CLIPBOARD_FORMAT_NAME_NOTE);

    QJsonParseError jsonParseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &jsonParseError);

    QJsonArray jsonArr = jsonDoc.array();

    QList<QLinkNote> notes;
    for (auto it = jsonArr.begin(); it != jsonArr.end(); ++it) {
        notes.append(QLinkNote::fromJson(it->toObject()));
    }

    m_ptrs->notesArea->pasteNotes(notes);
    updateMenuCore();
}

void TuningTab::remove() {
    m_ptrs->notesArea->handleDelete();
    updateMenuCore();
}

bool TuningTab::earliest() const {
    return historyIndex == 0;
}

bool TuningTab::latest() const {
    return historyIndex == historyList.size();
}

void TuningTab::addHistory(TuneOperation *n) {
    // Saved status doesn't exist
    if (savedHistoryIndex > historyIndex) {
        savedHistoryIndex = -1;
    }
    // Remove all operations after
    while (historyList.size() > historyIndex) {
        delete historyList.back();
        historyList.pop_back();
    }
    historyList.append(n);
    historyIndex++;

    setEdited(savedHistoryIndex != historyIndex);
}

void TuningTab::clearHistory() {
    for (int i = historyList.size() - 1; i >= 0; --i) {
        delete historyList.at(i);
    }
    historyList.clear();
    historyIndex = 0;
    savedHistoryIndex = -1;
}
