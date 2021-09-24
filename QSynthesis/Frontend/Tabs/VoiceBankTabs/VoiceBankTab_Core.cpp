#include "../VoiceBankTab.h"
#include "VoiceBank/QOtoReference.h"

bool VoiceBankTab::load() {
    bool aResult;

    voicebank.setDirname(m_filename);
    aResult = voicebank.load();

    if (!aResult) {
        QMessageBox::warning(this, MainTitle, tr("Unable to open folder!"));
        voicebank.reset();
    } else {
        loadCore();
    }

    updateTabName();
    return aResult;
}

bool VoiceBankTab::save() {
    if (!saveCore()) {
        return false;
    }
    bool aResult = voicebank.save();
    if (!aResult) {
        // No permission granted to write file
        QMessageBox::warning(this, MainTitle, tr("Unable to modify files!"));
    } else {
        updateOtoReferences();
        savedHistoryIndex = historyIndex; // Update saved history index
        setEdited(false);
    }

    updateTabName();
    return aResult;
}

bool VoiceBankTab::restore() {
    clearHistory();
    if (!voicebank.restore()) {
        QMessageBox::warning(this, MainTitle, tr("Unable to restore voice database!"));
        return false;
    }

    visionArea->reset();
    dataArea->removeAll();

    loadCore();
    setEdited(false);
    return true;
}

void VoiceBankTab::awake() {
    CentralTab::awake();

    handleBlocks();
}

void VoiceBankTab::sleep() {
    CentralTab::sleep();

    if (otoTimer->isActive()) {
        otoTimer->stop();
    }
}

void VoiceBankTab::enter() {
    CentralTab::enter();
    handleBlocks();
}

void VoiceBankTab::leave() {
    CentralTab::leave();

    if (otoTimer->isActive()) {
        otoTimer->stop();
    }
    forcePausePlaying();
}

void VoiceBankTab::loadCore() {
    // Char Text
    infoArea->setName(voicebank.name());
    infoArea->setAuthor(voicebank.author());
    infoArea->setAvatar(m_filename + Slash + voicebank.avatar());
    infoArea->setSprite(m_filename + Slash + voicebank.sprite());

    // Readme Text
    infoArea->setText(voicebank.ReadmeTxt.text());

    // Prefix Map
    infoArea->setPrefixMap(voicebank.PrefixMap.PrefixMap);
    infoArea->setSuffixMap(voicebank.PrefixMap.SuffixMap);

    // Oto
    const QMap<QString, QOtoLevel *> &map = voicebank.OtoLevels;
    for (auto it = map.begin(); it != map.end(); ++it) {
        QOtoLevel *level = it.value();
        dataArea->addTable(level->dirname(), level->otoData());
    }
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
    voicebank.ReadmeTxt.setText(infoArea->text());

    // Prefix Map
    voicebank.PrefixMap.PrefixMap = infoArea->prefixMap();
    voicebank.PrefixMap.SuffixMap = infoArea->suffixMap();

    // Oto
    const QMap<QString, OtoTableTab *> &map = dataArea->TableMap;
    for (auto it = map.begin(); it != map.end(); ++it) {
        OtoTableTab *tab = it.value();
        auto it2 = voicebank.OtoLevels.find(tab->dirname());
        if (it2 != voicebank.OtoLevels.end()) {
            it2.value()->setOtoData(tab->OtoSamples());
        }
    }
    return true;
}
