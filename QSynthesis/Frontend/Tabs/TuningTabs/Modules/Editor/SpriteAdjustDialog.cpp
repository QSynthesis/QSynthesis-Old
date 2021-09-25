#include "SpriteAdjustDialog.h"

SpriteAdjustDialog::SpriteAdjustDialog(QWidget *parent) : TransparentContainer(parent) {
    mainLayout = new QVBoxLayout(this);

    checkBoxesLayout = new QHBoxLayout();

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

    connect(cbVisible, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleVisibilityClicked);

    connect(scAlpha, &SlideLineControl::valueChanged, this,
            &SpriteAdjustDialog::handleAlphaChanged);

    connect(cbTopLeft, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleCornerClicked);
    connect(cbTopRight, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleCornerClicked);
    connect(cbBottomLeft, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleCornerClicked);
    connect(cbBottomRight, &QCheckBox::clicked, this, &SpriteAdjustDialog::handleCornerClicked);

    checkBoxesLayout->addWidget(cbTopLeft);
    checkBoxesLayout->addWidget(cbTopRight);
    checkBoxesLayout->addWidget(cbBottomLeft);
    checkBoxesLayout->addWidget(cbBottomRight);

    mainLayout->addWidget(cbVisible);
    mainLayout->addWidget(scAlpha);
    mainLayout->addLayout(checkBoxesLayout);

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
