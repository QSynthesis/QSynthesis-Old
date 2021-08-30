#include "TuneOperation.h"

TuneOperation::TuneOperation() : m_type(Unknown), m_next(nullptr) {
}

TuneOperation::~TuneOperation() {
}

TuneOperation::Type TuneOperation::type() const {
    return m_type;
}

TuneOperation *TuneOperation::next() const {
    return m_next;
}

void TuneOperation::setNext(TuneOperation *next) {
    m_next = next;
}
