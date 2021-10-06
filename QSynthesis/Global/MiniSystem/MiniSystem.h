#ifndef MINISYSTEM_H
#define MINISYSTEM_H

#include "Macros.h"
#include "MiniSystemWatcher.h"
#include "PathTree.h"

#include <QThread>

class MiniSystemNotifier;

#define qSystem MiniSystem::instance()
class MiniSystem : public QObject {
    Q_OBJECT
    Q_SINGLETON(MiniSystem)

public:
    enum Type {
        File,
        Directory,
    };

    explicit MiniSystem(QObject *parent = nullptr);
    ~MiniSystem();

    friend class MiniSystemNotifier;

public:
    void start();
    void stop();

public:
    MiniSystemNotifier *createNotifier(const QString &path, Type type = Directory,
                                       bool check = true);
    void removeNotifier(MiniSystemNotifier *notifier);
    void removeAllNotifiers();

private:
    QThread *m_thread;

    MiniSystemWatcher m_fileWatcher;
    MiniSystemWatcher m_dirWatcher;

    QObject *obj;

    void handleThreadFinished();

private:
    QMap<QString, QPair<long, long>> filesMap;
    PathTree dirsTree;

    QSet<MiniSystemNotifier *> fileNotifiers;
    QSet<MiniSystemNotifier *> dirNotifiers;

    static void exitOnWatchFailed();
};

#endif // MINISYSTEM_H
