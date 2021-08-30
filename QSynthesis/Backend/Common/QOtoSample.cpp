#include "QOtoSample.h"
#include "QUtils.h"

QOtoSample::QOtoSample() {
    clear();
}

QOtoSample::QOtoSample(const QString &filename) {
    setFilename(filename);
}

QString QOtoSample::filename() const {
    return m_filename;
}

void QOtoSample::setFilename(const QString &filename) {
    clear();
    m_filename = filename;
}

void QOtoSample::setData(QList<QGenonSettings> &&sample) {
    swap(sample);
}

void QOtoSample::setData(const QList<QGenonSettings> &sample) {
    clear();
    for (int i = 0; i < sample.size(); ++i) {
        append(sample.at(i));
    }
}

const QList<QGenonSettings> &QOtoSample::data() const {
    return *this;
}

void QOtoSample::clearAll() {
    clear();
    m_filename = "";
}

bool QOtoSample::valid() const {
    return isFileExist(m_filename);
}

bool QOtoSample::frqExist() const {
    QFileInfo info(m_filename);
    QString frqName = info.absolutePath() + Slash + info.baseName() + "_wav.frq";
    return isFileExist(frqName);
}

bool QOtoSample::mrqExist() const {
    return false;
}

bool QOtoSample::operator==(const QOtoSample &sample) const {
    return m_filename == sample.m_filename;
}

bool QOtoSample::operator!=(const QOtoSample &sample) const {
    return !((*this) == sample);
}

bool QOtoSample::operator<(const QOtoSample &sample) const {
    return m_filename.toLower() < sample.m_filename.toLower();
}

uint qHash(const QOtoSample &samples, uint seed) {
    return qHash(samples.m_filename, seed);
}
