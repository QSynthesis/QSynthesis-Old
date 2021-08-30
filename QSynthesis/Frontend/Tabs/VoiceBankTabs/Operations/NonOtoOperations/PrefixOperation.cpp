#include "PrefixOperation.h"

PrefixOperation::PrefixOperation() {
    m_typeN = PrefixMap;
}

PrefixOperation::PrefixOperation(Qs::PrefixMap prefixType) {
    m_typeN = PrefixMap;
    m_prefixType = prefixType;
}

int PrefixOperation::noteNum() const {
    return m_noteNum;
}

void PrefixOperation::setNoteNum(int noteNum) {
    m_noteNum = noteNum;
}

QString PrefixOperation::modified() const {
    return m_modified;
}

void PrefixOperation::setModified(const QString &modified) {
    m_modified = modified;
}

Qs::PrefixMap PrefixOperation::prefixType() const {
    return m_prefixType;
}

void PrefixOperation::setPrefixType(Qs::PrefixMap prefixType) {
    m_prefixType = prefixType;
}

bool PrefixOperation::differ() const {
    return m_origin != m_modified;
}

QString PrefixOperation::origin() const {
    return m_origin;
}

void PrefixOperation::setOrigin(const QString &origin) {
    m_origin = origin;
}
