#include "SequenceOperation.h"

SequenceOperation::SequenceOperation(bool increase) {
    m_typeN = increase ? Add : Remove;
    m_ignore = Qs::IgnoreNone;
}

SequenceOperation::~SequenceOperation() {
}

QList<QLinkNote> SequenceOperation::notes() const {
    return m_notes;
}

void SequenceOperation::setNotes(const QList<QLinkNote> &notes) {
    m_notes = notes;
}

bool SequenceOperation::differ() const {
    return !m_notes.isEmpty();
}

Qs::IgnoreSelection SequenceOperation::ignore() const {
    return m_ignore;
}

void SequenceOperation::setIgnore(const Qs::IgnoreSelection &ignore) {
    m_ignore = ignore;
}
