#include "DirectoryManager.h"

DirectoryManager::DirectoryManager(QObject *parent) : QObject(parent) {
    m_dirname = "";

    m_autoReload = false;

    connect(&m_watcher, &QFileSystemWatcher::directoryChanged, this,
            &DirectoryManager::handleDirChanged);
}

DirectoryManager::~DirectoryManager() {
}

bool DirectoryManager::load() {
    resetCore();
    return loadCore();
}

bool DirectoryManager::save() {
    // Temporarily removed
    if (watched()) {
        m_watcher.removePath(m_dirname);
    }

    bool res = saveCore();

    // Add back
    if (res && !watched()) {
        m_watcher.addPath(m_dirname);
    }

    return res;
}

void DirectoryManager::clear() {
    resetCore();
}

void DirectoryManager::reset() {
    if (watched()) {
        m_watcher.removePath(m_dirname);
    }
    m_dirname = "";
    m_keyFiles.clear();
    resetCore();
}

bool DirectoryManager::watched() const {
    return m_watcher.directories().indexOf(m_dirname) >= 0;
}

QString DirectoryManager::dirname() const {
    return m_dirname;
}

void DirectoryManager::setDirname(const QString &dir) {
    reset();
    m_dirname = dir;

    if (isDirExist(dir) && !watched()) {
        m_watcher.addPath(dir);
    }
    prepareCore();
}

bool DirectoryManager::autoReload() const {
    return m_autoReload;
}

void DirectoryManager::setAutoReload(bool autoReload) {
    m_autoReload = autoReload;
}

bool DirectoryManager::loadCore() {
    return false;
}

bool DirectoryManager::saveCore() {
    return false;
}

void DirectoryManager::resetCore() {
}

void DirectoryManager::prepareCore() {
}

void DirectoryManager::handleChangedCore() {
}

void DirectoryManager::handleDirChanged(const QString &path) {
    if (m_autoReload) {
        load();
    }

    handleChangedCore();
    emit changed();
}
