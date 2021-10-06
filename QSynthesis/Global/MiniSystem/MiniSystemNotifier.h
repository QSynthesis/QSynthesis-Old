#ifndef MINISYSTEMNOTIFIER_H
#define MINISYSTEMNOTIFIER_H

#include <QTimer>

#include "MiniSystem.h"

class MiniSystemNotifier : public QTimer {
    Q_OBJECT

private:
    explicit MiniSystemNotifier(const QString &path, MiniSystem::Type type, MiniSystem *system,
                                QObject *parent = nullptr);
    ~MiniSystemNotifier();

    friend class MiniSystem;

private:
    void init();

public:
    MiniSystem *system() const;
    QString path() const;

    MiniSystem::Type type() const;

public:
    void requestKill(); // This method must be called from other thread

private:
    QString m_path;

    MiniSystem *m_system;
    MiniSystem::Type m_type;

    QSet<QString> m_pending;

    void handleFileChanged(long id, MiniSystemWatcher::Action action, const QString &filename,
                           const QString &oldFilename);
    void sendChangedSignal(MiniSystemWatcher::Action action, const QString &filename,
                           const QString &oldFilename);
    void sendChangedSignalDirectly(MiniSystemWatcher::Action action, const QString &filename,
                                   const QString &oldFilename);
    void prepareChangedSignal(const QString &filename);
    void sendPendingSignals();

    void handleKillRequested();

    void onTimer();
    void onAwake();
    void onSleep();

signals:
    void fileChanged(const QStringList &files);
    void killRequested();
};

#endif // MINISYSTEMNOTIFIER_H
