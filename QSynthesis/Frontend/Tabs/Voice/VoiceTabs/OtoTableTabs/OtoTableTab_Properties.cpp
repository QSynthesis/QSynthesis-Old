#include "../OtoTableTab.h"

#include <QSound>

QString OtoTableTab::dirname() const {
    return m_dirname;
}

void OtoTableTab::setDirname(const QString &dirname) {
    m_dirname = dirname;
}

void OtoTableTab::playSound(int row) const {
    QGenonSettings genon = getGenonSettings(row);
    if (isFileExist(genon.mFileName)) {
        QSound::play(genon.mFileName);
    }
}

QColor OtoTableTab::invalidColor() const {
    return m_invalidColor;
}

void OtoTableTab::setInvalidColor(const QColor &invalidColor) {
    m_invalidColor = invalidColor;
    emit colorChanged();
}

QOtoSampleList OtoTableTab::otoSamples() const {
    return m_otoSamples;
}

QColor OtoTableTab::emptyColor() const {
    return m_emptyColor;
}

void OtoTableTab::setEmptyColor(const QColor &emptyColor) {
    m_emptyColor = emptyColor;
    emit colorChanged();
}

QColor OtoTableTab::normalColor() const {
    return m_normalColor;
}

void OtoTableTab::setNormalColor(const QColor &normalColor) {
    m_normalColor = normalColor;
    emit colorChanged();
}
