#include "VoiceBankTab.h"
#include "VoiceBank/QOtoReference.h"

bool VoiceBankTab::load() {
    bool aResult;

    voicebank.setDirname(m_filename);
    aResult = voicebank.load();

    if (!aResult) {
        QMessageBox::warning(this, MainTitle, tr("Unable to open folder!"));
        voicebank.reset();
    } else {
        addNotifier();
    }

    loadCore();
    updateTabName();
    return aResult;
}

bool VoiceBankTab::save() {
    if (!saveCore()) {
        return false;
    }

    removeNotifier();
    bool aResult = voicebank.save();

    if (!aResult) {
        // No permission granted to write file
        QMessageBox::warning(this, MainTitle, tr("Unable to modify files!"));
    } else {
        updateOtoReferences();
        savedHistoryIndex = historyIndex; // Update saved history index
        setEdited(false);
    }

    addNotifier();

    return aResult;
}

bool VoiceBankTab::restore() {
    clearHistory();
    if (!voicebank.restore()) {
        QMessageBox::warning(this, MainTitle, tr("Unable to restore voice database!"));
        return false;
    }

    visionArea->reset();

    loadCore();
    setEdited(false);
    return true;
}

void VoiceBankTab::awake() {
    CentralTab::awake();
}

void VoiceBankTab::sleep() {
    CentralTab::sleep();
}

void VoiceBankTab::enter() {
    CentralTab::enter();
}

void VoiceBankTab::leave() {
    CentralTab::leave();
    forcePausePlaying();
}

void VoiceBankTab::loadCore() {
    // Char Text
    infoArea->setName(voicebank.name());
    infoArea->setAuthor(voicebank.author());
    infoArea->setAvatar(m_filename + Slash + voicebank.avatar());
    infoArea->setSprite(m_filename + Slash + voicebank.sprite());

    // Readme Text
    infoArea->setText(voicebank.ReadmeTxt.Text);

    // Prefix Map
    infoArea->setPrefixMap(voicebank.PrefixMap.PrefixMap);
    infoArea->setSuffixMap(voicebank.PrefixMap.SuffixMap);

    // Oto
    auto &map = voicebank.OtoInis;
    QList<QOtoIni> list;
    for (auto it = map.begin(); it != map.end(); ++it) {
        list.append(it.value());
    }
    dataArea->loadTables(list);
}

bool VoiceBankTab::saveCore() {
    QString avatarPath = infoArea->avatar();
    QString newAvatarPath = avatarPath;
    // Not in voice bank
    if (!avatarPath.isEmpty() && !avatarPath.startsWith(m_filename)) {
        newAvatarPath = m_filename + Slash + PathFindFileName(avatarPath);
        if (!infoArea->avatarImage().save(newAvatarPath)) {
            QMessageBox::information(this, MainTitle,
                                     tr("Unable to copy the image to voice bank directory!"));
            return false;
        }
        infoArea->setAvatar(newAvatarPath);
    }

    QString spritePath = infoArea->sprite();
    QString newSpritePath = spritePath;
    // Not in voice bank
    if (!spritePath.isEmpty() && !spritePath.startsWith(m_filename)) {
        newSpritePath = m_filename + Slash + PathFindFileName(spritePath);
        if (!infoArea->spriteImage().save(newSpritePath)) {
            QMessageBox::information(this, MainTitle,
                                     tr("Unable to copy the image to voice bank directory!"));
            return false;
        }
        infoArea->setSprite(newSpritePath);
    }

    // Char Text
    voicebank.setName(infoArea->name());
    voicebank.setAuthor(infoArea->author());
    voicebank.setAvatar(PathFindFileName(newAvatarPath, m_filename));
    voicebank.setSprite(PathFindFileName(newSpritePath, m_filename));

    // Readme Text
    voicebank.ReadmeTxt.Text = infoArea->text();

    // Prefix Map
    voicebank.PrefixMap.PrefixMap = infoArea->prefixMap();
    voicebank.PrefixMap.SuffixMap = infoArea->suffixMap();

    // Oto
    QList<QOtoIni> list = dataArea->exportTables();
    voicebank.OtoInis.clear();
    for (auto it = list.begin(); it != list.end(); ++it) {
        const QOtoIni &oto = *it;
        voicebank.OtoInis.insert(oto.dirname(), oto);
    }
    return true;
}

void VoiceBankTab::exitCore() {
    removeNotifier();
}
