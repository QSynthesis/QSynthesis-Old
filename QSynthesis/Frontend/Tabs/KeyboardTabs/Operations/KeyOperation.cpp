#include "KeyOperation.h"

KeyOperation::KeyOperation() {
}

int KeyOperation::id() const {
    return m_id;
}

void KeyOperation::setId(int id) {
    m_id = id;
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

bool KeyOperation::differ() const {
    return QKeySequence(m_modified) != QKeySequence(m_origin);
}
