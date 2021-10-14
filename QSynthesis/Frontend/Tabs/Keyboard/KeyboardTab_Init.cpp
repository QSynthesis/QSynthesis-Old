#include "Actions/TuningActionList.h"
#include "Actions/VoiceActionList.h"
#include "Containers/TabWidget.h"
#include "KeyboardTab.h"

void KeyboardTab::initTab() {
    m_type = Qs::Keyboard;

    notifier = nullptr;

    initValues();
    initComponents();
}

void KeyboardTab::initComponents() {
    // Switch Layout
    switchLayout = new QHBoxLayout();
    switchLayout->setSpacing(20);
    switchLayout->setMargin(0);

    sBtnCommon = new SwitchButton(tr("General"));
    sBtnProject = new SwitchButton(tr("Project"));
    sBtnVoice = new SwitchButton(tr("Voice Manage"));

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

    commonKeyTab = new KeyTableTab(this, mainWidget);
    projectKeyTab = new KeyTableTab(this, mainWidget);
    voiceKeyTab = new KeyTableTab(this, mainWidget);

    commonKeyTab->setDefaultShortcuts(BaseActionList::commonDefaultShortcuts());
    projectKeyTab->setDefaultShortcuts(TuningActionList::defaultShortcuts());
    voiceKeyTab->setDefaultShortcuts(VoiceActionList::defaultShortcuts());

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

    connect(sBtnGroup, &SwitchButtonGroup::switchRequested, this,
            &KeyboardTab::handleSwitchRequested);
    connect(sBtnGroup, &SwitchButtonGroup::switched, this, &KeyboardTab::handleSwitched);
    connect(btnReset, &QPushButton::clicked, this, &KeyboardTab::handleResetCurrent);

    connect(mainWidget, &TabWidget::currentChanged, this, &KeyboardTab::handleTabIndexChanged);

    // Init
    sBtnGroup->setCurrentIndex(0);
    sBtnUnderline->setRealtimeState();
    handleSwitched();
}

void KeyboardTab::initValues() {
    tabActions = nullptr;

    externModified = false;

    historyIndex = 0;
    savedHistoryIndex = 0;
}

KeyTableTab *KeyboardTab::keyTabAt(int index) const {
    return qobject_cast<KeyTableTab *>(mainWidget->tabAt(index));
}

KeyTableTab *KeyboardTab::currentKeyTab() const {
    return keyTabAt(mainWidget->currentIndex());
}

void KeyboardTab::handleSwitchRequested(bool &accepted) {
    Q_UNUSED(accepted)
}

void KeyboardTab::handleSwitched() {
    int index = sBtnGroup->currentIndex();
    if (index != mainWidget->currentIndex()) {
        mainWidget->setCurrentIndex(index);
    }
}

void KeyboardTab::handleResetCurrent() {
    currentKeyTab()->resetAllShortcuts();
}

void KeyboardTab::handleTabIndexChanged(int index) {
    SwitchButton *btn = sBtnGroup->buttonAt(index);
    if (!btn->isChecked()) {
        btn->setChecked(true);
    }
    updateMenuCore();
}
