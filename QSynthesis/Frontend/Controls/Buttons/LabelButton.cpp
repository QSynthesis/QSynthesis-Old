#include "LabelButton.h"

LabelButton::LabelButton(QWidget *parent) : QPushButton(parent) {
}

LabelButton::LabelButton(const QString &text,QWidget *parent) : QPushButton(text, parent) {
}

LabelButton::LabelButton(const QIcon &icon, const QString &text,QWidget *parent)
    : QPushButton(icon, text, parent) {
}

LabelButton::~LabelButton() {
}
