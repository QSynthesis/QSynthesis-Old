#include "BaseWork.h"

BaseWork::BaseWork(QObject *parent) : QObject(parent) {
    m_process = new QProcess(this);
    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
            &BaseWork::handleProcessFinished);

    connect(this, &BaseWork::startRequested, this, &BaseWork::handleStartRequested);
    connect(this, &BaseWork::terminateRequested, this, &BaseWork::handleTerminateRequested);
}

BaseWork::~BaseWork() {
}

void BaseWork::start() {
    emit startRequested();
}

void BaseWork::terminate() {
    emit terminateRequested();
}

void BaseWork::startCore() {
    m_process->start();
    emit started();
}

void BaseWork::terminateCore() {
    if (m_process->state() == QProcess::Running) {
        m_process->kill();
    } else {
        emit crashed();
    }
}

void BaseWork::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    if (m_process->state() == QProcess::Running) {
        m_process->waitForFinished();
    }
    if (exitStatus == QProcess::NormalExit) {
        emit finished();
    } else {
        emit crashed();
    }
}

void BaseWork::handleStartRequested() {
    startCore();
}

void BaseWork::handleTerminateRequested() {
    terminateCore();
}
