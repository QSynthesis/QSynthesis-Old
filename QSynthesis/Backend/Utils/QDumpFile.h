#ifndef QDUMPFILE_H
#define QDUMPFILE_H

/*
 *
 * This class is designed to prevent data loss due to crash.
 * Append a binary data to the dump file to keep track of user's operation.
 * After saving project, the dump file will be obsolete and needs to be deleted.
 *
 */

#include <QFile>
#include <QString>

class QDumpFile {
public:
    QDumpFile();
    ~QDumpFile();

public:
    QString filename() const;
    void setFilename(const QString &filename);

    bool append(quint32 id, const QByteArray &data) const;
    bool pop() const;

    bool exists() const;
    bool remove() const;

    QList<QPair<quint32, QByteArray>> readAll(bool *ok = nullptr) const;

private:
    QString m_filename;
};

#endif // QDUMPFILE_H
