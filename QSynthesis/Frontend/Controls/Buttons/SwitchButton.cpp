#include "SwitchButton.h"

SwitchButton::SwitchButton(QWidget *parent) : QPushButton(parent) {
    init();
}

SwitchButton::SwitchButton(QString text,QWidget *parent) : QPushButton(text, parent) {
    init();
}

int SwitchButton::textWidth() const {
    return QFontMetrics(font()).horizontalAdvance(text());
}

int SwitchButton::textHeight() const {
    return QFontMetrics(font()).height();
}

void SwitchButton::setRecommendedSize(double w, double h) {
    setFixedSize(w * textWidth(), h * textHeight());
}

void SwitchButton::init() {
    setCheckable(true);
    adjustSize();
}
