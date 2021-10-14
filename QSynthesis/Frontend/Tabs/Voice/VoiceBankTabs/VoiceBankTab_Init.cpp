#include "../VoiceBankTab.h"
#include "VoiceBankGroup.h"

void VoiceBankTab::initTab() {
    m_type = Qs::Folder;

    m_ptrs = new VoiceBankGroup(this);

    notifier = nullptr;

    initValues();
    initComponents();
    initPlayer();
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
