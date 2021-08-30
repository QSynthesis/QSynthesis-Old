#include "PluginTempData.h"

PluginTempData::PluginTempData() {
    project = NODEF_STRING;
    hasPrev = hasNext = false;
    start = 0;
}

int PluginTempData::normalSize() const {
    return notes.size() + hasPrev + hasNext;
}

int PluginTempData::normalBegin() const {
    if (hasPrev) {
        return 1;
    } else {
        return 0;
    }
}

int PluginTempData::normalEnd() const {
    if (hasNext) {
        return notes.size() - 1;
    } else {
        return notes.size();
    }
}

QDebug operator<<(QDebug debug, const PluginTempData &ns) {
    debug.nospace() << QString("NotesSequence(Start=%1, End=%2, Prev=%3, Next=%4)")
                           .arg(ns.start)
                           .arg(ns.start + ns.normalEnd() - ns.normalBegin())
                           .arg(ns.hasPrev)
                           .arg(ns.hasNext);
    return debug;
}
