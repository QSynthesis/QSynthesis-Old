#include "SlideControl.h"

#include <QStyle>
#include <cmath>

/*--------------------------------------滑块控制--------------------------------------*/
SlideControl::SlideControl(QWidget *parent) :QWidget(parent) {
    InitSlideControl("", 0);
}

SlideControl::SlideControl(QString text,QWidget *parent) :QWidget(parent) {

    InitSlideControl(text, 0);
}

SlideControl::SlideControl(QString text, double value,QWidget *parent) :QWidget(parent) {

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

    // 标签
    pLabel = new QLabel(text, this);
    pLabel->adjustSize();

    // 微调框
    pSpinBox = new FixedSpinBox(this);
    pSpinBox->setProperty("status", "normal");

    pSpinBox->setDecimals(2);
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

    connect(pSpinBox, QOverload<double>::of(&FixedSpinBox::valueChanged), this,
            &SlideControl::handleSpinBoxChanged);
    connect(pSlider, &QSlider::valueChanged, this, &SlideControl::handleSliderChanged);

    m_unmodified = false;
}

void SlideControl::onModifyAction() {
    if (m_unmodified) {
        setUnmodified(false);
    }
}

void SlideControl::handleSliderChanged(int n) {
    onModifyAction();
    pSpinBox->setValue(double(n) / pow(10, pSpinBox->decimals()));

    emit valueChanged(getValue());
}

void SlideControl::handleSpinBoxChanged(double n) {
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

void SlideControl::setSpacing(int n) {
    pLayout->setHorizontalSpacing(n);
}

void SlideControl::setUnmodified(bool value) {
    if (value) {
        pSpinBox->setProperty("status", "unmodified");
        style()->polish(pSpinBox);
    } else {
        pSpinBox->setProperty("status", "normal");
        style()->polish(pSpinBox);
    }

    m_unmodified = value;
}

bool SlideControl::unmodified() const {
    return m_unmodified;
}
