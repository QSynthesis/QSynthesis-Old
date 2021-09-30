#include "QVoiceBank.h"
#include "QUtils.h"
#include "Strings/UtaFilenames.h"

QVoiceBank::QVoiceBank(QObject *parent) : QObject(parent), VoiceInfo(Qs::Default) {
    init();
}

QVoiceBank::QVoiceBank(const QString &dir, QObject *parent)
    : QObject(parent), VoiceInfo(Qs::Default) {
    init();
    setDirname(dir);
}

QVoiceBank::~QVoiceBank() {
    clearOto();
}

void QVoiceBank::init() {
}

bool QVoiceBank::loadOto() {
    // Add Oto Dirs
    QStringList dirs = findRecursiveDirs(m_filename);
    dirs.prepend(m_filename);
    for (auto it = dirs.begin(); it != dirs.end(); ++it) {
        OtoInis.insert(*it, QOtoIni(*it));
    }

    bool otoLoad = true;
    for (auto it = OtoInis.begin(); it != OtoInis.end(); ++it) {
        otoLoad &= it->load();
    }
    return otoLoad;
}

bool QVoiceBank::saveOto() {
    bool otoLoad = true;
    for (auto it = OtoInis.begin(); it != OtoInis.end(); ++it) {
        otoLoad &= it->save();
    }
    return otoLoad;
}

bool QVoiceBank::restoreOto() {
    bool result = true;
    for (auto it = OtoInis.begin(); it != OtoInis.end(); ++it) {
        QString dirname = it->dirname();

        QDir dir;
        if (dir.exists(dirname)) {
            if (!dir.mkpath(dirname)) {
                result = false;
                break;
            }
        }
        if (!it->save()) {
            result = false;
            break;
        }
    }

    if (!result) {
        return false;
    }
    return loadOto();
}

void QVoiceBank::clearOto() {
    OtoInis.clear();
}

bool QVoiceBank::loadCore(bool *valid) {
    if (!isDirExist(m_filename)) {
        return false;
    }

    bool otoLoad = loadOto();
    bool charLoad = VoiceInfo::loadCore(valid);
    bool readmeLoad = ReadmeTxt.load();
    bool mapLoad = PrefixMap.load();

    return otoLoad && charLoad && readmeLoad && mapLoad;
}

bool QVoiceBank::saveCore() {
    if (!isDirExist(m_filename)) {
        return false;
    }

    bool charSave = VoiceInfo::saveCore();
    bool readmeSave = ReadmeTxt.save();
    bool mapSave = PrefixMap.save();
    bool otoSave = saveOto();

    return charSave && readmeSave && mapSave && otoSave;
}

bool QVoiceBank::restore() {
    QDir dir(m_filename);
    if (!dir.exists()) {
        if (!dir.mkpath(m_filename)) {
            return false;
        }
    }

    bool charRestore = VoiceInfo::load();
    bool readmeRestore = ReadmeTxt.save();
    bool mapRestore = PrefixMap.save();
    bool otoRestore = restoreOto();

    return charRestore && readmeRestore && mapRestore && otoRestore;
}

void QVoiceBank::resetCore() {
    VoiceInfo::resetCore();
    ReadmeTxt.clear();
    PrefixMap.clear();
    OtoInis.clear();
}

void QVoiceBank::prepareCore() {
    VoiceInfo::prepareCore();
    ReadmeTxt.setDirname(m_filename);
    PrefixMap.setDirname(m_filename);
}
