#include "FileManager.h"
#include "QUtils.h"

FileManager::FileManager(QObject *parent) : QObject(parent) {
    m_filename = "";

    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &FileManager::handleFileChanged);
}

FileManager::~FileManager() {
}

bool FileManager::load(bool *valid) {
    resetCore();
    return loadCore(valid);
}

bool FileManager::save() {
    // Temporarily removed
    if (watched()) {
        m_watcher.removePath(m_filename);
    }

    bool res = saveCore();

    // Add back
    if (isFileExist(m_filename)) {
        if (!watched()) {
            m_watcher.addPath(m_filename);
        }
    }

    return res;
}

bool FileManager::remove() {
    if (watched()) {
        m_watcher.removePath(m_filename);
    }

    QFile file(m_filename);
    if (file.exists()) {
        return file.remove();
    } else {
        return true;
    }
}

void FileManager::clear() {
    resetCore();
}

void FileManager::reset() {
    if (watched()) {
        m_watcher.removePath(m_filename);
    }
    m_filename = "";
    resetCore();
}

bool FileManager::watched() const {
    return m_watcher.files().indexOf(m_filename) >= 0;
}

QString FileManager::filename() const {
    return m_filename;
}

void FileManager::setFilename(const QString &filename) {
    reset();
    m_filename = filename;

    if (isFileExist(filename)) {
        if (!watched()) {
            m_watcher.addPath(m_filename);
        }
    }
    prepareCore();
}
bool FileManager::loadCore(bool *valid) {
    return false;
}

bool FileManager::saveCore() {
    return false;
}

void FileManager::resetCore() {
}

void FileManager::prepareCore() {
}

void FileManager::handleChangedCore() {
}

void FileManager::handleDeletedCore() {
}

void FileManager::handleFileChanged(const QString &path) {
    handleChangedCore();
    emit changed();
}
