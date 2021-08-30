#include "ConfigData.h"

ConfigData::ConfigData() {
    notes = Modifiers();
    wave = Modifiers();
    wave.zoomHorizontally = Qt::ControlModifier;
}

ConfigData::Modifiers::Modifiers() {
    zoomHorizontally = (Qt::ShiftModifier | Qt::ControlModifier);
    zoomVertically = Qt::ControlModifier;
    moveHorizontally = Qt::ShiftModifier;
    moveVertically = Qt::NoModifier;

    reserveSelect = Qt::ControlModifier;
    continuousSelect = Qt::ShiftModifier;

    sceneReserveSelect = Qt::ControlModifier;
    sceneDragging = (Qt::ShiftModifier | Qt::ControlModifier);

    relativeStretch = Qt::ControlModifier;
}
