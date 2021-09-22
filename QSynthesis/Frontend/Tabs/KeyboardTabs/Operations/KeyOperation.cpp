#include "KeyOperation.h"

KeyOperation::KeyOperation() {
    m_next = nullptr;
}

KeyOperation::~KeyOperation() {
    if (m_next) {
        delete m_next;
        m_next = nullptr;
    }
}

QPair<int, int> KeyOperation::index() const {
    return m_index;
}

void KeyOperation::setIndex(const QPair<int, int> &index) {
    m_index = index;
}

QString KeyOperation::origin() const {
    return m_origin;
}

void KeyOperation::setOrigin(const QString &origin) {
    m_origin = origin;
}

QString KeyOperation::modified() const {
    return m_modified;
}

void KeyOperation::setModified(const QString &modified) {
    m_modified = modified;
}

KeyOperation *KeyOperation::next() const {
    return static_cast<KeyOperation *>(m_next);
}

bool KeyOperation::differ() const {
    return QKeySequence(m_modified) != QKeySequence(m_origin);
}
