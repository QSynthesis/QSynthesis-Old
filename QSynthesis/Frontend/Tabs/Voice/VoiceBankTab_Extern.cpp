#include "VoiceBankTab.h"
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
    otoIni.OtoSamples = tab->otoSamples();

    bool res = otoIni.toLocalFile(filename);
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

void VoiceBankTab::moveUp() {
    dataArea->currentTab()->moveUp();
}

void VoiceBankTab::moveDown() {
    dataArea->currentTab()->moveDown();
}

void VoiceBankTab::moveTop() {
    dataArea->currentTab()->moveTop();
}

void VoiceBankTab::moveBottom() {
    dataArea->currentTab()->moveBottom();
}

void VoiceBankTab::remove() {
    dataArea->currentTab()->remove();
}

void VoiceBankTab::duplicate() {
    dataArea->currentTab()->duplicate();
}
