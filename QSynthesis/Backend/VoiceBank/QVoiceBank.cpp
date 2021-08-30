#include "QVoiceBank.h"
#include "Strings/UtaFilenames.h"

QVoiceBank::QVoiceBank(QObject *parent) : VoiceInfo(parent) {
    init();
}

QVoiceBank::QVoiceBank(const QString &dir, QObject *parent) : VoiceInfo(parent) {
    init();
    setDirname(dir);
}

QVoiceBank::~QVoiceBank() {
    clearOto();
}

void QVoiceBank::init() {
    connect(&ReadmeTxt, &QReadmeText::changed, this, &QVoiceBank::handleReadmeTxtChanged);
    connect(&PrefixMap, &QPrefixMap::changed, this, &QVoiceBank::handlePrefixMapChanged);

    connect(&OtoRoot, &QOtoLevel::levelCreated, this, &QVoiceBank::handleLevelCreated);
    connect(&OtoRoot, &QOtoLevel::levelDestroyed, this, &QVoiceBank::handleLevelDestroyed);

    connect(&OtoRoot, &QOtoLevel::levelChanged, this, &QVoiceBank::handleLevelChanged);
    connect(&OtoRoot, &QOtoLevel::levelOtoIniChanged, this, &QVoiceBank::handleLevelOtoIniChanged);
}

void QVoiceBank::handleReadmeTxtChanged() {
    emit readmeTxtChanged();
}

void QVoiceBank::handlePrefixMapChanged() {
    emit prefixMapChanged();
}

void QVoiceBank::handleLevelCreated(QOtoLevel *level, bool init) {
    QString path = level->dirname();
    OtoLevels.insert(path, level);
    emit otoDirCreated(path);
}

void QVoiceBank::handleLevelDestroyed(QOtoLevel *level, bool init) {
    QString path = level->dirname();
    OtoLevels.remove(path);
    emit otoDirDestroyed(path);
}

void QVoiceBank::handleLevelChanged(QOtoLevel *level) {
    QString path = level->dirname();
    emit otoDirChanged(path);
}

void QVoiceBank::handleLevelOtoIniChanged(QOtoLevel *level) {
    QString path = level->otoFilename();
    emit otoFileChanged(path);
}

void QVoiceBank::loadOtoCache(QOtoLevel *level) {
    QList<QOtoLevel *> dirs = level->dirs();
    for (QOtoLevel *&oto : dirs) {
        loadOtoCache(oto);
        OtoCache.insert(oto->otoFilename(), oto->otoData());
    }
}

bool QVoiceBank::loadOto() {
    OtoLevels.clear();
    OtoLevels.insert(m_dirname, &OtoRoot);

    this->blockSignals(true);
    bool otoLoad = OtoRoot.load(); // Always true
    this->blockSignals(false);

    OtoCache.clear();
    loadOtoCache(&OtoRoot);

    return otoLoad;
}

bool QVoiceBank::saveOto() {
    this->blockSignals(true);
    bool otoSave = OtoRoot.save();
    this->blockSignals(false);

    OtoCache.clear();
    loadOtoCache(&OtoRoot);
    return otoSave;
}

bool QVoiceBank::restoreOto() {
    this->blockSignals(true);
    OtoRoot.clear();

    bool result = true;
    for (auto it = OtoCache.begin(); it != OtoCache.end(); ++it) {
        QString filename = it.key();
        QString dirname = PathFindUpper(filename);

        QDir dir;
        if (dir.exists(dirname)) {
            dir.mkpath(dirname);
        }
        QOtoIni file(filename);
        file.OtoSamples = it.value();
        if (!file.save()) {
            result = false;
            break;
        }
    }

    if (!result) {
        return false;
    }

    bool otoLoad = loadOto();
    this->blockSignals(false);
    return otoLoad;
}

void QVoiceBank::clearOto() {
    this->blockSignals(true);
    OtoRoot.reset();
    this->blockSignals(false);
}

bool QVoiceBank::loadCore() {
    if (!isDirExist(m_dirname)) {
        return false;
    }
    bool otoLoad = loadOto();
    bool charLoad = loadCharTxt();
    bool readmeLoad = ReadmeTxt.load();
    bool mapLoad = PrefixMap.load();

    return true;
}

bool QVoiceBank::saveCore() {
    if (!isDirExist(m_dirname)) {
        return false;
    }

    bool otoSave = saveOto();
    bool charSave = saveCharTxt();
    bool readmeSave = ReadmeTxt.save();
    bool mapSave = PrefixMap.save();

    return charSave && readmeSave && mapSave && otoSave;
}

bool QVoiceBank::restore() {
    if (!isDirExist(m_dirname)) {
        return false;
    }

    bool otoRestore = restoreOto();
    bool charRestore = saveCharTxt();
    bool readmeRestore = ReadmeTxt.save();
    bool mapRestore = PrefixMap.save();

    return charRestore && readmeRestore && mapRestore && otoRestore;
}

void QVoiceBank::resetCore() {
    VoiceInfo::resetCore();
    PrefixMap.clear();
    OtoRoot.clear();
}

void QVoiceBank::prepareCore() {
    VoiceInfo::prepareCore();
    ReadmeTxt.setFilename(m_dirname + Slash + FILE_NAME_VOICE_README);
    PrefixMap.setFilename(m_dirname + Slash + FILE_NAME_PREFIX_MAP);
    OtoRoot.setDirname(m_dirname);
}
