#include <QDebug>
#include <QFile>

#include "VoiceBankTab.h"
#include "VoiceBankTabs/VoiceBankGroup.h"
#include "mainwindow.h"

VoiceBankTab::VoiceBankTab(CentralTabWidget *parent) : CentralTab(parent) {
    initTab();
}

VoiceBankTab::~VoiceBankTab() {
    clearHistory();
}

void VoiceBankTab::initTab() {
    m_type = Qs::Folder;

    m_ptrs = new VoiceBankGroup(this);

    connect(&voicebank, &QVoiceBank::charTxtChanged, this, &VoiceBankTab::handleCharTxtChanged);
    connect(&voicebank, &QVoiceBank::readmeTxtChanged, this, &VoiceBankTab::handleReadmeTxtChanged);

    connect(&voicebank, &QVoiceBank::otoDirCreated, this, &VoiceBankTab::handleOtoDirChanged);
    connect(&voicebank, &QVoiceBank::otoDirDestroyed, this, &VoiceBankTab::handleOtoDirChanged);

    connect(&voicebank, &QVoiceBank::otoDirChanged, this, &VoiceBankTab::handleOtoDirChanged);
    connect(&voicebank, &QVoiceBank::otoFileChanged, this, &VoiceBankTab::handleOtoFileChanged);

    initValues();
    initComponents();

    initTimer();

    initPlayer();
}

void VoiceBankTab::setFilename(const QString &value) {
    CentralTab::setFilename(value);
    updateTabName();
}

void VoiceBankTab::updateMenuRoot() {
    tabActions->setNaturalStatus();
    updateMenuCore();
}

void VoiceBankTab::updateStatusRoot() {
}

void VoiceBankTab::updateMenuCore() {
    tabActions->saveFile->setEnabled(edited);
    tabActions->restoreFile->setEnabled(edited);

    tabActions->undo->setEnabled(!earliest());
    tabActions->redo->setEnabled(!latest());

    OtoTableTab *curTab = dataArea->currentTab();
    if (curTab) {
        bool empty = curTab->selectedRanges().isEmpty();
        bool isTop = curTab->isCurrentTop();
        bool isBottom = curTab->isCurrentBottom();
        bool isValid = curTab->isCurrentValid();
        bool isSingle = curTab->isSelectionSingle();

        tabActions->deselect->setEnabled(!empty);
        tabActions->reset->setEnabled(!empty);

        tabActions->moveUp->setEnabled(isSingle && !isTop);
        tabActions->moveTop->setEnabled(isSingle && !isTop);
        tabActions->moveDown->setEnabled(isSingle && !isBottom);
        tabActions->moveBottom->setEnabled(isSingle && !isBottom);
        tabActions->duplicate->setEnabled(isSingle);
        tabActions->remove->setEnabled(isSingle && !(isTop && isBottom && isValid));
    } else {
        tabActions->deselect->setEnabled(false);
        tabActions->reset->setEnabled(false);

        tabActions->moveUp->setEnabled(false);
        tabActions->moveTop->setEnabled(false);
        tabActions->moveDown->setEnabled(false);
        tabActions->moveBottom->setEnabled(false);
        tabActions->remove->setEnabled(false);
    }

    tabActions->generateFrq->setEnabled(false);
    tabActions->modifyAlias->setEnabled(false);
    tabActions->removeInvalid->setEnabled(false);
}

void VoiceBankTab::updateTabName() {
    QString title = voicebank.title();
    if (!title.isEmpty()) {
        setTabName(title);
    } else {
        setTabName(PathFindFileName(m_filename));
    }
}

void VoiceBankTab::initComponents() {
    // Init splitters
    mainSplitter = new QSplitter(Qt::Vertical, this);

    topSplitter = new QSplitter(Qt::Horizontal, mainSplitter);
    bottomSplitter = new QSplitter(Qt::Horizontal, mainSplitter);

    mainSplitter->setProperty("type", "voice-splitter");
    topSplitter->setProperty("type", "voice-splitter");
    bottomSplitter->setProperty("type", "voice-splitter");

    mainSplitter->setChildrenCollapsible(false);
    topSplitter->setChildrenCollapsible(false);
    bottomSplitter->setChildrenCollapsible(false);

    // Init areas
    infoArea = new OtoInfoArea(this, topSplitter);
    dataArea = new OtoDataArea(this, topSplitter);

    visionArea = new OtoVisionArea(this, bottomSplitter);
    playerArea = new OtoPlayerArea(this, bottomSplitter);

    topSplitter->addWidget(infoArea);
    topSplitter->addWidget(dataArea);

    bottomSplitter->addWidget(visionArea);
    bottomSplitter->addWidget(playerArea);

    mainSplitter->addWidget(topSplitter);
    mainSplitter->addWidget(bottomSplitter);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mainSplitter);
    mainLayout->setMargin(20);
    setLayout(mainLayout);

    mainSplitter->setSizes({2000, 1000});
    topSplitter->setSizes({1000, 2000});
    bottomSplitter->setSizes({4000, 1000});

    m_ptrs->infoArea = infoArea;
    m_ptrs->dataArea = dataArea;
    m_ptrs->visionArea = visionArea;
    m_ptrs->playerArea = playerArea;

    infoArea->initExtern();
    dataArea->initExtern();
    visionArea->initExtern();
    playerArea->initExtern();
}

void VoiceBankTab::initValues() {
    tabActions = nullptr;

    historyIndex = 0;
    savedHistoryIndex = 0;
}

void VoiceBankTab::initTimer() {
    otoTimer = new QTimer(this);
    connect(otoTimer, &QTimer::timeout, this, &VoiceBankTab::onOtoTimer);
}

VoiceBankGroup *VoiceBankTab::ptrs() const {
    return m_ptrs;
}
