#include "ConcatenateWork.h"

#include <cmath>

ConcatenateWork::ConcatenateWork(QObject *parent) : BaseWork(parent) {
}

ConcatenateWork::~ConcatenateWork() {
}

void ConcatenateWork::start() {
    m_process->setProgram(m_wavtool);
    m_process->setWorkingDirectory(m_workingDir);
    m_process->setArguments(m_args.fullArguments());

    m_process->start();
    emit started();
}

QString ConcatenateWork::workingDir() const {
    return m_workingDir;
}

void ConcatenateWork::setWorkingDir(const QString &workingDir) {
    m_workingDir = workingDir;
}

QString ConcatenateWork::wavtool() const {
    return m_wavtool;
}

void ConcatenateWork::setWavtool(const QString &wavtool) {
    m_wavtool = wavtool;
}

WavtoolArgs ConcatenateWork::args() const {
    return m_args;
}

void ConcatenateWork::setArgs(const WavtoolArgs &args) {
    m_args = args;
}
