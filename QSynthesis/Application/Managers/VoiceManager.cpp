#include "MiniSystem/MiniSystemNotifier.h"
#include "UTAU/QUtauStrings.h"
#include "application.h"

#include <QDir>
#include <QFileInfo>

VoiceManager::VoiceManager(QObject *parent) : QObject(parent) {
    notifier = nullptr;
}

VoiceManager::~VoiceManager() {
}

QList<VoiceInfo> VoiceManager::voices() const {
    QList<VoiceInfo> voices;
    for (auto it = voiceMap.begin(); it != voiceMap.end(); ++it) {
        const VoiceInfo &voice = it.value();
        voices.append(voice);
    }
    return voices;
}

QString VoiceManager::dirname() const {
    return m_dirname;
}

void VoiceManager::setDirname(const QString &dirname) {
    m_dirname = dirname;
}

bool VoiceManager::load() {
    QDir currDir(m_dirname);
    if (!currDir.exists()) {
        return false;
    }

    QStringList flist = currDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
    for (auto it = flist.begin(); it != flist.end(); ++it) {
        QString cur = *it;
        QString absoultPath = m_dirname + Slash + cur;
        VoiceInfo voice(absoultPath);
        if (voice.load()) {
            voiceMap.insert(cur, voice);
        }
    }

    notifier = qSystem->createNotifier(m_dirname, MiniSystem::Directory);
    connect(notifier, &MiniSystemNotifier::fileChanged, this, &VoiceManager::handleFileChanged);

    return true;
}

void VoiceManager::quit() {
    qSystem->removeNotifier(notifier);
    notifier = nullptr;
}

void VoiceManager::reloadVoice(const QString &key) {
    auto it = voiceMap.find(key);
    if (it != voiceMap.end()) {
        VoiceInfo &voice = it.value();
        if (!voice.load()) {
            voiceMap.erase(it);
        }
    } else {
        VoiceInfo voice(m_dirname + Slash + key);
        if (voice.load()) {
            voiceMap.insert(key, voice);
        }
    }
}

void VoiceManager::handleFileChanged(const QStringList &files) {
    for (const QString &filename : files) {
        QString pluginDir = PathFindNextLevel(filename, m_dirname);
        reloadVoice(pluginDir);
    }
    emit reloadRequested();
}
