#include "TempoOperation.h"

TempoOperation::TempoOperation() {
    init();
}

double TempoOperation::origin() const {
    return m_origin;
}

void TempoOperation::setOrigin(double origin) {
    m_origin = origin;
}

double TempoOperation::modified() const {
    return m_modified;
}

void TempoOperation::setModified(double modified) {
    m_modified = modified;
}

bool TempoOperation::orgStatus() const {
    return m_orgStatus;
}

void TempoOperation::setOrgStatus(bool orgStatus) {
    m_orgStatus = orgStatus;
}

bool TempoOperation::newStatus() const {
    return m_newStatus;
}

void TempoOperation::setNewStatus(bool newStatus) {
    m_newStatus = newStatus;
}

bool TempoOperation::differ() const {
    if (m_orgStatus == m_newStatus) {
        if (!m_orgStatus) {
            return false;
        } else if (m_origin == m_modified) {
            return false;
        }
    }
    return true;
}

int TempoOperation::index() const {
    return m_index;
}

void TempoOperation::setIndex(int index) {
    m_index = index;
}

void TempoOperation::init() {
    m_typeN = Tempo;
    m_origin = m_modified = 0;
}
