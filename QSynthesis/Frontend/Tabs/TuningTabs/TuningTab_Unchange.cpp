#include "../TuningTab.h"
#include "Areas/Editor/NotesArea.h"
#include "Document/SettingIniFile.h"
#include "Forms/EditorForm.h"
#include "Forms/ParamsForm.h"
#include "Forms/TracksForm.h"
#include "Scrolls/LiftersScrollArea.h"
#include "Scrolls/NotesScrollArea.h"
#include "Tabs/VoiceBankTab.h"
#include "TuningGroup.h"
#include "mainwindow.h"

#include <QFileDialog>
#include <QScrollBar>

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
    if (!oto) {
        return;
    }
    if (!isFreeButPlaying()) {
        return;
    }
    QString dir = oto->voiceDir();
    if (!isDirExist(dir)) {
        return;
    }
    forcePausePlaying();

    VoiceBankTab *tab = qRoot->addVoiceBankTab(dir);
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
    if (!oto) {
        return;
    }
    if (!isFreeButPlaying()) {
        return;
    }
    QString dir = oto->voiceDir();
    if (!isDirExist(dir)) {
        return;
    }
    forcePausePlaying();

    VoiceBankTab *tab = qRoot->addVoiceBankTab(dir);
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
    if (!isFreeButPlaying()) {
        return;
    }
    m_ptrs->tracksShell->setStatus(status);
}

void TuningTab::switchEditorStatus(Qs::Panels::Editor status) {
    if (!isFreeButPlaying()) {
        return;
    }
    m_ptrs->editorShell->setStatus(status);
}

void TuningTab::switchParamsStatus(Qs::Panels::Params status) {
    if (!isFreeButPlaying()) {
        return;
    }
    m_ptrs->paramsShell->setStatus(status);
}

void TuningTab::handleFormStatusChanged() {
    qSetting->tracksFormVisibility = tracksForm->unfolded();
    qSetting->editorFormVisibility = editorForm->unfolded();
    qSetting->paramsFormVisibility = paramsForm->unfolded();

    m_ptrs->liftersScroll->horizontalScrollBar()->setValue(
        m_ptrs->notesScroll->horizontalScrollBar()->value());
}

bool TuningTab::isFree() const {
    return isFreeButPlaying() && !isPlaying();
}

bool TuningTab::isFreeButPlaying() const {
    return !m_ptrs->notesArea->isLyricEditing() && !m_ptrs->notesArea->isSelecting() &&
           !qDragOut.dragging;
}

void TuningTab::setLengthUnit(int n) {
    m_ptrs->currentAdsorb = n;
    m_ptrs->notesArea->updateBackground();
    qSetting->lastQuantize = n;
}

void TuningTab::switchNoteVisibility() {
    m_ptrs->notesArea->setNotesVisible(!m_ptrs->notesArea->notesVisible());
}

void TuningTab::switchPitchVisibility() {
    m_ptrs->notesArea->setPitchesVisible(!m_ptrs->notesArea->pitchesVisible());
}

void TuningTab::switchEnvelopeVisibility() {
    m_ptrs->notesArea->setEnvelopesVisible(!m_ptrs->notesArea->envelopesVisible());
}

void TuningTab::switchParamsVisibility() {
    m_ptrs->notesArea->setParamsVisible(!m_ptrs->notesArea->paramsVisible());
}

void TuningTab::showPlayHeadOnly() {
    m_ptrs->notesArea->setPlayHeadOnCenter(false);
}

void TuningTab::showPlayHeadCenter() {
    m_ptrs->notesArea->setPlayHeadOnCenter(true);
}

void TuningTab::showSpriteAdjust() {
    m_ptrs->notesScroll->setAdjusterVisible(!m_ptrs->notesScroll->adjusterVisible());
}
