#include "TuneOperation.h"

TuneOperation::TuneOperation() : m_type(Unknown) {
}

TuneOperation::~TuneOperation() {
}

TuneOperation::Type TuneOperation::type() const {
    return m_type;
}

TuneOperation *TuneOperation::next() const {
    return static_cast<TuneOperation *>(m_next);
}
