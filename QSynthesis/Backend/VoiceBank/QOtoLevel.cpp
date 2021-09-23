#include "QOtoLevel.h"
#include "QGenonSettings.h"
#include "QUtauUtils.h"
#include "Strings/UtaFilenames.h"

QOtoLevel::QOtoLevel(QOtoLevel *parent) : DirectoryCollect(parent) {
    init();
    reset();
}

QOtoLevel::QOtoLevel(const QString &dir, QOtoLevel *parent) : DirectoryCollect(parent) {
    init();
    setDirname(dir);
}

QOtoLevel::~QOtoLevel() {
    resetCore();
}

void QOtoLevel::init() {
    connect(&otoIni, &QOtoIni::changed, this, &QOtoLevel::handleOtoIniChanged);

    QOtoLevel *root = this->root();
    if (this != root) {
        // Pass child's signal to root
        connect(this, &QOtoLevel::levelCreated, root, &QOtoLevel::handleLevelCreated);
        connect(this, &QOtoLevel::levelDestroyed, root, &QOtoLevel::handleLevelDestroyed);

        connect(this, &QOtoLevel::levelChanged, root, &QOtoLevel::handleLevelChanged);
        connect(this, &QOtoLevel::levelOtoIniChanged, root, &QOtoLevel::handleLevelOtoIniChanged);
    }
}

QOtoLevel *QOtoLevel::root() const {
    QOtoLevel *upper = qobject_cast<QOtoLevel *>(parent());
    if (!upper) {
        return const_cast<QOtoLevel *>(this);
    }
    return upper->root();
}

QList<QOtoLevel *> QOtoLevel::dirs() const {
    QList<QOtoLevel *> res;
    for (auto it = m_dirs.begin(); it != m_dirs.end(); ++it) {
        res.append(qobject_cast<QOtoLevel *>(*it));
    }
    return res;
}

void QOtoLevel::setOtoData(const QOtoSampleList &otoData) {
    otoIni.OtoSamples = otoData;
}

QOtoSampleList QOtoLevel::otoData() const {
    return otoIni.OtoSamples;
}

QString QOtoLevel::otoFilename() const {
    return otoIni.filename();
}

bool QOtoLevel::loadCore() {
    bool result = true;
    if (isFileExist(otoIni.filename())) {
        result &= otoIni.load();
    }
    result &= DirectoryCollect::loadCore();
    return result;
}

bool QOtoLevel::saveCore() {
    bool otoSave = otoIni.save();
    if (!otoSave) {
        return false;
    }
    return DirectoryCollect::saveCore();
}

void QOtoLevel::prepareCore() {
    otoIni.setFilename(m_dirname + Slash + FILE_NAME_OTO_INI);
}

DirectoryManager *QOtoLevel::addDirCore(const QString &dir, bool init) {
    QOtoLevel *oto = new QOtoLevel(dir, this);
    if (!oto->load()) {
        delete oto;
        return nullptr;
    }

    // Load Success
    emit levelCreated(oto, init);
    return oto;
}

void QOtoLevel::removeDirCore(DirectoryManager *dir, bool init) {
    QOtoLevel *level = qobject_cast<QOtoLevel *>(dir);
    emit levelDestroyed(level, init);
    delete level;
}

void QOtoLevel::handleOtoIniChanged() {
    emit levelOtoIniChanged(this); // Pass to root
}

void QOtoLevel::handleChangedCore() {
    DirectoryCollect::handleChangedCore(); // Base
    emit levelChanged(this);               // Pass to root
}

// Root slots
void QOtoLevel::handleLevelCreated(QOtoLevel *level, bool init) {
    emit levelCreated(level, init);
}

void QOtoLevel::handleLevelDestroyed(QOtoLevel *level, bool init) {
    emit levelDestroyed(level, init);
}

void QOtoLevel::handleLevelOtoIniChanged(QOtoLevel *level) {
    emit levelOtoIniChanged(level);
}

void QOtoLevel::handleLevelChanged(QOtoLevel *level) {
    emit levelChanged(level);
}
