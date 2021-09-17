#include "PluginsCollect.h"

PluginsCollect::PluginsCollect(QObject *parent) : DirectoryCollect(parent) {
}

PluginsCollect::PluginsCollect(QString dir, QObject *parent) : DirectoryCollect(dir, parent) {
}

QList<PluginInfo *> PluginsCollect::dirs() const {
    QList<PluginInfo *> res;
    for (auto it = m_dirs.begin(); it != m_dirs.end(); ++it) {
        PluginInfo *plugin = qobject_cast<PluginInfo *>(*it);
        if (plugin->valid()) {
            res.append(plugin);
        }
    }
    return res;
}

DirectoryManager *PluginsCollect::addDirCore(const QString &dir, bool init) {
    PluginInfo *plugin = new PluginInfo(dir, this);
    plugin->load();
    if (!isDirExist(dir)) {
        delete plugin;
        return nullptr;
    }
    plugin->setAutoReload(true);
    connect(plugin, &PluginInfo::pluginTxtChanged, this, &PluginsCollect::handleChildChanged);
    connect(plugin, &PluginInfo::changed, this, &PluginsCollect::handleChildChanged);
    return plugin;
}

void PluginsCollect::handleChildChanged() {
    emit changed();
}
