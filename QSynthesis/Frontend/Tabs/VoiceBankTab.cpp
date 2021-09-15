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
    mainSplitter->setChildrenCollapsible(false);

    topSplitter = new QSplitter(Qt::Horizontal, mainSplitter);
    bottomSplitter = new QSplitter(Qt::Horizontal, mainSplitter);
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
