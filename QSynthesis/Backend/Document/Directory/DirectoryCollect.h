#ifndef DIRECTORYCOLLECT_H
#define DIRECTORYCOLLECT_H

#include "DirectoryManager.h"

class DirectoryCollect : public DirectoryManager {
    Q_OBJECT
public:
    explicit DirectoryCollect(QObject *parent = nullptr);
    explicit DirectoryCollect(QString dir, QObject *parent = nullptr);
    virtual ~DirectoryCollect();

protected:
    QSet<QString> m_names; // Dir names cache
    QList<DirectoryManager *> m_dirs;

    virtual DirectoryManager *addDirCore(const QString &dirname, bool init);
    virtual void removeDirCore(DirectoryManager *dir, bool init);

    virtual void handleChildChangedCore(DirectoryManager *child);

    bool loadCore() override;
    bool saveCore() override;
    void resetCore() override;
    void handleChangedCore() override;

private:
    void addDir(const QString &dirname, bool init);
    void removeDir(DirectoryManager *dir, bool init);

    void handleChildChanged();
};

#endif // DIRECTORYCOLLECT_H
