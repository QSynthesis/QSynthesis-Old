#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

#include "MiniSystem/MiniSystem.h"
#include "PluginInfo.h"
#include "QUtils.h"

class PluginManager : public QObject {
    Q_OBJECT
public:
    explicit PluginManager(QObject *parent = nullptr);
    ~PluginManager();

public:
    QList<PluginInfo> plugins() const;

    QString dirname() const;
    void setDirname(const QString &dirname);

    bool load();
    void quit();

private:
    QString m_dirname;
    MiniSystemNotifier *notifier;
    QMap<QString, PluginInfo> pluginMap;

    void reloadPlugin(const QString &key);
    void handleFileChanged(const QStringList &files);

signals:
    void reloadRequested();
};

#endif // PLUGINMANAGER_H
