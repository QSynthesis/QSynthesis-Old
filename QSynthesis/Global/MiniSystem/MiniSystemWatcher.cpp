#include "MiniSystemWatcher.h"
#include "QUtils.h"

#include <QDir>

MiniSystemWatcher::MiniSystemWatcher(QObject *parent) : QObject(parent) {
    qRegisterMetaType<Action>("Action");
}

MiniSystemWatcher::~MiniSystemWatcher() {
}

void MiniSystemWatcher::watch() {
    efsw::FileWatcher::watch();
}

long MiniSystemWatcher::addPath(const QString &dir, bool recursive) {
    long id = efsw::FileWatcher::FileWatcher::addWatch(dir.toStdString(), this, recursive);
    if (id > 0) {
        m_idMap.insert(dir, id);
        return id;
    }
    return 0;
}

bool MiniSystemWatcher::removePath(const QString &dir) {
    auto it = m_idMap.find(dir);
    if (it == m_idMap.end()) {
        return false;
    }
    removePathById(it.value());
    m_idMap.erase(it);
    return true;
}

void MiniSystemWatcher::removeAllPaths() {
    for (auto it = m_idMap.begin(); it != m_idMap.end(); ++it) {
        removePathById(*it);
    }
    m_idMap.clear();
}

void MiniSystemWatcher::removePathById(long id) {
    efsw::FileWatcher::removeWatch(id);
}

QStringList MiniSystemWatcher::directories() {
    const std::list<std::string> &base = efsw::FileWatcher::directories();
    QStringList res;
    for (auto it = base.begin(); it != base.end(); ++it) {
        res.append(removeTailSlashes(QString::fromStdString(*it)));
    }
    return res;
}

void MiniSystemWatcher::setFollowSymlinks(bool follow) {
    efsw::FileWatcher::FileWatcher::followSymlinks(follow);
}

bool MiniSystemWatcher::followSymlinks() const {
    return efsw::FileWatcher::FileWatcher::followSymlinks();
}

void MiniSystemWatcher::handleFileAction(efsw::WatchID watchid, const std::string &dir,
                                         const std::string &filename, efsw::Action action,
                                         std::string oldFilename) {
    Q_UNUSED(watchid)
    Q_UNUSED(dir)

    QString qDir = removeTailSlashes(QDir::fromNativeSeparators(QString::fromStdString(dir)));
    emit fileChanged(watchid, static_cast<Action>(action),
                     qDir + '/' + QString::fromStdString(filename),
                     qDir + '/' + QString::fromStdString(oldFilename));
}

QString MiniSystemWatcher::lastErrorLog() {
    return QString::fromStdString(efsw::Errors::Log::getLastErrorLog());
}

MiniSystemWatcher::Error MiniSystemWatcher::createLastError(MiniSystemWatcher::Error err,
                                                            const QString &log) {
    return static_cast<Error>(
        efsw::Errors::Log::createLastError(static_cast<efsw::Error>(err), log.toStdString()));
}
