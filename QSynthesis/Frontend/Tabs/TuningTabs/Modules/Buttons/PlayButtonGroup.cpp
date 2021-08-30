#include "PlayButtonGroup.h"

PlayButtonGroup::PlayButtonGroup(QWidget *parent) : QWidget(parent) {
    QSizeF playGroupPadding(6, 6);

    btnPlay = new VectorButton(false, playGroupPadding, this);
    btnStop = new VectorButton(true, playGroupPadding, this);
    btnStart = new VectorButton(true, playGroupPadding, this);
    btnEnd = new VectorButton(true, playGroupPadding, this);

    btnPlay->setFixedSize(24, 24);
    btnStop->setFixedSize(24, 24);
    btnStart->setFixedSize(24, 24);
    btnEnd->setFixedSize(24, 24);

    btnPlay->setIcons(":/images/PlayGroupBtn1.svg", ":/images/PlayGroupBtn5.svg");
    btnStop->setIcons(":/images/PlayGroupBtn2.svg");
    btnStart->setIcons(":/images/PlayGroupBtn3.svg");
    btnEnd->setIcons(":/images/PlayGroupBtn4.svg");

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
