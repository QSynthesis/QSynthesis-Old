#include "SlideLineControl.h"

#include <QStyle>
#include <cmath>

/*--------------------------------------滑块文本控制--------------------------------------*/
SlideLineControl::SlideLineControl(QWidget *parent) : QWidget(parent) {
    InitSlideControl("", 0);
}

SlideLineControl::SlideLineControl(QString text, QWidget *parent) : QWidget(parent) {

    InitSlideControl(text, 0);
}

SlideLineControl::SlideLineControl(QString text, double value, QWidget *parent) : QWidget(parent) {

    InitSlideControl(text, value);
}

void SlideLineControl::setCaption(QString caption) {
    pLabel->setText(caption);
    pLabel->adjustSize();
}

QString SlideLineControl::caption() const {
    return pLabel->text();
}

void SlideLineControl::setBlankValue(double value) {
    blankValue = value;
}

void SlideLineControl::setMaximum(double value) {
    maximum = value;
    pValidator->setTop(maximum);
    pSlider->setMaximum(maximum * pow(10, pValidator->decimals()));
}
void SlideLineControl::setMinimum(double value) {
    minimum = value;
    pValidator->setBottom(minimum);
    pSlider->setMinimum(minimum * pow(10, pValidator->decimals()));
}
void SlideLineControl::setSingleStep(double value) {
    singleStep = value;
    pValidator->setDecimals(-log10(value));
}
void SlideLineControl::setValue(double value) {
    this->value = value;
    pText->setText(QString::number(value));
    pSlider->setValue(value * pow(10, pValidator->decimals()));
}

double SlideLineControl::getValue() {
    return pSlider->value() / pow(10, pValidator->decimals());
}

void SlideLineControl::setText(QString value) {
    pText->setText(value);
}

QString SlideLineControl::getText() const {
    return pText->text();
}

FixedLineEdit *SlideLineControl::Text() const {
    return pText;
}

QSlider *SlideLineControl::Slider() const {
    return pSlider;
}

void SlideLineControl::InitSlideControl(QString text, double value) {

    isSliderMoving = isTextEditing = false;

    // 标签
    pLabel = new QLabel(text, this);
    pLabel->adjustSize();

    // 微调框
    pText = new FixedLineEdit(this);
    pText->setProperty("status", "normal");

    pValidator = new QDoubleValidator();

    pValidator->setDecimals(2);
    pValidator->setNotation(QDoubleValidator::StandardNotation);

    pText->setValidator(pValidator);

    pText->adjustSize();

    // 滑动条
    pSlider = new QSlider(this);
    pSlider->setOrientation(Qt::Horizontal); // 水平方向
    pSlider->adjustSize();

    setMinimum(0);    // 最小值
    setMaximum(100);  // 最大值
    setSingleStep(1); // 步长
    setValue(value);
    setBlankValue(0);

    pSlider->setFixedHeight(18);

    pLayout = new QGridLayout(this);
    pLayout->setMargin(0);

    pLayout->addWidget(pLabel, 0, 0);
    pLayout->addWidget(pText, 0, 1);
    pLayout->addWidget(pSlider, 1, 0, 1, 2);

    setLayout(pLayout);

    connect(pText, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(pSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderChanged(int)));

    pText->setPlaceholderText(placeholderModified);
    m_unmodified = false;
}

void SlideLineControl::onModifyAction() {
    if (m_unmodified) {
        bool status = pText->isClearButtonEnabled();
        pText->setClearButtonEnabled(false);
        pText->clear();
        pText->setClearButtonEnabled(status);

        setUnmodified(false);
    }
}

void SlideLineControl::setPlaceholder(QString modi, QString unmo) {
    placeholderModified = modi;
    placeholderUnmodified = unmo;

    if (m_unmodified) {
        pText->setPlaceholderText(unmo);
    } else {
        pText->setPlaceholderText(modi);
    }
}

void SlideLineControl::onSliderChanged(int n) {
    onModifyAction();

    if (isTextEditing) {
        return;
    }
    isSliderMoving = true;
    pText->setText(QString::number(double(n) / pow(10, pValidator->decimals())));
    isSliderMoving = false;
}

void SlideLineControl::onTextChanged(QString s) {
    onModifyAction();

    if (isSliderMoving) {
        return;
    }
    double n = (s.isEmpty() || !isNumber(s, true, true)) ? blankValue : s.toDouble();

    if (n > maximum) {
        n = maximum;
        s = QString::number(n);
        pText->setText(s);
    }

    isTextEditing = true;
    pSlider->setValue(n * pow(10, pValidator->decimals()));
    isTextEditing = false;
}

void SlideLineControl::setProportion(int a, int b) {
    pLayout->setColumnStretch(0, a);
    pLayout->setColumnStretch(1, b);
}

void SlideLineControl::setMargin(int n) {
    pLayout->setMargin(n);
}

void SlideLineControl::setUnmodified(bool value) {
    if (value) {
        pText->setProperty("status", "unmodified");
        style()->polish(pText);
        pText->setPlaceholderText(placeholderUnmodified);
    } else {
        pText->setProperty("status", "normal");
        style()->polish(pText);
        pText->setPlaceholderText(placeholderModified);
    }

    m_unmodified = value;
}

bool SlideLineControl::unmodified() const {
    return m_unmodified;
}
