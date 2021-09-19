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
