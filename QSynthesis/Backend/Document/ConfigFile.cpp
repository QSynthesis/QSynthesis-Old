#include "ConfigFile.h"

Q_SINGLETON_DECLARE(ConfigFile)

ConfigFile::ConfigFile() : BaseFile(Qs::Default) {
    reset();
}

ConfigFile::ConfigFile(const QString &filename) : BaseFile(Qs::Default) {
    setFilename(filename);
}

ConfigFile::~ConfigFile() {
}

bool ConfigFile::loadCore(bool *valid) {
    return false;
}

bool ConfigFile::saveCore() {
    return false;
}

void ConfigFile::resetCore() {
    zoomH = Qt::ControlModifier | Qt::ShiftModifier;
    zoomV = Qt::ControlModifier;
    moveH = Qt::ShiftModifier;
    zoomWaveH = Qt::ControlModifier;
    selectR = Qt::ControlModifier;
    selectC = Qt::ShiftModifier;
    sceneDrag = Qt::ControlModifier | Qt::ShiftModifier;
    stretchA = Qt::NoModifier;
    stretchR = Qt::ControlModifier;
    strecthP = Qt::ShiftModifier;
}
