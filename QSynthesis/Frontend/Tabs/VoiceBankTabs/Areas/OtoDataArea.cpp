#include "OtoDataArea.h"
#include "../VoiceBankGroup.h"
#include "VoiceBank/QOtoLevel.h"

OtoDataArea::OtoDataArea(VoiceBankTab *tab, QWidget *parent) : VoiceBankArea(tab, parent) {
    init();
}

OtoDataArea::~OtoDataArea() {
}

void OtoDataArea::initExtern() {
}

void OtoDataArea::init() {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(10);

    otoTabs = new TabWidget(this);
    otoTabs->setProperty("type", "voice");

    mainLayout->addWidget(otoTabs);
    setLayout(mainLayout);
}

bool OtoDataArea::addTable(const QString &dirname, const QOtoSampleList &samples) {
    auto it = TableMap.find(dirname);
    if (it != TableMap.end()) {
        return false;
    }

    OtoTableTab *tab = new OtoTableTab(otoTabs);

    QString baseDir = m_ptrs->tab->filename();
    QString tabName = "/";
    if (dirname != baseDir) {
        tabName = PathFindFileName(dirname, baseDir);
        otoTabs->addTab(tab, tabName);
    } else {
        otoTabs->insertTab(0, tab, tabName);
    }
    TableMap.insert(dirname, tab);

    tab->setDirname(dirname);
    tab->setOtoSamples(samples);
    tab->refresh();

    connect(tab, &OtoTableTab::sampleChanged, this, &OtoDataArea::handleSampleChanged);
    connect(tab, &OtoTableTab::sampleMoved, this, &OtoDataArea::handleSampleMoved);
    connect(tab, &OtoTableTab::sampleAdded, this, &OtoDataArea::handleSampleAdded);
    connect(tab, &OtoTableTab::sampleRemoved, this, &OtoDataArea::handleSampleRemoved);
    connect(tab, &OtoTableTab::currentChanged, this, &OtoDataArea::handleCurrentChanged);
    return true;
}

bool OtoDataArea::removeTable(const QString &dirname) {
    auto it = TableMap.find(dirname);
    if (it == TableMap.end()) {
        return false;
    }
    OtoTableTab *tab = it.value();
    TableMap.erase(it);

    otoTabs->removeTab(tab);
    tab->deleteLater();

    return true;
}

bool OtoDataArea::refreshTable(const QString &dirname) {
    auto it = TableMap.find(dirname);
    if (it == TableMap.end()) {
        return false;
    }
    OtoTableTab *tab = it.value();
    tab->refresh();
    return true;
}

bool OtoDataArea::contains(const QString &dirname) const {
    return TableMap.contains(dirname);
}

void OtoDataArea::removeAll() {
    otoTabs->clear();
    for (auto it = TableMap.begin(); it != TableMap.end(); ++it) {
        it.value()->deleteLater();
    }
    TableMap.clear();
}

OtoTableTab *OtoDataArea::currentTab() {
    return qobject_cast<OtoTableTab *>(otoTabs->currentWidget());
}

bool OtoDataArea::locateSample(const QGenonSettings &genon) {
    QString dirname = PathFindUpper(genon.mFileName);
    auto it = TableMap.find(dirname);
    if (it == TableMap.end()) {
        qDebug() << "Cannot find sub folder" << dirname;
        return false;
    }
    OtoTableTab *tab = it.value();
    otoTabs->setCurrentWidget(tab);
    return tab->selectSample(genon);
}
