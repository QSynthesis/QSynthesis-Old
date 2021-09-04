#include "BaseWork.h"

BaseWork::BaseWork(QObject *parent) : QObject(parent) {
    m_process = new QProcess(this);
    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            &BaseWork::handleProcessFinished);
}

BaseWork::~BaseWork() {
}

void BaseWork::start() {
    m_process->start();
    emit started();
}

void BaseWork::terminate() {
    if (m_process->state() == QProcess::Running) {
        m_process->kill();
    }
}

void BaseWork::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    if (exitStatus == QProcess::NormalExit) {
        emit finished();
    } else {
        emit crashed();
    }
}
