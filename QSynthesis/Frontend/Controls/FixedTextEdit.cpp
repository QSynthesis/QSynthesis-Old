#include "FixedTextEdit.h"
#include "Managers/DataManager.h"

#include <QApplication>
#include <QEvent>
#include <QKeyEvent>

FixedTextEdit::FixedTextEdit(QWidget *parent) : QPlainTextEdit(parent) {
    initText();
}

FixedTextEdit::FixedTextEdit(const QString &text, QWidget *parent) : QPlainTextEdit(text, parent) {
    initText();
}

void FixedTextEdit::initText() {
    installEventFilter(this);

    recentText = text();
}
void FixedTextEdit::setText(const QString &text) {
    recentText = text;
    setPlainText(text);
}

QString FixedTextEdit::text() const {
    return toPlainText();
}

bool FixedTextEdit::eventFilter(QObject *obj, QEvent *event) {
    if (obj == this) {
        if (DataManager::keyIsDown(event)) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            int key = keyEvent->key();
            if ((key == Qt::Key_Return || key == Qt::Key_Enter) &&
                QApplication::keyboardModifiers() == Qt::ControlModifier) {
                onEditingFinished();
                return true;
            }
        }
    }
    return QPlainTextEdit::eventFilter(obj, event);
}

void FixedTextEdit::focusOutEvent(QFocusEvent *event) {
    QPlainTextEdit::focusOutEvent(event);
    emit loseFocus();
    onEditingFinished();
}

void FixedTextEdit::onEditingFinished() {
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
