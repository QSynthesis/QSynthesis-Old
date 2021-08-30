#include "OtoOperation.h"

OtoOperation::OtoOperation() : m_typeO(Unknown) {
    m_type = Oto;
}

OtoOperation::~OtoOperation() {
}

int OtoOperation::index() const {
    return m_index;
}

void OtoOperation::setIndex(int index) {
    m_index = index;
}

QString OtoOperation::dirname() const {
    return m_dirname;
}

void OtoOperation::setDirname(const QString &dirname) {
    m_dirname = dirname;
}

OtoOperation::Type OtoOperation::type() const {
    return m_typeO;
}
