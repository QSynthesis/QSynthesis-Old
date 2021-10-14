#include "PointsOperation.h"

PointsOperation::PointsOperation(bool mode2) {
    m_typeN = mode2 ? Mode2 : Envelope;
}

PointsOperation::~PointsOperation() {
}
