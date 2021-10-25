#include "OtoDataArea.h"
#include "../VoiceBankGroup.h"

OtoDataArea::OtoDataArea(VoiceBankTab *tab,QWidget *parent) : VoiceBankArea(tab, parent) {
    init();
}

OtoDataArea::~OtoDataArea() {
}

void OtoDataArea::initExtern() {
}

void OtoDataArea::init() {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);

    otoTabs = new TabWidget(this);
    otoTabs->setProperty("type", "voice");

    mainLayout->addWidget(otoTabs);
    setLayout(mainLayout);

    connect(otoTabs, &TabWidget::currentChanged, this, &OtoDataArea::handleTabIndexChanged);
}

bool OtoDataArea::addTable(const QString &dirname, const QOtoSampleList &samples) {
    auto it = TableMap.find(dirname);
    if (it != TableMap.end()) {
        return false;
    }

    OtoTableTab *tab = new OtoTableTab(otoTabs);
    it = TableMap.insert(dirname, tab);

    QString baseDir = m_ptrs->tab->filename();
    QString tabName = "/";
    if (dirname != baseDir) {
        tabName = PathFindFileName(dirname, baseDir);

        auto it2 = it + 1;
        if (it2 != TableMap.end()) {
            BaseTab *nextTab = it2.value();
            int index = otoTabs->indexOf(nextTab);
            otoTabs->insertTab(index, tab, tabName);
        } else {
            otoTabs->addTab(tab, tabName);
        }
    } else {
        otoTabs->insertTab(0, tab, tabName);
    }

    tab->setDirname(dirname);
    tab->setOtoSamples(samples);

    connect(tab, &OtoTableTab::sampleChanged, this, &OtoDataArea::handleSampleChanged);
    connect(tab, &OtoTableTab::sampleMoved, this, &OtoDataArea::handleSampleMoved);
    connect(tab, &OtoTableTab::sampleAdded, this, &OtoDataArea::handleSampleAdded);
    connect(tab, &OtoTableTab::sampleRemoved, this, &OtoDataArea::handleSampleRemoved);
    connect(tab, &OtoTableTab::currentChanged, this, &OtoDataArea::handleCurrentChanged);
    connect(tab, &OtoTableTab::selectionChanged, this, &OtoDataArea::handleSelectionChanged);
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

void OtoDataArea::loadTables(const QList<QOtoIni> &data) {
    removeAllTables();

    for (auto it = data.begin(); it != data.end(); ++it) {
        QOtoIni oto = *it;
        const QString &dirname = oto.dirname();
        QOtoSampleList samples = oto.OtoSamples;

        complementSamples(dirname, samples);

        // Add to frontend
        addTable(dirname, samples);
    }
}

QList<QOtoIni> OtoDataArea::exportTables() const {
    QList<QOtoIni> list;
    for (auto it = TableMap.begin(); it != TableMap.end(); ++it) {
        auto table = it.value();
        QOtoIni oto(it.key());
        oto.OtoSamples = table->otoSamples();
        list.append(oto);
    }
    return list;
}

bool OtoDataArea::notifyTable(const QStringList &files) {
    bool res = false;
    for (auto it = files.begin(); it != files.end(); ++it) {
        const QString &filename = *it;
        QFileInfo info(filename);
        bool fileChanged = false;
        if (info.exists()) {
            if (info.isFile()) {
                fileChanged = true;
            } else {
                auto it = TableMap.find(filename);
                if (it == TableMap.end()) {
                    // A folder has been created
                    QStringList dirs = FindRecursiveDirs(filename);
                    dirs.prepend(filename);
                    for (auto it2 = dirs.begin(); it2 != dirs.end(); ++it2) {
                        const QString &dirname = *it2;
                        QOtoSampleList samples;
                        complementSamples(dirname, samples);
                        addTable(dirname, samples);
                    }
                    res = true;
                }
            }
        } else {
            auto it = TableMap.find(filename);
            if (it != TableMap.end()) {
                // A folder has been removed
                const QString &dirname = it.key();
                QStringList dirToRemove;
                for (; it != TableMap.end(); ++it) {
                    const QString &subDirname = it.key();
                    if (subDirname.startsWith(dirname)) {
                        dirToRemove.append(subDirname);
                    }
                }
                for (auto it2 = dirToRemove.begin(); it2 != dirToRemove.end(); ++it2) {
                    removeTable(*it2);
                }
            } else {
                fileChanged = true;
            }
        }
        if (fileChanged) {
            QString path = info.absolutePath(); // Must exist
            auto it = TableMap.find(path);
            if (it != TableMap.end()) {
                res |= it.value()->refreshFile(filename); // A file has been changed
            }
        }
    }
    return res;
}

bool OtoDataArea::contains(const QString &dirname) const {
    return TableMap.contains(dirname);
}

void OtoDataArea::removeAllTables() {
    otoTabs->clear();
    for (auto it = TableMap.begin(); it != TableMap.end(); ++it) {
        it.value()->deleteLater();
    }
    TableMap.clear();
}

void OtoDataArea::complementSamples(const QString &dirname, QOtoSampleList &samples) {
    // Detect samples not in oto.ini
    QDir dir(dirname);
    QFileInfoList waveInfos =
        dir.entryInfoList({"*.wav"}, QDir::NoDotAndDotDot | QDir::Files, QDir::Time);
    for (QFileInfo &info : waveInfos) {
        QString path = info.absoluteFilePath();
        int targetPosition = 0;
        int index = samples.findAuto(path, &targetPosition);
        if (index < 0) {
            QGenonSettings genon;
            genon.mFileName = path;
            QOtoSample sample(path);
            sample.append(genon);
            samples.insert(targetPosition, sample);
        }
    }
}

OtoTableTab *OtoDataArea::currentTab() {
    return qobject_cast<OtoTableTab *>(otoTabs->currentWidget());
}

bool OtoDataArea::locateSample(const QGenonSettings &genon) {
    QString dirname = PathFindUpper(genon.mFileName);
    auto it = TableMap.find(dirname);
    if (it == TableMap.end()) {
        if (otoTabs->currentWidget()) {
            otoTabs->currentWidget()->setFocus();
        }
        return false;
    }
    OtoTableTab *tab = it.value();
    otoTabs->setCurrentWidget(tab);
    return tab->selectSample(genon);
}

void OtoDataArea::receiveFromVision(const QGenonSettings &sample) {
    auto it = TableMap.find(PathFindUpper(sample.mFileName));
    if (it == TableMap.end()) {
        return;
    }

    OtoTableTab *tab = it.value();
    if (otoTabs->currentWidget() != tab) {
        otoTabs->setCurrentWidget(tab);
    }
    tab->setCurrentSample(sample);
}
