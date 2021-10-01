#ifndef MINISYSTEMWATCHER_H
#define MINISYSTEMWATCHER_H

#include <QDebug>
#include <QObject>

#include "efsw/efsw.hpp"

// Simple encapsultaion of efsw::FileWatcher for Qt use
class MiniSystemWatcher : public QObject,
                          protected efsw::FileWatcher,
                          private efsw::FileWatchListener {
    Q_OBJECT
public:
    enum Error {
        FileNotFound = -1,
        FileRepeated = -2,
        FileOutOfScope = -3,
        FileNotReadable = -4,
        FileRemote = -5,
        Unspecified = -6,
    };
    enum Action {
        Created = 1,
        Removed = 2,
        Modified = 3,
        Renamed = 4,
    };

public:
    explicit MiniSystemWatcher(QObject *parent = nullptr);
    ~MiniSystemWatcher();

    void watch();

public:
    long addPath(const QString &dir, bool recursive = false);
    bool removePath(const QString &dir);
    void removeAllPaths();

    void removePathById(long id);

    QStringList directories();

    void setFollowSymlinks(bool follow);
    bool followSymlinks() const;

private:
    QMap<QString, long> m_idMap;

    void handleFileAction(efsw::WatchID watchid, const std::string &dir,
                          const std::string &filename, efsw::Action action,
                          std::string oldFilename) override;

public:
    static QString lastErrorLog();
    static Error createLastError(Error err, const QString &log);

private:
    static QString removeLastSlashes(QString dirname);

signals:
    void fileChanged(long id, Action action, const QString &filename, const QString &oldFilename);
};

#endif // MINISYSTEMWATCHER_H
