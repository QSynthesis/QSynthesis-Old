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
