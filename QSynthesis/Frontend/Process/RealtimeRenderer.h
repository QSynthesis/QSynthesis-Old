#ifndef REALTIMERENDERER_H
#define REALTIMERENDERER_H

#include <QObject>
#include <QThread>

#include "ResampleWork.h"

class RealtimeRenderer : public QObject {
    Q_OBJECT
public:
    explicit RealtimeRenderer(QObject *parent = nullptr);
    ~RealtimeRenderer();

public:
    int threadsCount() const;

    QList<int> priorWorks() const;
    void setPriorWorks(const QList<int> &priorWorks);

    void addWork(ResampleWork *work);
    void addWorks(const QList<ResampleWork *> &works);

private:
    QMap<int, ResampleWork *> pendingWorks;
    QList<QThread *> threads;

    QSet<QThread *> threadsAvailable;
    QSet<QThread *> threadsRunning;

    QMap<QThread *, ResampleWork *> runningWorks;
    QList<int> m_priorWorks;

    int nthreads;

    void addPending(ResampleWork *work);
    void addToThread(ResampleWork *work, QThread *thd);

    void handleThreadFinished();

public:
    void terminateAllWorks();

signals:
    void oneSuccess(int seq, const QString &filename);
};

#endif // REALTIMERENDERER_H
