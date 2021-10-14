#include "VoiceBankTab.h"
#include "VoiceBankGroup.h"

void VoiceBankTab::initPlayer() {
    m_player = new QMediaPlayer(this);
    m_player->setNotifyInterval(1);

    m_playing = false;
    m_playable = false;

    connect(m_player, &QMediaPlayer::positionChanged, this, &VoiceBankTab::onPlaying);
    connect(m_player, &QMediaPlayer::stateChanged, this, &VoiceBankTab::handleStateChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &VoiceBankTab::handleStatusChanged);
}

void VoiceBankTab::play() {
    if (m_player->state() == QMediaPlayer::PlayingState) {
        pause();
    } else if (m_playable) {
        m_player->play();
    }
}

void VoiceBankTab::replay() {
    jump(0);
}

void VoiceBankTab::stop() {
    m_player->stop();
}

void VoiceBankTab::jump(qint64 position, bool play) {
    if (!m_playable) {
        return;
    }
    m_player->setPosition(position);
    if (play) {
        m_player->play();
    }
}

void VoiceBankTab::pause() {
    m_player->pause();
}

void VoiceBankTab::resume() {
    m_player->play();
}

qint64 VoiceBankTab::duration() const {
    return m_player->duration();
}

qint64 VoiceBankTab::position() const {
    return m_player->position();
}

bool VoiceBankTab::isPlaying() const {
    return m_playing;
}

void VoiceBankTab::onPlaying(qint64 n) {
    playerArea->advancePlaying(n);
}

void VoiceBankTab::setMedia(const QMediaContent &media) {
    m_player->setMedia(media);
}

void VoiceBankTab::setPlaying(bool playing) {
    m_playing = playing;
    playerArea->setPlaying(playing);
}

void VoiceBankTab::setPlayable(bool playable) {
    if (!playable && m_playing) {
        stop();
    }
    m_playable = playable;
}

void VoiceBankTab::forcePausePlaying() {
    if (isPlaying()) {
        pause();
    }
}

void VoiceBankTab::handleStateChanged(QMediaPlayer::State newState) {
    if (newState == QMediaPlayer::StoppedState) {
        if (m_player->mediaStatus() == QMediaPlayer::EndOfMedia) {
            qDebug() << "Media Complete";
        } else {
            qDebug() << "Media Stop";
        }
        setPlaying(false);
    } else if (newState == QMediaPlayer::PlayingState) {
        qDebug() << "Media Play";
        setPlaying(true);
    } else if (newState == QMediaPlayer::PausedState) {
        qDebug() << "Media Pause";
        setPlaying(false);
    }
}

void VoiceBankTab::handleStatusChanged(QMediaPlayer::MediaStatus newStatus) {
    if (newStatus == QMediaPlayer::InvalidMedia) {
        QString title = MainTitle;
        QString content = tr("Audio file format error, please check the file!");

        QMessageBox::warning(this, title, content);
        setPlayable(false);
    } else {
        setPlayable(true);
    }
}
