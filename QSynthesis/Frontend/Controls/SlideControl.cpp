#include "SlideControl.h"

#include <cmath>

/*--------------------------------------滑块控制--------------------------------------*/
SlideControl::SlideControl(QWidget *parent) : QWidget(parent) {
    InitSlideControl("", 0);
}

SlideControl::SlideControl(QString text, QWidget *parent) : QWidget(parent) {

    InitSlideControl(text, 0);
}

SlideControl::SlideControl(QString text, double value, QWidget *parent) : QWidget(parent) {

    InitSlideControl(text, value);
}

void SlideControl::setMaximum(double value) {
    maximum = value;
    pSpinBox->setMaximum(maximum);
    pSlider->setMaximum(maximum * pow(10, pSpinBox->decimals()));
}
void SlideControl::setMinimum(double value) {
    minimum = value;
    pSpinBox->setMinimum(minimum);
    pSlider->setMinimum(minimum * pow(10, pSpinBox->decimals()));
}
void SlideControl::setSingleStep(double value) {
    singleStep = value;
    pSpinBox->setDecimals(-log10(value));
}
void SlideControl::setValue(double value) {
    this->value = value;
    pSpinBox->setValue(value);
    pSlider->setValue(value * pow(10, pSpinBox->decimals()));
}

double SlideControl::getValue() const {
    return pSlider->value() / pow(10, pSpinBox->decimals());
}

QDoubleSpinBox *SlideControl::SpinBox() const {
    return pSpinBox;
}

QSlider *SlideControl::Slider() const {
    return pSlider;
}

void SlideControl::setCaption(QString caption) {
    pLabel->setText(caption);
    pLabel->adjustSize();
}

QString SlideControl::caption() const {
    return pLabel->text();
}

void SlideControl::InitSlideControl(QString text, double value) {
    QFont font(mainFont());

    // 标签
    pLabel = new QLabel(text, this);
    pLabel->setFont(font);
    pLabel->adjustSize();

    // 微调框
    pSpinBox = new QDoubleSpinBox(this);
    pSpinBox->setDecimals(2);
    pSpinBox->setFont(font);
    pSpinBox->adjustSize();

    // 滑动条
    pSlider = new QSlider(this);
    pSlider->setOrientation(Qt::Horizontal); // 水平方向
    pSlider->adjustSize();

    setMinimum(0);    // 最小值
    setMaximum(100);  // 最大值
    setSingleStep(1); // 步长
    setValue(value);

    pSlider->setFixedHeight(18);

    pLayout = new QGridLayout(this);
    pLayout->setMargin(0);

    pLayout->addWidget(pLabel, 0, 0);
    pLayout->addWidget(pSpinBox, 0, 1);
    pLayout->addWidget(pSlider, 1, 0, 1, 2);

    setLayout(pLayout);

    connect(pSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onTextChanged(double)));
    connect(pSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderChanged(int)));
    bUnmodified = false;
}

void SlideControl::onModifyAction() {
    if (bUnmodified) {
        setUnmodified(false);
    }
}

void SlideControl::onSliderChanged(int n) {
    onModifyAction();
    pSpinBox->setValue(double(n) / pow(10, pSpinBox->decimals()));
}

void SlideControl::onTextChanged(double n) {
    onModifyAction();
    pSlider->setValue(n * pow(10, pSpinBox->decimals()));
}

void SlideControl::setProportion(int a, int b) {
    pLayout->setColumnStretch(0, a);
    pLayout->setColumnStretch(1, b);
}

void SlideControl::setMargin(int n) {
    pLayout->setMargin(n);
}

void SlideControl::setUnmodified(bool value) {
    if (value) {
        pSpinBox->setStyleSheet("background-color:#E1E1E1;");
    } else {
        pSpinBox->setStyleSheet("background-color:white;");
    }

    bUnmodified = value;
}

bool SlideControl::isUnmodified() {
    return bUnmodified;
}
