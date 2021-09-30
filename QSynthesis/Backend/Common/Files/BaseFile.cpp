#include "BaseFile.h"
#include "QUtils.h"

BaseFile::BaseFile() {
}

BaseFile::~BaseFile() {
}

BaseFile::BaseFile(Qs::VariableSource source) {
    Q_ASSERT(source == Qs::Default);
}

bool BaseFile::load(bool *valid) {
    resetCore();
    return loadCore(valid);
}

bool BaseFile::save() {
    return saveCore();
}

bool BaseFile::remove() {
    QFile file(m_filename);
    if (file.exists()) {
        return file.remove();
    } else {
        return true;
    }
}

void BaseFile::clear() {
    resetCore();
}

void BaseFile::reset() {
    m_filename.clear();
    resetCore();
}

bool BaseFile::exists() const {
    return isFileExist(m_filename);
}

QString BaseFile::filename() const {
    return m_filename;
}

void BaseFile::setFilename(const QString &filename) {
    reset();
    m_filename = filename;
    prepareCore();
}
bool BaseFile::loadCore(bool *valid) {
    Q_UNUSED(valid)
    return false;
}

bool BaseFile::saveCore() {
    return false;
}

void BaseFile::resetCore() {
}

void BaseFile::prepareCore() {
}
