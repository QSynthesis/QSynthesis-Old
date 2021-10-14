#include "OtoPlayerArea.h"
#include "../../VoiceBankTab.h"
#include "../VoiceBankGroup.h"

OtoPlayerArea::OtoPlayerArea(VoiceBankTab *tab,QWidget *parent) : VoiceBankArea(tab, parent) {
    init();
}

OtoPlayerArea::~OtoPlayerArea() {
}

void OtoPlayerArea::init() {
    m_duration = 0;
    m_rate = 0;
    m_depth = 0;
    m_channels = 0;

    mainLayout = new QVBoxLayout(this);

    lbCaption = new QLabel();
    lbCaption->setAlignment(Qt::AlignCenter);

    controller = new PlayerLabel();

    mainLayout->addWidget(lbCaption);
    mainLayout->addWidget(controller);

    setLayout(mainLayout);

    connect(controller, &PlayerLabel::played, this, &OtoPlayerArea::handlePlayerPlayed);
    connect(controller, &PlayerLabel::jumped, this, &OtoPlayerArea::handlePlayerJumped);
}

void OtoPlayerArea::initExtern() {
}

void OtoPlayerArea::setMedia(const QGenonSettings &sample, double duration, int rate, int depth,
                             int channels) {
    m_duration = duration * 1000;
    m_rate = rate;
    m_depth = depth;
    m_channels = channels;

    receiveFromVision(sample);
}

void OtoPlayerArea::removeMedia() {
    m_ptrs->tab->setMedia(QMediaContent());

    m_sample.clear();
    m_duration = 0;
    m_rate = 0;
    m_depth = 0;
    m_channels = 0;

    controller->clearPercent();

    updateCaption();
}

void OtoPlayerArea::updateCaption() {
    if (m_channels == 0) {
        lbCaption->setText("");
    } else {
        lbCaption->setText(
            tr("%1Hz %2bit ").arg(QString::number(m_rate), QString::number(m_depth)) +
            (m_channels == 1 ? tr("Mono") : tr("Stereo")));
    }
}

void OtoPlayerArea::advancePlaying(qint64 position) {
    controller->advancePlaying(double(position) / m_ptrs->tab->duration());
}

void OtoPlayerArea::setPlaying(bool playing) {
    controller->setPlaying(playing);
}

void OtoPlayerArea::receiveFromVision(const QGenonSettings &sample) {
    QString filename = sample.mFileName;

    if (!isSameFile(filename, m_sample.mFileName)) {
        m_ptrs->tab->setMedia(QMediaContent(QUrl::fromLocalFile(filename)));
        m_sample = sample;
    }

    if (m_duration != 0) {
        controller->setPercentA(sample.mOffset / m_duration);
        controller->setPercentB(sample.mBlank >= 0
                                    ? ((m_duration - sample.mBlank) / m_duration)
                                    : ((sample.mOffset - sample.mBlank) / m_duration));
    } else {
        controller->clearPercent();
    }

    updateCaption();
}

void OtoPlayerArea::handlePlayerPlayed(bool play) {
    if (play && !m_ptrs->tab->isPlaying()) {
        m_ptrs->tab->play();
    } else if (!play) {
        m_ptrs->tab->play();
    }
    controller->setPlaying(m_ptrs->tab->isPlaying());
}

void OtoPlayerArea::handlePlayerJumped(double percent) {
    m_ptrs->tab->jump(m_duration * percent, m_ptrs->tab->isPlaying());
}
