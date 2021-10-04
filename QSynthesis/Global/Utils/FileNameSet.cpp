#include "FileNameSet.h"

FileNameSet::FileNameSet() : m_type(File) {
}

FileNameSet::FileNameSet(FileNameSet::Type type) : m_type(type) {
}

FileNameSet::Type FileNameSet::type() const {
    return m_type;
}

void FileNameSet::setType(const Type &type) {
    m_type = type;
}

void FileNameSet::set(const QStringList &files) {
    m_files = files;
    for (int i = 0; i < m_files.size(); ++i) {
        m_files[i] = m_files[i];
    }
}

QStringList FileNameSet::all() const {
    return m_files;
}

QStringList FileNameSet::valid() const {
    QStringList files;
    for (auto it = m_files.begin(); it != m_files.end(); ++it) {
        const QString &cur = *it;
        if (((m_type == File) && isFileExist(cur)) || ((m_type == Directory) && isDirExist(cur))) {
            files.append(cur);
        }
    }
    return files;
}

void FileNameSet::filter() {
    set(valid());
}

bool FileNameSet::unshift(const QString &s) {
    QString filename = removeTailSlashes(QDir::fromNativeSeparators(s));
    int index = m_files.indexOf(filename);
    if (index >= 0) {
        return false;
    }
    // 插到前面
    m_files.prepend(filename);
    return true;
}

void FileNameSet::advance(const QString &s) {
    QString filename = removeTailSlashes(QDir::fromNativeSeparators(s));
    remove(filename);
    unshift(filename);
}

bool FileNameSet::push(const QString &s) {
    QString filename = removeTailSlashes(QDir::fromNativeSeparators(s));
    int index = m_files.indexOf(filename);
    if (index >= 0) {
        return false;
    }
    // 插到前面
    m_files.append(filename);
    return true;
}

bool FileNameSet::remove(const QString &s) {
    QString filename = removeTailSlashes(QDir::fromNativeSeparators(s));
    int index = m_files.indexOf(filename);
    if (index < 0) {
        return false;
    }
    m_files.removeAt(index);
    return true;
}

bool FileNameSet::isEmpty() const {
    return m_files.isEmpty();
}

bool FileNameSet::contains(const QString &s) {
    return m_files.contains(s);
}


void FileNameSet::clear() {
    m_files.clear();
}
