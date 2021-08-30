#ifndef PLUGINSCOLLECT_H
#define PLUGINSCOLLECT_H

#include "DirectoryCollect.h"
#include "PluginInfo.h"

// app/pluigns
class PluginsCollect : public DirectoryCollect {
    Q_OBJECT
public:
    explicit PluginsCollect(QObject *parent = nullptr);
    explicit PluginsCollect(QString dir, QObject *parent = nullptr);

    QList<PluginInfo *> dirs() const;

private:
    DirectoryManager *addDirCore(const QString &dir, bool init) override;

    void handleChildChanged();
};

#endif // PLUGINSCOLLECT_H
