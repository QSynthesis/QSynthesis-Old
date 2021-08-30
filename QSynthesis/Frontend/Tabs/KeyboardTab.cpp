#include "KeyboardTab.h"
#include "mainwindow.h"

#include <QFontDatabase>
#include <QHeaderView>
#include <QJsonArray>

KeyboardTab::KeyboardTab(TabWidget *parent) : CentralTab(parent) {
    m_type = Qs::Keyboard;

    // 新建主容器
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    mainWidget = new KeyboardTabContent(this, this);
    mainLayout->addWidget(mainWidget);

    connect(mainWidget->tableWidget, &KeyTableWidget::keyModified, this,
            &KeyboardTab::handleKeyModified);

    historyIndex = 0;
    savedHistoryIndex = 0;
}

KeyboardTab::~KeyboardTab() {
    clearHistory();
}

bool KeyboardTab::load() {
    bool valid = true;
    bool success = cfg.load(&valid);

    if (success && valid) {
    } else {
        QMessageBox::about(nullptr, ErrorTitle, tr("Unable to load configuration file!"));
        return false;
    }

    keys = cfg.data();
    mainWidget->tableWidget->load(keys);
    return true;
}

bool KeyboardTab::save() {
    cfg.setData(keys);
    if (!cfg.save()) {
        QMessageBox::about(nullptr, ErrorTitle, tr("Unable to save file!"));
        return false;
    }

    savedHistoryIndex = historyIndex; // Update saved history index
    setEdited(false);
    return true;
}

bool KeyboardTab::restore() {
    return false;
}

void KeyboardTab::awake() {
    CentralTab::awake();
}

void KeyboardTab::sleep() {
    CentralTab::sleep();
}

void KeyboardTab::setFilename(const QString &value) {
    CentralTab::setFilename(value);
    cfg.setFilename(m_filename);
}

void KeyboardTab::setFixedname(const QString &value) {
    CentralTab::setFixedname(value);
    updateTabName();
}

void KeyboardTab::updateMenuRoot() {
    tabActions->setNaturalStatus();
    updateMenuCore();
}

void KeyboardTab::updateMenuCore() {
    tabActions->saveFile->setEnabled(edited);
    tabActions->restoreFile->setEnabled(edited);

    tabActions->undo->setEnabled(!earliest());
    tabActions->redo->setEnabled(!latest());
}

void KeyboardTab::handleKeyModified(int row, QString key) {
    KeyOperation *k = new KeyOperation();

    k->setId(row);
    k->setOrigin(keys.keyForId(row).toString());
    k->setModified(key);

    keys.setKeyForId(row, QKeySequence(key));

    if (k->differ()) {
        addHistory(k);
    }
}

void KeyboardTab::handleOperation(KeyOperation *k, bool undo) {
    mainWidget->tableWidget->setKey(k->id(), undo ? k->origin() : k->modified());
}
