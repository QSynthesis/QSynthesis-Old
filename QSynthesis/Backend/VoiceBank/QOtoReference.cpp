#include "QOtoReference.h"
#include "QPrefixMap.h"
#include "QVoiceBank.h"
#include "Strings/UtaFilenames.h"
#include "Tabs/VoiceBankTab.h"

QMap<QString, QPair<int, QOtoReference *>> QOtoReference::otoRefMap;

QOtoReference::QOtoReference(QObject *parent) : QObject(parent) {
    qDebug() << "[Oto Reference] Add";
}

QOtoReference::~QOtoReference() {
    qDebug() << "[Oto Reference] Remove";
}

bool QOtoReference::fromFiles(const QString &voiceDir) {
    m_voiceDir = voiceDir;

    m_spritePath.clear();
    if (!(loadPrefixMap() && loadOtoIni())) {
        m_voiceDir.clear();
        return false;
    }
    VoiceInfo info(voiceDir);
    if (info.load()) {
        m_spritePath = info.sprite();
    }
    return true;
}

bool QOtoReference::fromMemory(const QVoiceBank &voicebank) {
    prefixMap = voicebank.PrefixMap.PrefixMap;
    suffixMap = voicebank.PrefixMap.SuffixMap;

    clearOtoIni();
    const QMap<QString, QOtoIni> &map = voicebank.OtoInis;
    for (auto it = map.begin(); it != map.end(); ++it) {
        registerSamples(it->OtoSamples);
    }

    m_spritePath = voicebank.sprite();
    return true;
}

void QOtoReference::sendRefresh() {
    emit refresh();
}

void QOtoReference::clearData() {
    clearOtoIni();
    clearPrefixMap();
    m_spritePath.clear();
}

bool QOtoReference::findSample(const QString &oLyric, QGenonSettings *oGenon, int oNoteNum) const {
    QMap<QString, QGenonSettings>::const_iterator it;
    QMap<int, QString>::const_iterator it2;
    if (oNoteNum > 0 && !(prefixMap.isEmpty() && suffixMap.isEmpty())) {
        // Find suffix
        it2 = suffixMap.find(oNoteNum);
        if (it2 != suffixMap.end()) {
            it = genonSettings.find(oLyric + it2.value());
            if (it != genonSettings.end()) {
                *oGenon = it.value();
                return 1;
            }
        }
        // Find prefix
        it2 = prefixMap.find(oNoteNum);
        if (it2 != prefixMap.end()) {
            it = genonSettings.find(it2.value() + oLyric);
            if (it != genonSettings.end()) {
                *oGenon = it.value();
                return 1;
            }
        }
    }
    // Find anyway
    it = genonSettings.find(oLyric);
    if (it != genonSettings.end()) {
        *oGenon = it.value();
        return 1;
    }
    return 0;
}

QStringList QOtoReference::findAliasStartsWith(const QString &prefix) const {
    QStringList res;
    for (auto it = genonSettings.begin(); it != genonSettings.end(); ++it) {
        if (it.key().startsWith(prefix, Qt::CaseInsensitive)) {
            res.append(it.key());
        }
    }
    return res;
}

bool QOtoReference::loadOtoIni() {
    bool result = true;

    QStringList dirs = findRecursiveDirs(m_voiceDir);
    dirs.prepend(m_voiceDir);

    clearOtoIni();
    for (auto it = dirs.begin(); it != dirs.end(); ++it) {
        QOtoIni oto(*it);
        if (!oto.load()) {
            result = false;
            break;
        }
        registerSamples(oto.OtoSamples);
    }

    if (!result) {
        clearOtoIni();
    }
    return result;
}

bool QOtoReference::loadPrefixMap() {
    QPrefixMap file(m_voiceDir);
    clearPrefixMap();
    if (!file.load()) {
        return false;
    }
    prefixMap = file.PrefixMap;
    suffixMap = file.SuffixMap;
    return true;
}

void QOtoReference::clearOtoIni() {
    genonSettings.clear();
    flags.clear();
}

void QOtoReference::clearPrefixMap() {
    prefixMap.clear();
    suffixMap.clear();
}

void QOtoReference::registerSamples(const QOtoSampleList &samples) {
    for (auto it = samples.begin(); it != samples.end(); ++it) {
        const QOtoSample &sample = *it;
        for (auto it2 = sample.begin(); it2 != sample.end(); ++it2) {
            const QGenonSettings &genon = *it2;
            QString filename = PathFindFileName(genon.mFileName);
            QString fileBody = filename.mid(0, filename.lastIndexOf("."));
            QString alias = genon.mAlias;

            // Register filename
            if (!fileBody.isEmpty()) {
                auto it3 = flags.find(fileBody);
                if (it3 == flags.end() || it3.value() == ofBlank) {
                    genonSettings[fileBody] = genon;
                    flags[fileBody] = ofFileName;
                }
            }
            // Register alias
            if (!alias.isEmpty()) {
                auto it3 = flags.find(alias);
                if (it3 == flags.end() || it3.value() != ofAlias) {
                    genonSettings[alias] = genon;
                    flags[alias] = ofAlias;
                }
            }
        }
    }
}

QString QOtoReference::voiceDir() const {
    return m_voiceDir;
}

QString QOtoReference::prefixMapPath() const {
    return m_voiceDir + Slash + FILE_NAME_PREFIX_MAP;
}

QString QOtoReference::spritePath() const {
    return m_voiceDir + Slash + m_spritePath;
}

bool QOtoReference::addReference(QString voiceDir, QOtoReference *&oto) {
    // Search
    QMap<QString, QPair<int, QOtoReference *>>::iterator it = otoRefMap.find(voiceDir);
    if (it != otoRefMap.end()) {
        it.value().first++;
        oto = it.value().second;
        return true;
    }

    // Plus
    QOtoReference *ref = new QOtoReference();
    if (!ref->fromFiles(voiceDir)) {
        return false;
    }

    QMap<QString, QPair<int, QOtoReference *>>::iterator it2 =
        otoRefMap.insert(voiceDir, qMakePair(1, ref));
    oto = it2.value().second;

    return true;
}

bool QOtoReference::removeReference(QString voiceDir) {
    // Search
    QMap<QString, QPair<int, QOtoReference *>>::iterator it = otoRefMap.find(voiceDir);
    if (it == otoRefMap.end()) {
        return false;
    }

    // Subtract
    QPair<int, QOtoReference *> &pair = it.value();
    pair.first--;
    if (pair.first == 0) {
        delete pair.second;
        otoRefMap.erase(it);
    }
    return true;
}

QOtoReference *QOtoReference::findReference(QString voiceDir) {
    // Search
    QMap<QString, QPair<int, QOtoReference *>>::iterator it = otoRefMap.find(voiceDir);
    if (it != otoRefMap.end()) {
        return it.value().second;
    }
    return nullptr;
}

bool QOtoReference::refreshReference(QString voiceDir, const QVoiceBank &voicebank) {
    // Search
    QMap<QString, QPair<int, QOtoReference *>>::iterator it = otoRefMap.find(voiceDir);
    if (it == otoRefMap.end()) {
        return false;
    }
    // Refresh
    QOtoReference *ref = it.value().second;
    if (!ref->fromMemory(voicebank)) {
        return false;
    }
    ref->sendRefresh();
    return true;
}
