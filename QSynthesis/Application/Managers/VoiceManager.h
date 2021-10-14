#ifndef VOICEMANAGER_H
#define VOICEMANAGER_H

#include <QObject>

#include "MiniSystem/MiniSystem.h"
#include "QUtils.h"
#include "VoiceInfo.h"

class VoiceManager : public QObject {
    Q_OBJECT
public:
    explicit VoiceManager(QObject *parent = nullptr);
    ~VoiceManager();

public:
    QList<VoiceInfo> voices() const;

    QString dirname() const;
    void setDirname(const QString &dirname);

    bool load();
    void quit();

private:
    QString m_dirname;
    MiniSystemNotifier *notifier;
    QMap<QString, VoiceInfo> voiceMap;

    void reloadVoice(const QString &key);
    void handleFileChanged(const QStringList &files);

signals:
    void reloadRequested();
};
#endif // VOICEMANAGER_H
