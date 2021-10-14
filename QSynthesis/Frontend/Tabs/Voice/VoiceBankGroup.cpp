#include "VoiceBankGroup.h"

VoiceBankGroup::VoiceBankGroup(VoiceBankTab *parent) : LayerGroup(parent), tab(parent) {
    tab = parent;
}

QDebug operator<<(QDebug debug, const VoiceBankGroup &vg) {
    debug.nospace() << "VoiceBankGroup"
                    << " "
                    << "Tab(" << vg.tab << ")"
                    << "\n";
    return debug;
}
