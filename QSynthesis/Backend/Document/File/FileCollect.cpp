#include "FileCollect.h"

FileCollect::FileCollect(QObject *parent) : DirectoryManager(parent) {
    reset();
}

FileCollect::FileCollect(QString dir, QObject *parent) : DirectoryManager(parent) {
    setDirname(dir);
}

FileCollect::~FileCollect() {
    reset();
}

FileManager *FileCollect::addFileCore(const QString &filename) {
    return nullptr;
}

void FileCollect::handleChildChangedCore(FileManager *child) {
}

bool FileCollect::loadCore() {
    QDir currDir(m_dirname);
    QFileInfoList flist = currDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    for (auto &info : flist) {
        addFile(info.absoluteFilePath());
    }
    return true;
}

bool FileCollect::saveCore() {
    bool result = true;
    for (FileManager *&file : m_files) {
        result &= file->save();
        if (!result) {
            break;
        }
    }
    return result;
}

void FileCollect::resetCore() {
    for (FileManager *&file : m_files) {
        delete file;
    }
    m_files.clear();
    m_names.clear();
}

void FileCollect::handleChangedCore() {
    QDir currDir(m_dirname);
    QFileInfoList flist = currDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    for (auto &info : flist) {
        QString dir = info.absoluteFilePath();
        if (!m_names.contains(dir)) {
            addFile(dir);
        }
    }

    QList<FileManager *> newFiles;
    for (auto it = m_files.begin(); it != m_files.end(); ++it) {
        FileManager *file = *it;
        if (!isFileExist(file->filename())) {
            m_names.remove(file->filename());
            delete file;
        } else {
            newFiles.append(file);
        }
    }
    m_files = newFiles;
}

void FileCollect::addFile(const QString &filename) {
    FileManager *file = addFileCore(filename);
    if (file->load()) {
        m_files.append(file);
        m_names.insert(filename);

        connect(file, &FileManager::changed, this, &FileCollect::handleChildChanged);
    } else {
        delete file;
    }
}

void FileCollect::handleChildChanged() {
    FileManager *file = qobject_cast<FileManager *>(sender());
    handleChildChangedCore(file);
}
