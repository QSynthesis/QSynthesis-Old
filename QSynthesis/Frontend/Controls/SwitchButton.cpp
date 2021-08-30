#include "SwitchButton.h"
#include "mainwindow.h"

SwitchButton::SwitchButton(QWidget *parent) : QPushButton(parent) {
    init();
}

SwitchButton::SwitchButton(QString text, QWidget *parent) : QPushButton(text, parent) {
    init();
}

int SwitchButton::textWidth() const {
    return QFontMetrics(font()).width(text());
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

void SwitchButton::mouseDoubleClickEvent(QMouseEvent *event) {
    emit doubleClicked();
}

SwitchButtonGroup::SwitchButtonGroup(QObject *parent) : QObject(parent) {
    m_current = nullptr;
}

void SwitchButtonGroup::addButton(SwitchButton *btn) {
    int index = btns.indexOf(btn);
    if (index >= 0) {
        return;
    }
    btns.append(btn);
    connect(btn, &SwitchButton::toggled, this, &SwitchButtonGroup::updateSelected);
    connect(btn, &SwitchButton::doubleClicked, this, &SwitchButtonGroup::onOneDoubleClicked);
}

void SwitchButtonGroup::removeButton(SwitchButton *btn) {
    int index = btns.indexOf(btn);
    if (index < 0) {
        return;
    }
    btns.removeAt(index);
    disconnect(btn, &SwitchButton::toggled, this, &SwitchButtonGroup::updateSelected);
    disconnect(btn, &SwitchButton::doubleClicked, this, &SwitchButtonGroup::onOneDoubleClicked);
}

int SwitchButtonGroup::currentIndex() {
    return btns.indexOf(m_current);
}

void SwitchButtonGroup::setCurrentIndex(int index) {
    if (index < 0 || index >= btns.size()) {
        return;
    }

    for (int i = 0; i < btns.size(); ++i) {
        btns.at(i)->blockSignals(true);
        btns.at(i)->setChecked(false);
        btns.at(i)->blockSignals(false);
    }

    SwitchButton *btn = btns.at(index);
    m_current = btn;

    btn->blockSignals(true);
    btn->setChecked(true);
    btn->blockSignals(false);
}

SwitchButton *SwitchButtonGroup::currentButton() {
    return m_current;
}

void SwitchButtonGroup::updateSelected(bool checked) {
    SwitchButton *btn = qobject_cast<SwitchButton *>(sender());
    setCurrentIndex(btns.indexOf(btn));
    emit switched();
}

void SwitchButtonGroup::onOneDoubleClicked() {
    emit oneDoubleClicked();
}
