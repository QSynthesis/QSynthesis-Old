#include "QVocaloidFile.h"

QVocaloidFile::QVocaloidFile(QVocaloidFile::Format format) : m_format(format) {
}

QVocaloidFile::QVocaloidFile() : m_format(VSQX) {
}

QVocaloidFile::Format QVocaloidFile::format() const {
    return m_format;
}

void QVocaloidFile::setFormat(const Format &format) {
    m_format = format;
}
