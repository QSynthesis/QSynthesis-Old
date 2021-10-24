#ifndef BASEWORK_H
#define BASEWORK_H

#include <QDebug>
#include <QObject>
#include <QProcess>

class BaseWork : public QObject {
    Q_OBJECT
public:
    explicit BaseWork(QObject *parent = nullptr);
    virtual ~BaseWork();

    void start();
    void terminate();

public:
    virtual void startCore();
    virtual void terminateCore();

protected:
    QProcess *m_process;

    virtual void handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void handleStartRequested();
    void handleTerminateRequested();

signals:
    void started();
    void finished();
    void crashed();

    void startRequested();
    void terminateRequested();
};

#endif // BASEWORK_H
