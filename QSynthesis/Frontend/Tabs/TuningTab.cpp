#include "TuningTab.h"
#include "TuningTabs/Areas/Editor/NotesArea.h"
#include "TuningTabs/Forms/EditorForm.h"
#include "TuningTabs/Forms/ParamsForm.h"
#include "TuningTabs/Forms/TracksForm.h"
#include "TuningTabs/Modules/Form/FormSplitter.h"
#include "TuningTabs/ProjectInfoHandler.h"
#include "TuningTabs/TuningGroup.h"

#include <QMimeData>

TuningGroup *TuningTab::ptrs() const {
    return m_ptrs;
}

TuningTab::TuningTab(CentralTabWidget *parent) : CentralTab(parent) {
    initTab();
}

TuningTab::~TuningTab() {
    exitCore();
    clearHistory();
    DestroyDir(m_workingDir);
}

void TuningTab::setFilename(const QString &value) {
    CentralTab::setFilename(value);
    updateTabName();

    if (notifier) {
        qSystem->removeNotifier(notifier);
    }
    notifier = qSystem->createNotifier(m_filename, MiniSystem::File);
    if (notifier) {
        connect(notifier, &MiniSystemNotifier::fileChanged, this, &TuningTab::handleFileChanged);
    }
}

void TuningTab::setEdited(bool value) {
    CentralTab::setEdited(value);
    if (value) {
        saveTempFile();
    }
}

void TuningTab::setTabName(const QString &value) {
    QString filename = value;
    if (deleted) {
        filename.prepend(DeletedPrefix);
    }
    CentralTab::setTabName(filename);
}

void TuningTab::updateTabName() {
    setTabName(PathFindFileName(m_filename));
}

void TuningTab::updateMenuRoot() {
    tabActions->setNaturalStatus();
    updateMenuCore();
}

void TuningTab::updateStatusRoot() {
}

void TuningTab::updateMenuCore() {
    tabActions->saveFile->setEnabled(edited || untitled || deleted);
    tabActions->restoreFile->setEnabled(edited && !untitled && !deleted);
    tabActions->undo->setEnabled(!earliest());
    tabActions->redo->setEnabled(!latest());

    tabActions->cut->setEnabled(!qDragOut.selectedNotes.isEmpty());
    tabActions->copy->setEnabled(!qDragOut.selectedNotes.isEmpty());
    tabActions->remove->setEnabled(!qDragOut.selectedNotes.isEmpty() ||
                                   !qDragOut.selectedPoints.isEmpty());
    tabActions->deselect->setEnabled(!qDragOut.selectedNotes.isEmpty() ||
                                     !qDragOut.selectedPoints.isEmpty());

    tabActions->transpose->setEnabled(!qDragOut.selectedNotes.isEmpty());
    tabActions->octaveUp->setEnabled(!qDragOut.selectedNotes.isEmpty());
    tabActions->octaveDown->setEnabled(!qDragOut.selectedNotes.isEmpty());

    tabActions->reset->setEnabled(!qDragOut.selectedNotes.isEmpty());
    tabActions->noteProperty->setEnabled(!qDragOut.selectedNotes.isEmpty());

    updatePasteMenu();
}

void TuningTab::updatePasteMenu() {
    QClipboard *board = QApplication::clipboard();

    bool hasData = board->mimeData()->hasFormat(CLIPBOARD_FORMAT_NAME_NOTE);
    tabActions->paste->setEnabled(hasData && m_ptrs->notesArea->isAvailableToPaste());
}

void TuningTab::handleSavedStateChanged() {
    setPlayable(false);
}

void TuningTab::handleFileChanged(const QStringList &files) {
    if (deleted) {
        return;
    }
    savedHistoryIndex = -1;
    if (isFileExist(m_filename)) {
        externModified = true;
        setEdited(true);
    } else {
        setDeleted(true);
    }
}
