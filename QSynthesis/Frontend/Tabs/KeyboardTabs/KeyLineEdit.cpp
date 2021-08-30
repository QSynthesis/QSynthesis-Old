#include "KeyLineEdit.h"

KeyLineEdit::KeyLineEdit(QWidget *parent) : FixedLineEdit(parent) {
    m_key = Qt::Key_unknown;
    setAlignment(Qt::AlignCenter);
}

void KeyLineEdit::setKey(int key) {
    Qt::Key qkey = static_cast<Qt::Key>(key);
    if (qkey != Qt::Key_unknown) {
        m_key = qkey;
        setText(QKeySequence(qkey).toString());
    } else {
        m_key = Qt::Key_unknown;
        setText("");
    }
}

int KeyLineEdit::key() const {
    return m_key;
}

void KeyLineEdit::setText(QString qsText) {
    QLineEdit::setText(qsText);
}

void KeyLineEdit::keyPressEvent(QKeyEvent *e) {
    int uKey = e->key();
    Qt::Key key = static_cast<Qt::Key>(uKey);
    if (key == Qt::Key_unknown) {
        return;
    }
    //除去单个的特殊按键
    if (key == Qt::Key_Enter || key == Qt::Key_Return) {
        emit enterModify();
        return;
    }
    if (key == Qt::Key_Escape) {
        emit abandon();
        return;
    }
    if (key == Qt::Key_Control || key == Qt::Key_Shift || key == Qt::Key_Alt ||
        key == Qt::Key_Tab || key == Qt::Key_CapsLock) {
        return;
    }
    if (key == Qt::Key_Backspace) {
        emit keyChange(Qt::Key_unknown);
        m_key = Qt::Key_unknown;
        setText("");
        return;
    }

    Qt::KeyboardModifiers modifiers = e->modifiers();
    if (modifiers & Qt::ShiftModifier) {
        uKey += Qt::SHIFT;
    }
    if (modifiers & Qt::ControlModifier) {
        uKey += Qt::CTRL;
    }
    if (modifiers & Qt::AltModifier) {
        uKey += Qt::ALT;
    }
    if (modifiers & Qt::MetaModifier) {
        uKey += Qt::META;
    }

    setText(QKeySequence(uKey).toString());
    m_key = key;
    emit keyChange(uKey);
}
