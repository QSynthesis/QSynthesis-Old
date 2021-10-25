#include "QDumpFile.h"
#include "Constants.h"

QDumpFile::QDumpFile() {
}

QDumpFile::~QDumpFile() {
}

QString QDumpFile::filename() const {
    return m_filename;
}

void QDumpFile::setFilename(const QString &filename) {
    m_filename = filename;
}

bool QDumpFile::append(quint32 id, const QByteArray &data) const {
    QFile file(m_filename);
    bool exist = file.exists();
    if (!file.open(QIODevice::Append)) {
        return false;
    }
    // Write file head
    if (!exist) {
        file.write(FILE_HEAD_DUMP.toUtf8());
    }

    // Write id and size
    int size = data.size();
    file.write((char *) &id, sizeof(id));
    file.write((char *) &size, sizeof(size));

    // Write data
    file.write(data);

    // Write twice
    file.write((char *) &size, sizeof(size));

    file.close();
    return true;
}

bool QDumpFile::pop() const {
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    const int idLen = sizeof(quint32);
    const int szLen = sizeof(int);
    QByteArray head(FILE_HEAD_DUMP.toUtf8());
    int total = file.size();
    int removeLen = idLen + szLen * 2;
    if (total < head.size() + removeLen) {
        file.close();
        return false;
    }

    file.seek(file.size() - szLen);

    QByteArray szBytes;
    szBytes = file.read(szLen);
    int size = *(int *) szBytes.data();

    removeLen += size;
    if (total < head.size() + removeLen) {
        file.close();
        return false;
    }
    file.close();

    return file.resize(total - removeLen);
}

bool QDumpFile::exists() const {
    QFile file(m_filename);
    return file.exists();
}

bool QDumpFile::remove() const {
    QFile file(m_filename);
    return file.exists() || file.remove();
}

QList<QPair<quint32, QByteArray>> QDumpFile::readAll(bool *ok) const {
    QList<QPair<quint32, QByteArray>> res;

#define RETURN(b)                                                                                  \
    if (ok) {                                                                                      \
        *ok = b;                                                                                   \
    }                                                                                              \
    return res;

    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly)) {
        RETURN(false)
    }

    // Read file head
    QByteArray head(FILE_HEAD_DUMP.toUtf8());
    QByteArray headBytes = file.read(head.size());
    if (headBytes != head) {
        file.close();
        RETURN(false)
    }

    bool failed = false;
    const int idLen = sizeof(quint32);
    const int szLen = sizeof(int);
    while (!file.atEnd() && !failed) {
        QByteArray idBytes, szBytes, dataBytes;
        idBytes = file.read(idLen);
        szBytes = file.read(szLen);
        if (idBytes.size() != idLen || szBytes.size() != szLen) {
            failed = true;
            break;
        }
        quint32 id = *(quint32 *) idBytes.data();
        int size = *(int *) szBytes.data();
        dataBytes = file.read(size);
        if (dataBytes.size() != size) {
            failed = true;
            break;
        }
        res.append(qMakePair(id, dataBytes));
        file.skip(szLen);
    }
    file.close();

    if (failed) {
        RETURN(false)
    }
    RETURN(true)
}
