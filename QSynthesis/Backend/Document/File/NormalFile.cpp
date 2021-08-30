#include "NormalFile.h"

#include <QDebug>

NormalFile::NormalFile(QObject *parent) : FileManager(parent) {
    reset();
}

NormalFile::NormalFile(const QString &filename, QObject *parent) : FileManager(parent) {
    setFilename(filename);
}

NormalFile::~NormalFile() {
}

bool NormalFile::loadCore(bool *valid) {
    QFile aInFile(m_filename);
    if (!aInFile.open(QFile::ReadOnly | QIODevice::Text)) {
        return 0;
    }
    m_data = aInFile.readAll();
    if (valid) {
        *valid = true;
    }
    aInFile.close();
    return true;
}

bool NormalFile::saveCore() {
    QFile aOutFile(m_filename);
    if (!aOutFile.open(QFile::WriteOnly | QIODevice::Text)) {
        return 0;
    }
    aOutFile.write(m_data);
    aOutFile.close();
    return true;
}

void NormalFile::resetCore() {
    m_data.clear();
}

QByteArray NormalFile::data() const {
    return m_data;
}

void NormalFile::setData(const QByteArray &data) {
    m_data = data;
}
