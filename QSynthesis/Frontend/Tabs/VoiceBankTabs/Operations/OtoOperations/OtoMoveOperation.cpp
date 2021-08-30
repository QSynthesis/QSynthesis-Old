#include "OtoMoveOperation.h"

OtoMoveOperation::OtoMoveOperation() {
    m_typeO = Move;
}

int OtoMoveOperation::movement() const {
    return m_movement;
}

void OtoMoveOperation::setMovement(int movement) {
    m_movement = movement;
}

QGenonSettings OtoMoveOperation::sample() const {
    return m_sample;
}

void OtoMoveOperation::setSample(const QGenonSettings &sample) {
    m_sample = sample;
}

bool OtoMoveOperation::differ() const {
    return m_movement != 0;
}
