#include "SequenceOperation.h"

SequenceOperation::SequenceOperation(bool increase) {
    m_typeN = increase ? Add : Remove;
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
