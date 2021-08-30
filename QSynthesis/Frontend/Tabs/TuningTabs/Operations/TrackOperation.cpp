#include "TrackOperation.h"

TrackOperation::TrackOperation() : m_typeT(Unknown) {
    m_type = Track;
}

TrackOperation::~TrackOperation() {
}

TrackOperation::Type TrackOperation::type() const {
    return m_typeT;
}

void TrackOperation::setType(const Type &type) {
    m_typeT = type;
}

int TrackOperation::index() const
{
    return m_index;
}

void TrackOperation::setIndex(int index)
{
    m_index = index;
}
