#include "../VoiceBankTab.h"
#include "VoiceBank/QOtoReference.h"

void VoiceBankTab::updateOtoReferences() {
    QOtoReference::refreshReference(m_filename, voicebank);
}

bool VoiceBankTab::locateSample(const QGenonSettings &genon) {
    return dataArea->locateSample(genon);
}

void VoiceBankTab::locatePrefix(int noteNum) {
    infoArea->locatePrefix(noteNum);
}

bool VoiceBankTab::exportCurrentSettings(const QString &filename) {
    if (filename.startsWith(m_filename)) {
        QMessageBox::warning(this, MainTitle, tr("Don't save to current voice folder!"));
        return false;
    }

    OtoTableTab *tab = dataArea->currentTab();

    QOtoIni otoIni;
    otoIni.setFilename(filename);
    otoIni.OtoSamples = tab->OtoSamples();

    bool res = otoIni.save();
    if (!res) {
        QMessageBox::warning(this, MainTitle, tr("Unable to write file!"));
    }
    return res;
}

void VoiceBankTab::setOffsetByCursor() {
    visionArea->setOffsetByCursor();
}

void VoiceBankTab::setConstantByCursor() {
    visionArea->setConstantByCursor();
}

void VoiceBankTab::setBlankByCursor() {
    visionArea->setBlankByCursor();
}

void VoiceBankTab::setPreUttrByCursor() {
    visionArea->setPreUttrByCursor();
}

void VoiceBankTab::setOverlapByCursor() {
    visionArea->setOverlapByCursor();
}
