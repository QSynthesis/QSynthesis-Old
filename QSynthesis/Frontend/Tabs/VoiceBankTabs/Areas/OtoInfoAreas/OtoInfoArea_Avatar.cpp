#include "../../VoiceBankGroup.h"
#include "../OtoInfoArea.h"

QString OtoInfoArea::avatar() const {
    return m_avatar;
}

bool OtoInfoArea::setAvatar(const QString &path) {
    if (!isFileExist(path) || !m_image.load(path)) {
        resetAvatar();
        return false;
    }

    lbImage->setScaledContents(true);
    lbImage->setPixmap(m_image);

    m_avatar = path;
    return true;
}

void OtoInfoArea::resetAvatar() {
    m_image = createBitmapFromSVG_W(":/images/user-fill.svg", lbImage->size(), Qt::darkGray);
    lbImage->setScaledContents(true);
    lbImage->setPixmap(m_image);
    m_avatar = "";
}

QPixmap OtoInfoArea::image() const {
    return m_image;
}

void OtoInfoArea::handleRevealAvatar() {
    if (isFileExist(m_avatar)) {
        RevealFile(m_avatar);
    }
}

void OtoInfoArea::handleReplaceAvatar(QString path) {
    QString org = m_avatar;
    //    if (!isSubDir(m_ptrs->tab->filename(), path)) {
    //        QMessageBox::warning(nullptr, MainTitle,
    //                             tr("Please select an image inside the voice folder!"));
    //        return;
    //    }
    if (!setAvatar(path)) {
        return;
    }
    handleAvatarChanged(m_avatar, org);
}

void OtoInfoArea::handleRemoveAvatar() {
    QString org = m_avatar;
    resetAvatar();
    handleAvatarChanged(m_avatar, org);
}
