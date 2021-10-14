#include "PluginManager.h"
#include "MiniSystem/MiniSystemNotifier.h"
#include "UTAU/QUtauStrings.h"
#include "application.h"

#include <QDir>
#include <QFileInfo>

PluginManager::PluginManager(QObject *parent) : QObject(parent) {
    notifier = nullptr;
}

PluginManager::~PluginManager() {
}

QList<PluginInfo> PluginManager::plugins() const {
    QList<PluginInfo> plugins;
    for (auto it = pluginMap.begin(); it != pluginMap.end(); ++it) {
        const PluginInfo &plugin = it.value();
        if (plugin.valid()) {
            plugins.append(plugin);
        }
    }
    return plugins;
}

QString PluginManager::dirname() const {
    return m_dirname;
}

void PluginManager::setDirname(const QString &dirname) {
    m_dirname = dirname;
}

bool PluginManager::load() {
    QDir currDir(m_dirname);
    if (!currDir.exists()) {
        return false;
    }

    QStringList flist = currDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
    for (auto it = flist.begin(); it != flist.end(); ++it) {
        QString cur = *it;
        QString absoultPath = m_dirname + Slash + cur;
        PluginInfo plugin(absoultPath);
        if (plugin.load()) {
            pluginMap.insert(cur, plugin);
        }
    }

    notifier = qSystem->createNotifier(m_dirname, MiniSystem::Directory);
    connect(notifier, &MiniSystemNotifier::fileChanged, this, &PluginManager::handleFileChanged);
    return true;
}

void PluginManager::quit() {
    qSystem->removeNotifier(notifier);
    notifier = nullptr;
}

void PluginManager::reloadPlugin(const QString &key) {
    auto it = pluginMap.find(key);
    if (it != pluginMap.end()) {
        PluginInfo &plugin = it.value();
        if (!plugin.load()) {
            pluginMap.erase(it);
        }
    } else {
        PluginInfo plugin(m_dirname + Slash + key);
        if (plugin.load()) {
            pluginMap.insert(key, plugin);
        }
    }
}

void PluginManager::handleFileChanged(const QStringList &files) {
    for (const QString &filename : files) {
        QString pluginDir = PathFindNextLevel(filename, m_dirname);
        reloadPlugin(pluginDir);
    }
    emit reloadRequested();
}
