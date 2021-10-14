#include "NonOtoOperation.h"

NonOtoOperation::NonOtoOperation() : m_typeN(Unknown) {
    m_type = NonOto;
}

NonOtoOperation::~NonOtoOperation() {
}

NonOtoOperation::Type NonOtoOperation::type() const {
    return m_typeN;
}
