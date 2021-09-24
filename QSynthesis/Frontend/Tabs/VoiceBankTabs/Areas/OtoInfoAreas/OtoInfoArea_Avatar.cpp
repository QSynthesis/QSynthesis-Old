#include "../../VoiceBankGroup.h"
#include "../OtoInfoArea.h"

QString OtoInfoArea::avatar() const {
    return m_avatar;
}

QPixmap OtoInfoArea::avatarImage() const {
    return m_avatarImg;
}

bool OtoInfoArea::setAvatar(const QString &path) {
    if (!isFileExist(path) || !m_avatarImg.load(path)) {
        resetAvatar();
        return false;
    }

    lbImage->setScaledContents(true);
    lbImage->setPixmap(m_avatarImg);

    m_avatar = path;
    return true;
}

void OtoInfoArea::resetAvatar() {
    m_avatarImg = createBitmapFromSVG_W(":/images/user-fill.svg", lbImage->size(), Qt::darkGray);
    lbImage->setScaledContents(true);
    lbImage->setPixmap(m_avatarImg);
    m_avatar = "";
}

QString OtoInfoArea::sprite() const {
    return m_sprite;
}

QPixmap OtoInfoArea::spriteImage() const {
    return m_spriteImg;
}

bool OtoInfoArea::setSprite(const QString &path) {
    if (!isFileExist(path) || !m_spriteImg.load(path)) {
        resetAvatar();
        return false;
    }

    imageTab->content()->setMargin(0);
    imageTab->content()->setText("");
    imageTab->content()->setPixmap(m_spriteImg);
    imageTab->content()->adjustSize();
    m_sprite = path;

    return true;
}

void OtoInfoArea::resetSprite() {
    m_spriteImg = QPixmap();
    imageTab->content()->setMargin(5);
    imageTab->content()->setText(tr("Null"));
    imageTab->content()->adjustSize();
    m_sprite = "";
}

void OtoInfoArea::handleRevealAvatar() {
    if (isFileExist(m_avatar)) {
        RevealFile(m_avatar);
    }
}

void OtoInfoArea::handleReplaceAvatar(QString path) {
    QString org = m_avatar;
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

void OtoInfoArea::handleRevealSprite() {
    if (isFileExist(m_sprite)) {
        RevealFile(m_sprite);
    }
}

void OtoInfoArea::handleReplaceSprite(QString path) {
    QString org = m_sprite;
    if (!setSprite(path)) {
        return;
    }
    handleSpriteChanged(m_sprite, org);
}

void OtoInfoArea::handleRemoveSprite() {
    QString org = m_sprite;
    resetSprite();
    handleSpriteChanged(m_sprite, org);
}
