#include "SpriteAdjustDialog.h"

SpriteAdjustDialog::SpriteAdjustDialog(QWidget *parent) : TransparentContainer(parent) {
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);

    topLayout = new QHBoxLayout();
    bottomLayout = new QHBoxLayout();

    cbVisible = new QCheckBox(tr("Foreground visible"));
    scAlpha = new SlideLineControl(tr("Foreground opacity (0~100)"));

    scAlpha->setSpacing(15);
    scAlpha->setMinimum(0);
    scAlpha->setMaximum(100);
    scAlpha->setSingleStep(1);

    cbTopLeft = new QCheckBox(tr("Top left"));
    cbTopRight = new QCheckBox(tr("Top right"));
    cbBottomLeft = new QCheckBox(tr("Bottom left"));
    cbBottomRight = new QCheckBox(tr("Bottom right"));

    cbTopLeft->setAutoExclusive(true);
    cbTopRight->setAutoExclusive(true);
    cbBottomLeft->setAutoExclusive(true);
    cbBottomRight->setAutoExclusive(true);

    QSizeF padding2(5, 5);
    QSize btnSize2(24, 24);
    btnClose = new IconButton(padding2);
    btnClose->setIcon(":/images/close-line.svg");
    btnClose->setFixedSize(btnSize2);

    connect(cbVisible, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleVisibilityClicked);

    connect(scAlpha, &SlideLineControl::valueChanged, this,
            &SpriteAdjustDialog::handleAlphaChanged);

    connect(cbTopLeft, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleCornerClicked);
    connect(cbTopRight, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleCornerClicked);
    connect(cbBottomLeft, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleCornerClicked);
    connect(cbBottomRight, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleCornerClicked);

    connect(btnClose, &IconButton::clicked, this, &SpriteAdjustDialog::handleCloseBtnClicked);

    topLayout->addWidget(cbVisible);
    topLayout->addWidget(btnClose);

    bottomLayout->addWidget(cbTopLeft);
    bottomLayout->addWidget(cbTopRight);
    bottomLayout->addWidget(cbBottomLeft);
    bottomLayout->addWidget(cbBottomRight);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(scAlpha);
    mainLayout->addLayout(bottomLayout);

    setMinimumWidth(400);
}

SpriteAdjustDialog::~SpriteAdjustDialog() {
}

bool SpriteAdjustDialog::visibility() const {
    return cbVisible->isChecked();
}

int SpriteAdjustDialog::alpha() const {
    return int(scAlpha->getValue());
}

Qt::Corner SpriteAdjustDialog::corner() const {
    if (cbTopLeft->isChecked()) {
        return Qt::TopLeftCorner;
    }
    if (cbTopRight->isChecked()) {
        return Qt::TopRightCorner;
    }
    if (cbBottomLeft->isChecked()) {
        return Qt::BottomLeftCorner;
    }
    return Qt::BottomRightCorner;
}

void SpriteAdjustDialog::setVisibility(bool visible) {
    cbVisible->setChecked(visible);
}

void SpriteAdjustDialog::setAlpha(int alpha) {
    scAlpha->setValue(alpha);
}

void SpriteAdjustDialog::setCorner(Qt::Corner corner) {
    cbTopLeft->setChecked(corner == Qt::TopLeftCorner);
    cbTopRight->setChecked(corner == Qt::TopRightCorner);
    cbBottomLeft->setChecked(corner == Qt::BottomLeftCorner);
    cbBottomRight->setChecked(corner == Qt::BottomRightCorner);
}

void SpriteAdjustDialog::handleVisibilityClicked() {
    emit visibilityChanged(visibility());
}

void SpriteAdjustDialog::handleCornerClicked() {
    emit cornerChanged(corner());
}

void SpriteAdjustDialog::handleAlphaChanged(double value) {
    emit alphaChanged(int(value));
}

void SpriteAdjustDialog::handleCloseBtnClicked() {
    emit closeRequested();
}
