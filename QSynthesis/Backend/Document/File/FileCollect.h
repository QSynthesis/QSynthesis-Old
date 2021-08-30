#ifndef FILECOLLECT_H
#define FILECOLLECT_H

#include "Directory/DirectoryManager.h"
#include "FileManager.h"

class FileCollect : public DirectoryManager {
    Q_OBJECT
public:
    explicit FileCollect(QObject *parent = nullptr);
    explicit FileCollect(QString dir, QObject *parent = nullptr);
    ~FileCollect();

protected:
    QSet<QString> m_names; // Dir names cache
    QList<FileManager *> m_files;

    virtual FileManager *addFileCore(const QString &filename);
    virtual void handleChildChangedCore(FileManager *child);

    bool loadCore() override;
    bool saveCore() override;
    void resetCore() override;
    void handleChangedCore() override;

    void addFile(const QString &filename);

    void handleChildChanged();
};

#endif // FILECOLLECT_H
