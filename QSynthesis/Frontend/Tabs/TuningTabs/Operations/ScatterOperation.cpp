#include "ScatterOperation.h"

ScatterOperation::ScatterOperation(bool mode1) {
    m_typeN = mode1 ? Mode1 : Vibrato;
}

ScatterOperation::~ScatterOperation() {
}
