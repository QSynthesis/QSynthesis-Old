#include "../KeyboardTab.h"
#include "TabWidget.h"

void KeyboardTab::initTab() {
    m_type = Qs::Keyboard;

    connect(&cfg, &ShortcutsFile::changed, this, &KeyboardTab::handleFileChanged);

    initValues();
    initComponents();
}

void KeyboardTab::initComponents() {
    // Switch Layout
    switchLayout = new QHBoxLayout();
    switchLayout->setSpacing(20);
    switchLayout->setMargin(0);

    sBtnCommon = new SwitchButton(tr("Common"));
    sBtnProject = new SwitchButton(tr("Project"));
    sBtnVoice = new SwitchButton(tr("Voice Bank Manage"));

    sBtnCommon->setProperty("type", "key-table-tab");
    sBtnProject->setProperty("type", "key-table-tab");
    sBtnVoice->setProperty("type", "key-table-tab");

    sBtnGroup = new SwitchButtonGroup(this);
    sBtnGroup->addButton(sBtnCommon);
    sBtnGroup->addButton(sBtnProject);
    sBtnGroup->addButton(sBtnVoice);

    sBtnUnderline = new SwitchButtonUnderline();
    sBtnUnderline->setProperty("type", "keyboard");
    sBtnUnderline->setGroup(sBtnGroup);

    btnReset = new QPushButton(tr("Reset Current"));
    btnReset->setObjectName("reset");

    switchLayout->addWidget(sBtnCommon);
    switchLayout->addWidget(sBtnProject);
    switchLayout->addWidget(sBtnVoice);
    switchLayout->addStretch();
    switchLayout->addWidget(btnReset);

    switchLineLayout = new QVBoxLayout();
    switchLineLayout->setMargin(0);
    switchLineLayout->setSpacing(0);
    switchLineLayout->addLayout(switchLayout);
    switchLineLayout->addWidget(sBtnUnderline);

    // Main Widget
    mainWidget = new TabWidget(this);
    mainWidget->setProperty("type", "keyboard");

    commonKeyTab = new KeyTableTab(mainWidget);
    projectKeyTab = new KeyTableTab(mainWidget);
    voiceKeyTab = new KeyTableTab(mainWidget);

    mainWidget->tabBar()->setVisible(false);
    mainWidget->addTab(commonKeyTab, "");
    mainWidget->addTab(projectKeyTab, "");
    mainWidget->addTab(voiceKeyTab, "");

    // Main Layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(40);

    mainLayout->addLayout(switchLineLayout);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(mainWidget);

    setLayout(mainLayout);

    connect(sBtnGroup, &SwitchButtonGroup::switched, this, &KeyboardTab::handleSwitched);

    // Init
    sBtnCommon->setChecked(true);
    sBtnUnderline->setRealtimeState();
}

void KeyboardTab::initValues() {
    tabActions = nullptr;

    historyIndex = 0;
    savedHistoryIndex = 0;
}

void KeyboardTab::handleSwitched() {
    int index = sBtnGroup->currentIndex();
    mainWidget->setCurrentIndex(index);
}
