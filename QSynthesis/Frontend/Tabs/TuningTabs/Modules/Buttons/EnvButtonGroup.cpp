#include "EnvButtonGroup.h"

EnvButtonGroup::EnvButtonGroup(QWidget *parent) : QWidget(parent) {
    QSizeF envGroupPadding(1, 1);

    btnP2P3 = new VectorButton(true, envGroupPadding, this);
    btnP1P4 = new VectorButton(true, envGroupPadding, this);
    btnReset = new VectorButton(true, envGroupPadding, this);

    btnP2P3->setIcons(":/images/EnvGroupBtn1.svg");
    btnP1P4->setIcons(":/images/EnvGroupBtn2.svg");
    btnReset->setIcons(":/images/EnvGroupBtn3.svg");

    btnP2P3->setFixedSize(24, 24);
    btnP1P4->setFixedSize(24, 24);
    btnReset->setFixedSize(24, 24);

    connect(btnP2P3, &VectorButton::clicked, this, &EnvButtonGroup::onP2P3BtnClicked);
    connect(btnP1P4, &VectorButton::clicked, this, &EnvButtonGroup::onP1P4BtnClicked);
    connect(btnReset, &VectorButton::clicked, this, &EnvButtonGroup::onResetBtnClicked);

    mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);

    mainLayout->addWidget(btnP2P3);
    mainLayout->addWidget(btnP1P4);
    mainLayout->addWidget(btnReset);

    setLayout(mainLayout);

    adjustSize();
    setFixedWidth(width());
}

void EnvButtonGroup::onP2P3BtnClicked() {
    emit p2p3();
}

void EnvButtonGroup::onP1P4BtnClicked() {
    emit p1p4();
}

void EnvButtonGroup::onResetBtnClicked() {
    emit reset();
}
