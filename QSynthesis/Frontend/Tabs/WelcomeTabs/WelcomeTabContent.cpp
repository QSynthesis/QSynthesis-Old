#include "WelcomeTabContent.h"
#include "mainwindow.h"

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

    // -- Top Layout
    lbTitle = new QLabel("QSynthesis");
    lbTitle->setProperty("type", "title");

    btnNew = new QPushButton(tr("New"));
    btnNew->setProperty("type", "special");
    btnOpen = new QPushButton(tr("Open"));
    btnOpen->setProperty("type", "special");

    lbTitle->adjustSize();
    btnNew->adjustSize();
    btnOpen->adjustSize();

    topLayout->addWidget(lbTitle);
    topLayout->addStretch();
    topLayout->addWidget(btnNew);
    topLayout->addWidget(btnOpen);

    // -- Medium Layout
    sBtnFiles = new SwitchButton(tr("Projects"));
    sBtnFolders = new SwitchButton(tr("Folders"));
    sBtnTemplates = new SwitchButton(tr("Templates"));

    sBtnFiles->setProperty("type", "list");
    sBtnFolders->setProperty("type", "list");
    sBtnTemplates->setProperty("type", "list");

    // sBtnFiles->setRecommendedSize(1, 1.75);
    // sBtnFolders->setRecommendedSize(1, 1.75);
    // sBtnTemplates->setRecommendedSize(1, 1.75);

    sBtnGroup = new SwitchButtonGroup(this);
    sBtnGroup->addButton(sBtnFiles);
    sBtnGroup->addButton(sBtnFolders);
    sBtnGroup->addButton(sBtnTemplates);
    sBtnFiles->setChecked(true);

    switchLayout->addWidget(sBtnFiles);
    switchLayout->addWidget(sBtnFolders);
    switchLayout->addWidget(sBtnTemplates);
    switchLayout->addStretch();

    filesList = new FileListWidget();
    filesList->setFrameShape(QListWidget::NoFrame);

    // Empty Label
    lbEmpty = new QLabel(tr("No data."), this);
    lbEmpty->setProperty("type", "tip");
    lbEmpty->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    lbEmpty->adjustSize();

    // Main Layout
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(switchLayout);
    mainLayout->addSpacing(10);

    mainLayout->addWidget(lbEmpty);
    mainLayout->addWidget(filesList);

    this->setLayout(mainLayout);

    connect(btnNew, &QPushButton::clicked, this, &WelcomeTabContent::onNewBtnClicked);
    connect(btnOpen, &QPushButton::clicked, this, &WelcomeTabContent::onOpenBtnClicked);

    connect(sBtnFiles, &SwitchButton::clicked, this, &WelcomeTabContent::onFilesBtnClicked);
    connect(sBtnFolders, &SwitchButton::clicked, this, &WelcomeTabContent::onFoldersBtnClicked);
    connect(sBtnTemplates, &SwitchButton::clicked, this, &WelcomeTabContent::onTemplatesBtnClicked);

    connect(filesList, &FileListWidget::propertyChanged, this, &WelcomeTabContent::refresh);
}

void WelcomeTabContent::refresh() {
    QStringList ustFiles = qSetting->projects.valid();
    QStringList voiceBanks = qSetting->folders.valid();

    filesList->clear();

    if (sBtnGroup->currentButton() == sBtnFiles) {
        // ust
        filesList->setType(FileListWidget::Files);
        for (auto it = ustFiles.begin(); it != ustFiles.end(); ++it) {
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
        for (auto it = voiceBanks.begin(); it != voiceBanks.end(); ++it) {
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

void WelcomeTabContent::onFilesBtnClicked() {
    refresh();
}

void WelcomeTabContent::onFoldersBtnClicked() {
    refresh();
}

void WelcomeTabContent::onTemplatesBtnClicked() {
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
