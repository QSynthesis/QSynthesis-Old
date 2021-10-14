#include "MoveOperation.h"

MoveOperation::MoveOperation() {
    m_typeN = Move;
}

MoveOperation::~MoveOperation() {
}

int MoveOperation::movement() const {
    return m_movement;
}

void MoveOperation::setMovement(int movement) {
    m_movement = movement;
}

QList<int> MoveOperation::verticals() const {
    return m_verticals;
}

void MoveOperation::setVerticals(const QList<int> &verticals) {
    m_verticals = verticals;
}

int MoveOperation::index() const {
    return m_index;
}

void MoveOperation::setIndex(int index) {
    m_index = index;
}

bool MoveOperation::differ() const {
    if (m_movement != 0) {
        return true;
    }

    bool flag = false;
    for (int i = 0; i < m_verticals.size(); ++i) {
        if (m_verticals.at(i) != 0) {
            flag = true;
            break;
        }
    }
    return flag;
}
