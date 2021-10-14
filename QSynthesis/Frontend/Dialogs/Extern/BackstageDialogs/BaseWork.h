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

    virtual void start();
    virtual void terminate();

protected:
    QProcess *m_process;

    virtual void handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void started();
    void finished();
    void crashed();
};

#endif // BASEWORK_H
