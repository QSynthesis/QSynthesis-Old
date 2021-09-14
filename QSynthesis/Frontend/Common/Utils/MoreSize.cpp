#include "MoreSize.h"

MoreSize::MoreSize() {
}

MoreSize::MoreSize(const QSize &sz) : QSizeF(sz) {
}

MoreSize::MoreSize(const QSizeF &sz) : QSizeF(sz) {
}

MoreSize::MoreSize(double w, double h) : QSizeF(w, h) {
}

MoreSize::MoreSize(double w, double h, int l) : QSizeF(w, h), m_length(l) {
}

MoreSize::~MoreSize() {
}

int MoreSize::length() const {
    return m_length;
}

void MoreSize::setLength(int length) {
    m_length = length;
}
