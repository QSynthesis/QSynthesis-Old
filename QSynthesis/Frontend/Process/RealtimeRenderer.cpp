#include "RealtimeRenderer.h"
#include "QUtils.h"

#include <QTimer>

RealtimeRenderer::RealtimeRenderer(QObject *parent) : QObject(parent), nthreads(8) {
    for (int i = 0; i < nthreads; ++i) {
        QThread *thd = new QThread(this);
        connect(thd, &QThread::finished, this, &RealtimeRenderer::handleThreadFinished);
        threads.append(thd);
        threadsAvailable.insert(thd);
    }
}

RealtimeRenderer::~RealtimeRenderer() {
}

int RealtimeRenderer::threadsCount() const {
    return nthreads;
}

QList<int> RealtimeRenderer::priorWorks() const {
    return m_priorWorks;
}

void RealtimeRenderer::setPriorWorks(const QList<int> &priorWorks) {
    m_priorWorks = priorWorks;
}

void RealtimeRenderer::addWork(ResampleWork *work) {
    if (!threadsAvailable.isEmpty()) {
        addToThread(work, *threadsAvailable.begin());
    } else {
        addPending(work);
    }
}

void RealtimeRenderer::addWorks(const QList<ResampleWork *> &works) {
    for (auto it = works.begin(); it != works.end(); ++it) {
        addWork(*it);
    }
}

void RealtimeRenderer::addPending(ResampleWork *work) {
    int seq = work->args().sequence();
    auto it = pendingWorks.find(seq);
    if (it != pendingWorks.end()) {
        ResampleWork *&p = it.value();
        delete p;
        p = work;
    } else {
        pendingWorks.insert(seq, work);
    }
}

void RealtimeRenderer::addToThread(ResampleWork *work, QThread *thd) {
    qDebug() << "Run" << work << work->args().sequence()
             << PathFindFileName(work->args().outFile());

    const ResamplerArgs &args = work->args();
    int index = m_priorWorks.indexOf(args.sequence());
    if (index >= 0) {
        m_priorWorks.removeAt(index);
    }

    QString cacheDir = PathFindUpper(args.outFile());
    RemoveFilesWithPrefixNumber(cacheDir, args.sequence());

    threadsAvailable.remove(thd);
    threadsRunning.insert(thd);

    runningWorks.insert(thd, work);

    work->moveToThread(thd);

    connect(thd, &QThread::started, work, &ResampleWork::start);
    connect(work, &ResampleWork::finished, thd, &QThread::quit);
    connect(work, &ResampleWork::crashed, thd, &QThread::quit);

    thd->start();
}

void RealtimeRenderer::handleThreadFinished() {
    QThread *thd = qobject_cast<QThread *>(sender());

    auto it = runningWorks.find(thd);
    if (it == runningWorks.end()) {
        return;
    }

    ResampleWork *work = it.value();
    ResampleWork *work2 = nullptr;
    int seq = work->args().sequence();
    QString filename = PathFindFileName(work->args().outFile());

    // Abandon
    auto it2 = pendingWorks.find(work->args().sequence());
    if (it2 != pendingWorks.end()) {
        work2 = it.value();
    }
    delete work;

    runningWorks.erase(it);

    threadsRunning.remove(thd);
    threadsAvailable.insert(thd);

    if (work2) {
        addToThread(work2, thd);
    } else {
        if (!pendingWorks.isEmpty()) {
            auto it3 = pendingWorks.begin();
            if (m_priorWorks.isEmpty()) {
                auto it4 = pendingWorks.find(m_priorWorks.front());
                if (it4 != pendingWorks.end()) {
                    it3 = it4;
                }
            }
            work2 = it3.value();
            pendingWorks.erase(it3);
            addToThread(work2, thd);
        }
        emit oneSuccess(seq, filename);
    }
}

void RealtimeRenderer::terminateAllWorks() {
    // Remove pending works
    for (auto it = pendingWorks.begin(); it != pendingWorks.begin(); it++) {
        delete it.value();
    }
    pendingWorks.clear();
    if (runningWorks.isEmpty()) {
        return;
    }

    // Call running works to finish
    for (auto it = runningWorks.begin(); it != runningWorks.end(); it++) {
        it.value()->terminate();
    }

    // Wait for finish
    QEventLoop loop;
    QTimer timer;
    connect(&timer, &QTimer::timeout, this, [&loop, this]() {
        if (runningWorks.isEmpty()) {
            loop.quit();
        }
    });

    timer.start(10);
    loop.exec();
    timer.stop();
}
