#include "EventHandler.h"

EventHandler::EventHandler() {
}

bool EventHandler::keyIsDown(QEvent *event) {
    QList<QEvent::Type> types{QEvent::KeyPress, QEvent::ShortcutOverride};
    return types.contains(event->type());
}
