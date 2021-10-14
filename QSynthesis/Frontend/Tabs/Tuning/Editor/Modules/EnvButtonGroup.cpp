#include "EnvButtonGroup.h"

EnvButtonGroup::EnvButtonGroup(QWidget *parent) :QWidget(parent) {
    QSizeF envGroupPadding(1, 1);
    QSize envGroupSize(24, 24);

    btnP2P3 = new VectorButton(true, envGroupPadding, this);
    btnP1P4 = new VectorButton(true, envGroupPadding, this);
    btnReset = new VectorButton(true, envGroupPadding, this);

    btnP2P3->setProperty("type", "title-bar-env");
    btnP1P4->setProperty("type", "title-bar-env");
    btnReset->setProperty("type", "title-bar-env");

    btnP2P3->setIcons(":/images/EnvGroupBtn2_Line.svg");
    btnP1P4->setIcons(":/images/EnvGroupBtn1_Line.svg");
    btnReset->setIcons(":/images/EnvGroupBtn3_Line.svg");

    btnP2P3->setToolTip(tr("Envelope crossFade (p2p3)"));
    btnP1P4->setToolTip(tr("Envelope crossFade (p1p4)"));
    btnReset->setToolTip(tr("Reset Envelope"));

    btnP2P3->setFixedSize(envGroupSize);
    btnP1P4->setFixedSize(envGroupSize);
    btnReset->setFixedSize(envGroupSize);

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
