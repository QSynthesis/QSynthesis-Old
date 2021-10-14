#include "FixedLineEdit.h"

FixedLineEdit::FixedLineEdit(QWidget *parent) : QLineEdit(parent) {
    initText();
}

FixedLineEdit::FixedLineEdit(const QString &text,QWidget *parent) : QLineEdit(text, parent) {
    initText();
}

void FixedLineEdit::setText(QString text) {
    recentText = text;
    QLineEdit::setText(text);
    setCursorPosition(0);
}

void FixedLineEdit::focusOutEvent(QFocusEvent *event) {
    QLineEdit::focusOutEvent(event);
    emit loseFocus();
}

void FixedLineEdit::initText() {
    recentText = text();
    connect(this, &QLineEdit::editingFinished, this, &FixedLineEdit::onEditingFinished);
}

void FixedLineEdit::onEditingFinished() {
    if (hasFocus()) {
        clearFocus();
    }
    QString currentText = text();
    if (currentText == recentText) {
        return;
    }
    recentText = currentText;
    emit editingFinished2();
}
