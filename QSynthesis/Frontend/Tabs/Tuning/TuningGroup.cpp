#include "TuningGroup.h"

TuningGroup::TuningGroup(TuningTab *parent) : QObject(parent), tab(parent) {
    currentWidth = 60;
    currentHeight = 32;
    currentAdsorb = 1;
    currentSections = 40;
}

QDebug operator<<(QDebug debug, const TuningGroup &tg) {
    debug.nospace() << "TuningGroup"
                    << " "
                    << "Tab(" << tg.tab << ")";
    return debug;
}
