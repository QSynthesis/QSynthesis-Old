#include "Operation.h"

Operation::Operation() {
    m_desc = "";
}

Operation::~Operation() {
}

QString Operation::desc() const {
    return m_desc;
}

void Operation::setDesc(const QString &desc) {
    m_desc = desc;
}

bool Operation::differ() const {
    return false;
}
