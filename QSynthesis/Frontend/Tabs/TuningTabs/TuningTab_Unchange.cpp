#include "../TuningTab.h"
#include "Areas/Editor/NotesArea.h"
#include "Forms/EditorForm.h"
#include "Forms/ParamsForm.h"
#include "Forms/TracksForm.h"
#include "TuningGroup.h"
#include "mainwindow.h"

#include <QFileDialog>

void TuningTab::moveToStart() {
    m_ptrs->notesArea->moveToStart();
}

void TuningTab::moveToEnd() {
    m_ptrs->notesArea->moveToEnd();
}

void TuningTab::removeAllCaches() {
    QString dir = defaultCacheDir();
    if (isDirExist(dir)) {
        RemoveFilesWithPrefix(dir, "");
    }
}

void TuningTab::exportRecentAudio() {
    QString tempFileName = tempAudioFile();

    if (!m_playable || !isFileExist(tempFileName)) {
        QMessageBox::warning(this, MainTitle, tr("No audio files have been generated recently."));
        return;
    }

    QString path = QFileDialog::getSaveFileName(this, tr("Export wave file"),
                                                PathFindFileName(tempFileName), audioFilterString);

    if (!path.isEmpty()) {
        if (!CopyFile(tempFileName, path)) {
            QMessageBox::warning(this, MainTitle,
                                 tr("Unable to copy file, please check permissions!"));
            return;
        }
    }

    qDebug() << "Save path : " << path;
}

void TuningTab::configueLyric() {
    if (isPlaying() || !oto) {
        return;
    }
    VoiceBankTab *tab = root()->addVoiceBankTab(oto->voiceDir());
    if (!tab) {
        return;
    }
    if (!m_ptrs->draggers.selectedNotes.isEmpty()) {
        GraphicsNote *p = m_ptrs->draggers.selectedNotes.front();
        qDebug() << p->genonSettings();
        tab->locateSample(p->genonSettings());
    }
}

void TuningTab::configuePrefix() {
    if (isPlaying() || !oto) {
        return;
    }
    VoiceBankTab *tab = root()->addVoiceBankTab(oto->voiceDir());
    if (!tab) {
        return;
    }
    if (!m_ptrs->draggers.selectedNotes.isEmpty()) {
        GraphicsNote *p = m_ptrs->draggers.selectedNotes.front();
        tab->locatePrefix(p->Note.noteNum);
    } else {
        tab->locatePrefix(-1);
    }
}

void TuningTab::switchTrackStatus(Qs::Panels::Tracks status) {
    if (m_ptrs->draggers.dragging) {
        return;
    }
    m_ptrs->tracksShell->setStatus(status);
}

void TuningTab::switchEditorStatus(Qs::Panels::Editor status) {
    if (m_ptrs->draggers.dragging) {
        return;
    }
    m_ptrs->editorShell->setStatus(status);
}

void TuningTab::switchParamsStatus(Qs::Panels::Params status) {
    if (m_ptrs->draggers.dragging) {
        return;
    }
    m_ptrs->paramsShell->setStatus(status);
}
