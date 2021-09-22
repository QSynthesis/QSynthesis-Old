#include "ProjectInfoHandler.h"
#include "../TuningTab.h"
#include "Operations/ProjectOperation.h"

ProjectInfoHandler::ProjectInfoHandler(TuningTab *parent) : QObject(parent), m_tab(parent) {
}

ProjectInfoHandler::~ProjectInfoHandler() {
}

QString ProjectInfoHandler::wavtool() const {
    return m_wavtool;
}

void ProjectInfoHandler::setWavtool(const QString &wavtool) {
    m_wavtool = wavtool;
}

QString ProjectInfoHandler::outFile() const {
    return m_outFile;
}

void ProjectInfoHandler::setOutFile(const QString &outFile) {
    m_outFile = outFile;
}

void ProjectInfoHandler::modifyValues(const QString &wavtool, const QString &outFile) {
    ProjectOperation *p = new ProjectOperation();

    p->setOrgWavtool(m_wavtool);
    p->setOrgOutfile(m_outFile);

    p->setNewWavtool(wavtool);
    p->setNewOutfile(outFile);

    saveOperation(p);

    m_wavtool = wavtool;
    m_outFile = outFile;
}

void ProjectInfoHandler::saveOperation(ProjectOperation *p) {
    p = static_cast<ProjectOperation *>(p->simplify(p));
    if (p) {
        m_tab->addHistory(p);
    } else {
        qDebug() << "[Project Info] Addition Refused";
    }
}

bool ProjectInfoHandler::handleOperation(ProjectOperation *p, bool undo) {
    m_wavtool = undo ? p->orgWavtool() : p->newWavtool();
    m_outFile = undo ? p->orgOutfile() : p->newOutfile();
    return true;
}
