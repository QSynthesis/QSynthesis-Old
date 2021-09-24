#include "KeyModifyDialog.h"
#include "AppAssistant.h"

#include <QKeyEvent>

KeyModifyDialog::KeyModifyDialog(QWidget *parent) : QDialog(parent) {
    setWindowFlags(Qt::Popup); // Auto exit

    setFixedSize(500, 120);
    mainLayout = new QVBoxLayout();
    hintLable = new QLabel(tr("Press desired key combination and then press ENTER."));

    lineEdit = new FixedLineEdit();
    lineEdit->setAlignment(Qt::AlignCenter);
    lineEdit->setEnabled(false);

    QPoint globalPos = parent->mapToGlobal(QPoint(0, 0));
    int x = globalPos.x() + (parent->width() - width()) / 2;
    int y = globalPos.y() + (parent->height() - height()) / 2;
    move(x, y);

    mainLayout->addWidget(hintLable);
    mainLayout->addWidget(lineEdit);
    setLayout(mainLayout);

    m_tempKey = Qt::Key_unknown;
    m_keyBind = 0;
    m_modifiers = 0;

    installEventFilter(this);
}

KeyModifyDialog::~KeyModifyDialog() {
}

QString KeyModifyDialog::text() const {
    return lineEdit->text();
}

int KeyModifyDialog::key() const {
    return m_keyBind;
}

int KeyModifyDialog::modifiers() const {
    return m_modifiers;
}

void KeyModifyDialog::setText(const QString &text) {
    lineEdit->setText(text);
}

bool KeyModifyDialog::keyDownEvent(QKeyEvent *event) {
    bool normalRes = false;
    Qt::Key key = (Qt::Key) event->key();
    Qt::KeyboardModifiers modifiers = event->modifiers();

    modifiers &= ~Qt::MetaModifier;

    // Function keys
    if (modifiers == 0 || modifiers == Qt::KeypadModifier) {
        if (key == Qt::Key_Enter || key == Qt::Key_Return) {
            accept();
            return normalRes;
        }
        if (key == Qt::Key_Escape) {
            reject();
            return normalRes;
        }
        if (key == Qt::Key_Backspace) {
            m_tempKey = Qt::Key_unknown;
            setText("");
            return normalRes;
        }
    }

    // Exclude special keys
    if (AppAssistant::isUnusableKey(key) || key == Qt::Key_unknown) {
        return normalRes;
    }

    QKeySequence shortcut;
    int keyBind = 0;

    // Set current key
    if (!AppAssistant::isModifierKey(key)) {
        keyBind = key;
    }
    // No current key but has last key
    if (keyBind == 0 && m_tempKey != Qt::Key_unknown) {
        keyBind = m_tempKey;
    }
    // Save current key
    if (keyBind != 0) {
        m_tempKey = (Qt::Key) keyBind;
    }

    m_keyBind = keyBind;
    m_modifiers = modifiers;

    setText(QKeySequence(keyBind + modifiers).toString(QKeySequence::NativeText));
    return normalRes;
}

bool KeyModifyDialog::eventFilter(QObject *obj, QEvent *event) {
    if (obj == this) {
        if (event->type() == QEvent::ShortcutOverride) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (!keyEvent->isAutoRepeat()) {
                if (keyDownEvent(keyEvent)) {
                    return true;
                }
            }
        } else if (event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (!keyEvent->isAutoRepeat()) {
                if (keyEvent->key() == m_tempKey) {
                    m_tempKey = Qt::Key_unknown;
                }
            }
        }
    }
    return QDialog::eventFilter(obj, event);
}
