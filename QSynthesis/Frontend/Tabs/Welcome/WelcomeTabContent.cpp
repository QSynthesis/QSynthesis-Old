#include "WelcomeTabContent.h"
#include "SettingIniFile.h"
#include "WelcomeTab.h"
#include "application.h"

WelcomeTabContent::WelcomeTabContent(WelcomeTab *tab, QWidget *parent)
    : CentralTabContent(parent), m_tab(tab) {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(40);
    mainLayout->setSpacing(10);

    topLayout = new QHBoxLayout();
    topLayout->setMargin(0);

    switchLayout = new QHBoxLayout();
    switchLayout->setSpacing(25);
    switchLayout->setMargin(0);

    switchLineLayout = new QVBoxLayout();
    switchLineLayout->setSpacing(0);
    switchLineLayout->setMargin(0);

    // -- Top
    lbTitle = new QLabel("QSynthesis");
    lbTitle->setProperty("type", "title");

    btnNew = new QPushButton(tr("New"));
    btnNew->setProperty("type", "special");
    btnOpen = new QPushButton(tr("Open"));
    btnOpen->setProperty("type", "special");

    lbTitle->adjustSize();
    btnNew->adjustSize();
    btnOpen->adjustSize();

    // -- Medium
    sBtnFiles = new SwitchButton(tr("Projects"));
    sBtnFolders = new SwitchButton(tr("Folders"));
    sBtnTemplates = new SwitchButton(tr("Templates"));

    sBtnFiles->setProperty("type", "list");
    sBtnFolders->setProperty("type", "list");
    sBtnTemplates->setProperty("type", "list");

    sBtnGroup = new SwitchButtonGroup(this);
    sBtnGroup->addButton(sBtnFiles);
    sBtnGroup->addButton(sBtnFolders);
    sBtnGroup->addButton(sBtnTemplates);

    sBtnUnderline = new SwitchButtonUnderline();
    sBtnUnderline->setProperty("type", "list");
    sBtnUnderline->setGroup(sBtnGroup);

    filesList = new FileListWidget();
    filesList->setFrameShape(QListWidget::NoFrame);

    // Empty Label
    lbEmpty = new QLabel(tr("No data."), this);
    lbEmpty->setProperty("type", "tip");
    lbEmpty->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    lbEmpty->adjustSize();

    // Layout
    topLayout->addWidget(lbTitle);
    topLayout->addStretch();
    topLayout->addWidget(btnNew);
    topLayout->addWidget(btnOpen);

    switchLayout->addWidget(sBtnFiles);
    switchLayout->addWidget(sBtnFolders);
    switchLayout->addWidget(sBtnTemplates);
    switchLayout->addStretch();

    switchLineLayout->addLayout(switchLayout);
    switchLineLayout->addWidget(sBtnUnderline);

    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(switchLineLayout);
    mainLayout->addSpacing(10);

    mainLayout->addWidget(lbEmpty);
    mainLayout->addWidget(filesList);

    this->setLayout(mainLayout);

    connect(btnNew, &QPushButton::clicked, this, &WelcomeTabContent::onNewBtnClicked);
    connect(btnOpen, &QPushButton::clicked, this, &WelcomeTabContent::onOpenBtnClicked);

    connect(sBtnGroup, &SwitchButtonGroup::switched, this, &WelcomeTabContent::handleSwitched);

    connect(filesList, &FileListWidget::propertyChanged, this, &WelcomeTabContent::refresh);

    // Init
    sBtnGroup->setCurrentIndex(0);
    sBtnUnderline->setRealtimeState();
    handleSwitched();
}

void WelcomeTabContent::refresh() {
    QStringList projects = qSetting->projects.valid();
    QStringList folders = qSetting->folders.valid();

    filesList->clear();

    if (sBtnGroup->currentButton() == sBtnFiles) {
        // ust
        filesList->setType(FileListWidget::Files);
        for (auto it = projects.begin(); it != projects.end(); ++it) {
            QString fullName = *it;
            QFileInfo fileinfo = QFileInfo(fullName);
            QString filename = fileinfo.fileName();

            QString LastTime;

            if (fileinfo.exists()) {
                QDateTime begin_time = fileinfo.lastModified();
                LastTime = begin_time.toString("yyyy-MM-dd hh:mm");
            } else {
                LastTime = "";
            }

            addItem(filename, LastTime, fullName);
        }
    } else if (sBtnGroup->currentButton() == sBtnFolders) {
        // voice
        VoiceInfo info;
        filesList->setType(FileListWidget::Folders);
        for (auto it = folders.begin(); it != folders.end(); ++it) {
            QString fullName = *it;
            QFileInfo fileinfo = QFileInfo(fullName);
            QString filename = fileinfo.fileName();

            QString LastTime;

            if (fileinfo.exists()) {
                QDateTime begin_time = fileinfo.lastModified();
                LastTime = begin_time.toString("yyyy-MM-dd hh:mm");
            } else {
                LastTime = "";
            }

            QString voice = PathFindFileName(fullName);
            info.setDirname(fullName);
            if (info.load()) {
                voice = info.title();
            }
            addItem(voice, LastTime, fullName);
        }
    } else {
        filesList->setType(FileListWidget::Files);
    }
    filesList->setFixedHeight(filesList->itemHeight() * (filesList->count() + 0.1));
    refreshWidget();
    this->adjustSize();
}

void WelcomeTabContent::addItem(const QString &FileName, const QString &LastOpenTime,
                                QString FileLocation) {
    QListWidgetItem *pItem = new QListWidgetItem();

    pItem->setData(Qt::DisplayRole, FileName);
    pItem->setData(Qt::UserRole + 1, LastOpenTime); //待修改
    pItem->setData(Qt::UserRole + 2, FileLocation);

    filesList->addItem(pItem);
}

void WelcomeTabContent::onNewBtnClicked() {
    m_tab->tabActions->newFile->trigger();
}


void WelcomeTabContent::onOpenBtnClicked() {
    m_tab->tabActions->openFile->trigger();
}

void WelcomeTabContent::handleSwitched() {
    refresh();
}

void WelcomeTabContent::refreshWidget() {
    if (filesList->count() == 0) {
        filesList->hide();
        filesList->setAttribute(Qt::WA_DontShowOnScreen);
        lbEmpty->show();
        lbEmpty->setAttribute(Qt::WA_DontShowOnScreen, false);
    } else {
        filesList->show();
        filesList->setAttribute(Qt::WA_DontShowOnScreen, false);
        lbEmpty->hide();
        lbEmpty->setAttribute(Qt::WA_DontShowOnScreen);
    }
}
