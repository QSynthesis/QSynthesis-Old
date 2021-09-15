#include "TuningTab.h"
#include "TuningTabs/Areas/Editor/NotesArea.h"
#include "TuningTabs/Forms/EditorForm.h"
#include "TuningTabs/Forms/ParamsForm.h"
#include "TuningTabs/Forms/TracksForm.h"
#include "TuningTabs/Modules/Form/FormSplitter.h"
#include "TuningTabs/ProjectInfoHandler.h"
#include "TuningTabs/TuningGroup.h"
#include "mainwindow.h"

void TuningTab::initTab() {
    m_type = Qs::Tuning;

    m_ptrs = new TuningGroup(this);
    m_ptrs->currentAdsorb = qSetting->lastQuantize;

    projectInfo = new ProjectInfoHandler(this);
    connect(&ustFile, &SequenceTextFile::changed, this, &TuningTab::handleFileChanged);

    initValues();
    initComponents();

    // Make Working Directory
    initPlayer();
    initWorkingDir();
}

void TuningTab::initComponents() {
    mainSplitter = new FormSplitter(this);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    editorForm = new EditorForm(this);
    tracksForm = new TracksForm(this); // Must be created after editor part
    paramsForm = new ParamsForm(this); // Must be created after editor part

    mainSplitter->addForm(tracksForm);
    mainSplitter->addForm(editorForm);
    mainSplitter->addForm(paramsForm);

    mainSplitter->setMainForm(editorForm);

    mainSplitter->setStretchFactor(tracksForm, 1);
    mainSplitter->setStretchFactor(editorForm, 1);
    mainSplitter->setStretchFactor(paramsForm, 1);
    mainSplitter->setSizes({1000, 3000, 1000}); // Set proportion mandatorily

    mainLayout->addWidget(mainSplitter);
    this->setLayout(mainLayout);

    m_ptrs->tracksShell = tracksForm;
    m_ptrs->editorShell = editorForm;
    m_ptrs->paramsShell = paramsForm;

    m_tempMenu = new TemporaryMenu(this);

    // First Status
    bool visibilities[3] = {qSetting->tracksFormVisibility, qSetting->editorFormVisibility,
                            qSetting->paramsFormVisibility};
    if (!visibilities[0]) {
        tracksForm->setUnfolded(false);
    }
    if (!visibilities[2]) {
        paramsForm->setUnfolded(false);
    }
    if (!visibilities[1] && (visibilities[0] || visibilities[2])) {
        editorForm->setUnfolded(false);
    }

    connect(mainSplitter, &FormSplitter::statusChanged, this, &TuningTab::handleFormStatusChanged);
}

void TuningTab::initValues() {
    tabActions = nullptr;
    oto = nullptr;

    untitled = false;
    deleted = false;

    historyIndex = 0;
    savedHistoryIndex = 0;
}

void TuningTab::initWorkingDir() {
    m_workingDir =
        tempDirectoryName + Slash + QDateTime ::currentDateTime().toString("MM-dd-hh-mm-ss-zzz");

    QDir dir;
    if (dir.exists(m_workingDir)) {
    } else if (!dir.mkpath(m_workingDir)) {
        qRoot->exitOnNoIOPermission();
    }

    savedRenderArgs.clear();
}

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

void TuningTab::setFilename(const QString &value) {
    CentralTab::setFilename(value);
    updateTabName();
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

void TuningTab::updateTabName() {
    setTabName(PathFindFileName(m_filename));
}

void TuningTab::handleFileChanged() {
    savedHistoryIndex = -1;
    if (isFileExist(m_filename)) {
        setEdited(true);
    } else {
        setDeleted(true);
    }
}
