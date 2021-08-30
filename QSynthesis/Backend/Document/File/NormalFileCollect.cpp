#include "NormalFileCollect.h"

NormalFileCollect::NormalFileCollect(QObject *parent) : FileCollect(parent) {
}

NormalFileCollect::NormalFileCollect(QString dir, QObject *parent) : FileCollect(dir, parent) {
}

NormalFileCollect::~NormalFileCollect() {
}

QList<NormalFile *> NormalFileCollect::files() const {
    QList<NormalFile *> res;
    for (auto it = m_files.begin(); it != m_files.end(); ++it) {
        res.append(qobject_cast<NormalFile *>(*it));
    }
    return res;
}

FileManager *NormalFileCollect::addFileCore(const QString &filename) {
    NormalFile *file = new NormalFile(filename, this);
    return file;
}
