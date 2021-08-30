#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include "QUtils.h"

#include <QApplication>
#include <QKeySequence>

class ConfigData {
public:
    struct Modifiers {
        Qt::KeyboardModifiers zoomHorizontally;
        Qt::KeyboardModifiers zoomVertically;
        Qt::KeyboardModifiers moveHorizontally;
        Qt::KeyboardModifiers moveVertically;

        Qt::KeyboardModifiers reserveSelect;
        Qt::KeyboardModifiers continuousSelect;

        Qt::KeyboardModifiers sceneReserveSelect;
        Qt::KeyboardModifiers sceneDragging;

        Qt::KeyboardModifiers relativeStretch;

        Modifiers();
    };

    explicit ConfigData();

    Modifiers notes;
    Modifiers wave;
};

#endif // CONFIGDATA_H
