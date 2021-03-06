#include "Base/BaseForms/FormSplitter.h"
#include "Editor/EditorForm.h"
#include "Editor/Modules/FindReplaceDialog.h"
#include "Handlers/ProjectInfoHandler.h"
#include "Managers/MemoryManager.h"
#include "Params/ParamsForm.h"
#include "SettingIniFile.h"
#include "Tracks/TracksForm.h"
#include "TuningGroup.h"
#include "TuningTab.h"
#include "application.h"
#include "mainwindow.h"

void TuningTab::initTab() {
    m_type = Qs::Tuning;

    m_ptrs = new TuningGroup(this);
    m_ptrs->currentAdsorb = qSetting->lastQuantize;

    projectInfo = new ProjectInfoHandler(this);
    notifier = nullptr;

    initValues();
    initComponents();

    initRenderer();

    // Make Working Directory
    initWorkingDir();
}

void TuningTab::initComponents() {
    mainSplitter = new FormSplitter(this);
    mainSplitter->setAutoUnfold(true);

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
    externModified = false;

    historyIndex = 0;
    savedHistoryIndex = 0;
}

void TuningTab::initWorkingDir() {
    m_workingDir =
        qApp->tempDir() + Slash + QDateTime ::currentDateTime().toString("MM-dd-hh-mm-ss-zzz");

    QDir dir;
    if (dir.exists(m_workingDir)) {
    } else if (!dir.mkpath(m_workingDir)) {
        qApp->exitOnPermissionDenied();
    }
}
