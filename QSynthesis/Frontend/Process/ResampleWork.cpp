#include "ResampleWork.h"
#include "QUtils.h"

#include <cmath>

ResampleWork::ResampleWork(QObject *parent) : BaseWork(parent) {
    m_skipExist = false;
}

ResampleWork::~ResampleWork() {
}

void ResampleWork::startCore() {
    m_process->setProgram(m_resampler);
    m_process->setWorkingDirectory(m_workingDir);
    m_process->setArguments(m_args.fullArguments());

    emit started();

    if (!isFileExist(m_resampler)) {
        handleProcessFinished(0, QProcess::CrashExit);
    } else if (!m_skipExist || !isFileExist(m_args.outFile())) {
        m_process->start();
    } else {
        handleProcessFinished(0, QProcess::NormalExit);
    }
}

QString ResampleWork::workingDir() const {
    return m_workingDir;
}

void ResampleWork::setWorkingDir(const QString &workingDir) {
    m_workingDir = workingDir;
}

QString ResampleWork::resampler() const {
    return m_resampler;
}

void ResampleWork::setResampler(const QString &resampler) {
    m_resampler = resampler;
}

ResamplerArgs ResampleWork::args() const {
    return m_args;
}

void ResampleWork::setArgs(const ResamplerArgs &args) {
    m_args = args;
}

bool ResampleWork::skipExist() const {
    return m_skipExist;
}

void ResampleWork::setSkipExist(bool skipExist) {
    m_skipExist = skipExist;
}
