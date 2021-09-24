#include "AppAssistant.h"

Q_SINGLETON_DECLARE(AppAssistant)

QList<QTranslator *> AppAssistant::Translators{};

AppAssistant::AppAssistant(QObject *parent) : QObject(parent) {
}

AppAssistant::~AppAssistant() {
}

bool AppAssistant::keyIsDown(QEvent *event) {
    QList<QEvent::Type> types{QEvent::KeyPress, QEvent::ShortcutOverride};
    return types.contains(event->type());
}

bool AppAssistant::isUnusableKey(Qt::Key key) {
    QList<Qt::Key> keys{Qt::Key_CapsLock, Qt::Key_NumLock, Qt::Key_ScrollLock, Qt::Key_Meta};
    return keys.contains(key);
}

bool AppAssistant::isSpecialKey(Qt::Key key) {
    QList<Qt::Key> keys{Qt::Key_Tab, Qt::Key_Escape, Qt::Key_Return, Qt::Key_Enter};
    return keys.contains(key);
}

bool AppAssistant::isModifierKey(Qt::Key key) {
    QList<Qt::Key> keys{Qt::Key_Control, Qt::Key_Shift, Qt::Key_Alt};
    return keys.contains(key);
}

bool AppAssistant::isSpecialShortcut(QKeySequence shortcut) {
    QList<QKeySequence> shortcuts{QKeySequence("Tab")};
    return shortcuts.contains(shortcut);
}

bool AppAssistant::translate(const QString &filename) {
    QTranslator *t = new QTranslator(self);
    if (t->load(filename)) {
        qApp->installTranslator(t);
        Translators.append(t);
        return true;
    }
    delete t;
    return false;
}

void AppAssistant::eliminate() {
    for (QTranslator *t : Translators) {
        qApp->removeTranslator(t);
        delete t;
    }
    Translators.clear();
}
