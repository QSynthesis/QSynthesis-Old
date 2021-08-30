#include "OtoChangeOperation.h"

OtoChangeOperation::OtoChangeOperation() {
    m_typeO = Change;
}

QGenonSettings OtoChangeOperation::origin() const {
    return m_origin;
}

void OtoChangeOperation::setOrigin(const QGenonSettings &origin) {
    m_origin = origin;
}

QGenonSettings OtoChangeOperation::modified() const {
    return m_modified;
}

void OtoChangeOperation::setModified(const QGenonSettings &modified) {
    m_modified = modified;
}

bool OtoChangeOperation::differ() const {
    return m_origin != m_modified;
}
