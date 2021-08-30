#include "OtoVariateOperation.h"

OtoVariateOperation::OtoVariateOperation(bool increase) {
    m_typeO = increase ? Add : Remove;
}

QGenonSettings OtoVariateOperation::sample() const {
    return m_sample;
}

void OtoVariateOperation::setSample(const QGenonSettings &sample) {
    m_sample = sample;
}

bool OtoVariateOperation::differ() const {
    return true;
}
