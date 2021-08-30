#include "NoteOperation.h"

NoteOperation::NoteOperation() : m_typeN(Unknown) {
    m_type = Note;
}

NoteOperation::~NoteOperation() {
}

QList<int> NoteOperation::index() const {
    return m_index;
}

void NoteOperation::setIndex(const QList<int> &index) {
    m_index = index;
}

NoteOperation::Type NoteOperation::type() const {
    return m_typeN;
}

NoteOperation *NoteOperation::next() const {
    return static_cast<NoteOperation *>(m_next);
}
