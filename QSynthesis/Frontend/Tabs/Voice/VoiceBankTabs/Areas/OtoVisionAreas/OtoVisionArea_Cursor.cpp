#include "../OtoVisionArea.h"

void OtoVisionArea::setOffsetByCursor() {
    if (vision->containsCursor()) {
        vision->setFocus();
        vision->setOffsetByCursor();
    }
}

void OtoVisionArea::setConstantByCursor() {
    if (vision->containsCursor()) {
        vision->setFocus();
        vision->setConstantByCursor();
    }
}

void OtoVisionArea::setBlankByCursor() {
    if (vision->containsCursor()) {
        vision->setFocus();
        vision->setBlankByCursor();
    }
}

void OtoVisionArea::setPreUttrByCursor() {
    if (vision->containsCursor()) {
        vision->setFocus();
        vision->setPreUttrByCursor();
    }
}

void OtoVisionArea::setOverlapByCursor() {
    if (vision->containsCursor()) {
        vision->setFocus();
        vision->setOverlapByCursor();
    }
}
