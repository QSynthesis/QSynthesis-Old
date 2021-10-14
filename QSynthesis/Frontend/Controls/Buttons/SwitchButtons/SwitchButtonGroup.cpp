#include "SwitchButtonGroup.h"
#include "../SwitchButton.h"

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

SwitchButton *SwitchButtonGroup::buttonAt(int index) {
    if (index < 0 || index >= btns.size()) {
        return nullptr;
    }
    return btns.at(index);
}

void SwitchButtonGroup::updateSelected(bool checked) {
    SwitchButton *btn = qobject_cast<SwitchButton *>(sender());

    bool accepted = true;
    emit switchRequested(accepted);

    if (accepted) {
        setCurrentIndex(btns.indexOf(btn));
        emit switched();
    } else {
        setCurrentIndex(currentIndex());
    }
}

void SwitchButtonGroup::onOneDoubleClicked() {
    emit oneDoubleClicked();
}
