#include "DirectoryCollect.h"
#include "VoiceInfo.h"

DirectoryCollect::DirectoryCollect(QObject *parent) : DirectoryManager(parent) {
    reset();
}

DirectoryCollect::DirectoryCollect(QString dir, QObject *parent) : DirectoryManager(parent) {
    setDirname(dir);
}

DirectoryCollect::~DirectoryCollect() {
    reset();
}

DirectoryManager *DirectoryCollect::addDirCore(const QString &dirname, bool init) {
    DirectoryManager *dir = new DirectoryManager(this);
    dir->setDirname(dirname);
    if (!dir->load()) {
        delete dir;
        return nullptr;
    }
    return dir;
}

void DirectoryCollect::removeDirCore(DirectoryManager *dir, bool init) {
    delete dir;
}

void DirectoryCollect::handleChildChangedCore(DirectoryManager *child) {
}

bool DirectoryCollect::loadCore() {
    QDir currDir(m_dirname);
    if (!currDir.exists()) {
        return false;
    }
    QFileInfoList flist = currDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (auto &info : flist) {
        addDir(info.absoluteFilePath(), true);
    }
    return true;
}

bool DirectoryCollect::saveCore() {
    bool result = true;
    for (DirectoryManager *&dir : m_dirs) {
        result &= dir->save();
        if (!result) {
            break;
        }
    }
    return result;
}

void DirectoryCollect::resetCore() {
    for (DirectoryManager *&dir : m_dirs) {
        removeDirCore(dir, true);
    }
    m_dirs.clear();
    m_names.clear();
}

void DirectoryCollect::handleChangedCore() {
    QDir currDir(m_dirname);
    QFileInfoList flist = currDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (auto &info : flist) {
        QString dirname = info.absoluteFilePath();
        if (!m_names.contains(dirname)) {
            qDebug() << "Add New Dir" << dirname;
            addDir(dirname, false);
        }
    }

    QList<DirectoryManager *> newDirs;
    for (auto it = m_dirs.begin(); it != m_dirs.end(); ++it) {
        DirectoryManager *dir = *it;
        if (!isDirExist(dir->dirname())) {
            removeDir(dir, false);
        } else {
            newDirs.append(dir);
        }
    }
    m_dirs = newDirs;
}

void DirectoryCollect::addDir(const QString &dirname, bool init) {
    DirectoryManager *dir = addDirCore(dirname, init);
    if (dir) {
        m_dirs.append(dir);
        m_names.insert(dirname);
        connect(dir, &DirectoryManager::changed, this, &DirectoryCollect::handleChildChanged);
    }
}

void DirectoryCollect::removeDir(DirectoryManager *dir, bool init) {
    m_names.remove(dir->dirname());
    removeDirCore(dir, init);
}

void DirectoryCollect::handleChildChanged() {
    DirectoryManager *dir = qobject_cast<DirectoryManager *>(sender());
    handleChildChangedCore(dir);
}
