#include "Operation.h"

Operation::Operation() {
    m_desc = "";
    m_next = nullptr;
}

Operation::~Operation() {
    if (m_next) {
        delete m_next;
        m_next = nullptr;
    }
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

Operation *Operation::simplify(Operation *o) {
    QList<Operation *> list;
    // Save
    for (auto it = o; it; it = it->next()) {
        list.append(it);
    }
    // Remove Link
    for (auto it = list.begin(); it != list.end(); ++it) {
        (*it)->setNext(nullptr);
    }
    // Remove No Use
    for (auto it = list.begin(); it != list.end(); ++it) {
        Operation *&cur = *it;
        if (!cur->differ()) {
            delete cur;
            cur = nullptr;
        }
    }
    // Relink
    Operation *res = nullptr;
    for (auto it = list.begin(); it != list.end(); ++it) {
        Operation *&cur = *it;
        if (cur) {
            if (res) {
                res->setTail(cur);
            } else {
                res = cur;
            }
        }
    }
    return res;
}

Operation *Operation::next() const {
    return m_next;
}

void Operation::setNext(Operation *next) {
    m_next = next;
}

void Operation::setTail(Operation *next) {
    if (m_next) {
        m_next->setTail(next);
    } else {
        setNext(next);
    }
}
