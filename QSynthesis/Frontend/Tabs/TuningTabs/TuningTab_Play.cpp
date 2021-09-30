#include "../TuningTab.h"
#include "Areas/Editor/NotesArea.h"
#include "Forms/EditorForm.h"
#include "Interfaces/TracksInterface.h"
#include "ProjectInfoHandler.h"
#include "TuningGroup.h"

void TuningTab::initPlayer() {
    m_player = new QMediaPlayer(this);
    m_player->setNotifyInterval(20);

    m_playing = false;
    m_playable = false;

    connect(m_player, &QMediaPlayer::positionChanged, this, &TuningTab::onPlaying);
    connect(m_player, &QMediaPlayer::stateChanged, this, &TuningTab::handleStateChanged);
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &TuningTab::handleStatusChanged);
}

void TuningTab::play() {
    if (m_player->state() == QMediaPlayer::PlayingState) {
        pause();
    } else if (m_player->state() == QMediaPlayer::PausedState && m_playable) {
        resume();
    } else if (isFreeButPlaying() && renderCore()) {
        setPlayable(true);
        setMedia(QMediaContent(QUrl::fromLocalFile(m_workingDir + Slash + FILE_NAME_TEMP_AUDIO)));
        m_player->play();
    }
}

void TuningTab::stop() {
    m_player->stop();
}

void TuningTab::jump(qint64 position, bool play) {
    if (!m_playable) {
        return;
    }
    m_player->setPosition(position);
    if (play) {
        m_player->play();
    }
}

void TuningTab::pause() {
    m_player->pause();
}

void TuningTab::resume() {
    m_player->play();
}

qint64 TuningTab::duration() const {
    return m_player->duration();
}

qint64 TuningTab::position() const {
    return m_player->position();
}

void TuningTab::replay() {
    jump(0);
}

bool TuningTab::isPlaying() const {
    return m_playing;
}

void TuningTab::setPlaying(bool playing) {
    m_playing = playing;

    if (!playing) {
        m_ptrs->notesArea->stopPlaying();
    }

    m_ptrs->editorShell->updatePlayStatus(playing);
}

void TuningTab::setPlayable(bool playable) {
    if (!playable && m_playing) {
        stop();
    }
    m_playable = playable;
}

void TuningTab::forcePausePlaying() {
    if (isPlaying()) {
        pause();
    }
}

void TuningTab::onPlaying(qint64 n) {
    if (m_playing) {
        m_ptrs->notesArea->advancePlaying(n);
    }
}

void TuningTab::setMedia(const QMediaContent &media) {
    m_player->setMedia(media);
}

void TuningTab::handleStateChanged(QMediaPlayer::State newState) {
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

void TuningTab::handleStatusChanged(QMediaPlayer::MediaStatus newStatus) {
    if (newStatus == QMediaPlayer::InvalidMedia) {
        QString title = MainTitle;
        QString content = tr("Wave file format error, please check the settings!");

        QMessageBox::warning(this, title, content);
    }
}
