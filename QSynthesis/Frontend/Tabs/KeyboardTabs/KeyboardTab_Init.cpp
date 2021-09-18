#include "../KeyboardTab.h"
#include "TabWidget.h"

void KeyboardTab::initTab() {
    m_type = Qs::Keyboard;

    connect(&cfg, &ShortcutsFile::changed, this, &KeyboardTab::handleFileChanged);

    initValues();
    initComponents();
}

void KeyboardTab::initComponents() {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(40);

    mainWidget = new TabWidget(this);
    mainWidget->setProperty("type", "keyboard");

    commonKeyTab = new KeyTableTab(mainWidget);
    projectKeyTab = new KeyTableTab(mainWidget);
    voiceKeyTab = new KeyTableTab(mainWidget);

    mainWidget->addTab(commonKeyTab, tr("Common"));
    mainWidget->addTab(projectKeyTab, tr("Project"));
    mainWidget->addTab(voiceKeyTab, tr("Voice Bank Manage"));

    setLayout(mainLayout);
    mainLayout->addWidget(mainWidget);
}

void KeyboardTab::initValues() {
    tabActions = nullptr;

    historyIndex = 0;
    savedHistoryIndex = 0;
}
