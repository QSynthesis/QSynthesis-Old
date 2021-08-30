#include "ProjectOperation.h"

ProjectOperation::ProjectOperation() {
    m_type = Project;
}

ProjectOperation::~ProjectOperation() {
}

bool ProjectOperation::differ() const {
    return (m_orgWavtool != m_newWavtool) || (m_orgOutfile != m_newOutfile) ||
           (m_orgCache != m_newCache);
}

QString ProjectOperation::orgWavtool() const {
    return m_orgWavtool;
}

void ProjectOperation::setOrgWavtool(const QString &orgWavtool) {
    m_orgWavtool = orgWavtool;
}

QString ProjectOperation::newWavtool() const {
    return m_newWavtool;
}

void ProjectOperation::setNewWavtool(const QString &newWavtool) {
    m_newWavtool = newWavtool;
}

QString ProjectOperation::orgOutfile() const {
    return m_orgOutfile;
}

void ProjectOperation::setOrgOutfile(const QString &orgOutfile) {
    m_orgOutfile = orgOutfile;
}

QString ProjectOperation::newOutfile() const {
    return m_newOutfile;
}

void ProjectOperation::setNewOutfile(const QString &newOutfile) {
    m_newOutfile = newOutfile;
}

QString ProjectOperation::orgCache() const {
    return m_orgCache;
}

void ProjectOperation::setOrgCache(const QString &orgCache) {
    m_orgCache = orgCache;
}

QString ProjectOperation::newCache() const {
    return m_newCache;
}

void ProjectOperation::setNewCache(const QString &newCache) {
    m_newCache = newCache;
}
