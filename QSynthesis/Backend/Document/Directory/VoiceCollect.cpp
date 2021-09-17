#include "VoiceCollect.h"

VoiceCollect::VoiceCollect(QObject *parent) : DirectoryCollect(parent) {
}

VoiceCollect::VoiceCollect(QString dir, QObject *parent) : DirectoryCollect(dir, parent) {
}

QList<VoiceInfo *> VoiceCollect::dirs() const {
    QList<VoiceInfo *> res;
    for (auto it = m_dirs.begin(); it != m_dirs.end(); ++it) {
        VoiceInfo *voice = qobject_cast<VoiceInfo *>(*it);
        if (voice->valid()) {
            res.append(voice);
        }
    }
    return res;
}

DirectoryManager *VoiceCollect::addDirCore(const QString &dir, bool init) {
    VoiceInfo *voice = new VoiceInfo(dir, this);
    voice->load();
    if (!isDirExist(dir)) {
        delete voice;
        return nullptr;
    }
    voice->setAutoReload(true);
    connect(voice, &VoiceInfo::charTxtChanged, this, &VoiceCollect::handleChildChanged);
    return voice;
}

void VoiceCollect::handleChildChanged() {
    emit changed();
}
