#include "PlayerLabel.h"

#include <QLayoutItem>

PlayerLabel::PlayerLabel(QWidget *parent) : QWidget(parent) {
    mainLayout = new QGridLayout(this);

    slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(100);

    QSizeF playGroupPadding(4, 4);
    QSize playGroupSize(24, 24);

    btnPlay = new VectorButton(false, playGroupPadding, this);
    btnABPlay = new VectorButton(true, playGroupPadding, this);

    btnPlay->setProperty("type", "sample");
    btnABPlay->setProperty("type", "sample");

    btnPlay->setIcons(":/images/PlayGroupBtn1_Line.svg", ":/images/PlayGroupBtn5_Line.svg");
    btnABPlay->setIcons(":/images/PlayGroupBtn6_Line.svg");

    btnPlay->setFixedSize(playGroupSize);
    btnABPlay->setFixedSize(playGroupSize);

    connect(slider, &QSlider::sliderPressed, this, &PlayerLabel::handleSliderPressed);
    connect(slider, &QSlider::sliderMoved, this, &PlayerLabel::handleSliderMoved);
    connect(slider, &QSlider::sliderReleased, this, &PlayerLabel::handleSliderReleased);

    connect(btnPlay, &VectorButton::clicked, this, &PlayerLabel::handlePlayBtnClicked);
    connect(btnABPlay, &VectorButton::clicked, this, &PlayerLabel::handleABPlayBtnClicked);

    mainLayout->addWidget(slider, 0, 0, 1, 4);
    mainLayout->addWidget(new QWidget(), 1, 0);
    mainLayout->addWidget(btnPlay, 1, 1);
    mainLayout->addWidget(btnABPlay, 1, 2);
    mainLayout->addWidget(new QWidget(), 1, 3);

    setLayout(mainLayout);

    m_abOnly = false;
    m_pressed = false;

    clearPercent();
}

PlayerLabel::~PlayerLabel() {
}

double PlayerLabel::percentA() const {
    return m_percentA;
}

void PlayerLabel::setPercentA(double percentA) {
    m_percentA = percentA;
}

double PlayerLabel::percentB() const {
    return m_percentB;
}

void PlayerLabel::setPercentB(double percentB) {
    m_percentB = percentB;
}

void PlayerLabel::clearPercent() {
    m_percentA = 0;
    m_percentB = 1;
}

void PlayerLabel::advancePlaying(double percent) {
    if (m_abOnly && percent >= m_percentB) {
        emit played();
    }
    if (m_pressed) {
        return;
    }
    slider->setValue(slider->maximum() * percent);
}

bool PlayerLabel::abOnly() const {
    return m_abOnly;
}

bool PlayerLabel::pressed() const {
    return m_pressed;
}

void PlayerLabel::setPlaying(bool playing) {
    btnPlay->setStatus(playing);
    if (!playing) {
        m_abOnly = false;
    }
}

void PlayerLabel::setABOnly(bool value) {
    m_abOnly = value;
}

void PlayerLabel::handleSliderPressed() {
    m_pressed = true;
}

void PlayerLabel::handleSliderMoved(int position) {
}

void PlayerLabel::handleSliderReleased() {
    m_pressed = false;
    emit jumped(slider->value() / slider->maximum());
}

void PlayerLabel::handlePlayBtnClicked() {
    m_abOnly = false;
    emit played();
}

void PlayerLabel::handleABPlayBtnClicked() {
    m_abOnly = true;
    emit jumped(m_percentA);
    emit played(true);
}
