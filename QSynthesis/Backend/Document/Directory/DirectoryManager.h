#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include <QFileSystemWatcher>
#include <QObject>

#include "QUtils.h"

class DirectoryManager : public QObject {
    Q_OBJECT
public:
    explicit DirectoryManager(QObject *parent = nullptr);
    virtual ~DirectoryManager();

    bool load();
    bool save();

    void clear();
    void reset();
    bool watched() const;

    QString dirname() const;
    void setDirname(const QString &dir);

    bool autoReload() const;
    void setAutoReload(bool autoReload);

protected:
    QString m_dirname;
    QStringList m_keyFiles;
    QFileSystemWatcher m_watcher;

    bool m_autoReload;

    virtual bool loadCore();
    virtual bool saveCore();

    virtual void resetCore();
    virtual void prepareCore();

    virtual void handleChangedCore();

private:
    void handleDirChanged(const QString &path);

signals:
    void changed();
};

#endif // DIRECTORYMANAGER_H
