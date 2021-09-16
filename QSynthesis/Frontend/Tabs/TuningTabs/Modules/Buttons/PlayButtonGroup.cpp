#include "PlayButtonGroup.h"

PlayButtonGroup::PlayButtonGroup(QWidget *parent) : QWidget(parent) {
    QSizeF playGroupPadding(5, 5);
    QSize playGroupSize(24, 24);

    btnPlay = new VectorButton(false, playGroupPadding, this);
    btnStop = new VectorButton(true, playGroupPadding, this);
    btnStart = new VectorButton(true, playGroupPadding, this);
    btnEnd = new VectorButton(true, playGroupPadding, this);

    btnPlay->setFixedSize(playGroupSize);
    btnStop->setFixedSize(playGroupSize);
    btnStart->setFixedSize(playGroupSize);
    btnEnd->setFixedSize(playGroupSize);

    btnPlay->setIcons(":/images/PlayGroupBtn1_Line.svg", ":/images/PlayGroupBtn5_Line.svg");
    btnStop->setIcons(":/images/PlayGroupBtn2_Line.svg");
    btnStart->setIcons(":/images/PlayGroupBtn3_Line.svg");
    btnEnd->setIcons(":/images/PlayGroupBtn4_Line.svg");

    connect(btnPlay, &VectorButton::clicked, this, &PlayButtonGroup::onPlayBtnClicked);
    connect(btnStop, &VectorButton::clicked, this, &PlayButtonGroup::onStopBtnClicked);
    connect(btnStart, &VectorButton::clicked, this, &PlayButtonGroup::onStartBtnClicked);
    connect(btnEnd, &VectorButton::clicked, this, &PlayButtonGroup::onEndBtnClicked);

    mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);

    mainLayout->addWidget(btnPlay);
    mainLayout->addWidget(btnStop);
    mainLayout->addWidget(btnStart);
    mainLayout->addWidget(btnEnd);

    setLayout(mainLayout);

    adjustSize();
    setFixedWidth(width());
}

void PlayButtonGroup::onPlayBtnClicked() {
    emit play();
}

void PlayButtonGroup::onStopBtnClicked() {
    emit stop();
}

void PlayButtonGroup::onStartBtnClicked() {
    emit start();
}

void PlayButtonGroup::onEndBtnClicked() {
    emit end();
}
