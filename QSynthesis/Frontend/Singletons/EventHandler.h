#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QKeyEvent>

class EventHandler {
public:
    EventHandler();

    static bool keyIsDown(QEvent *event);
};

#endif // EVENTHANDLER_H
